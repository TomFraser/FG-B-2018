import sensor,image, time, math, pyb
from pyb import *
import ustruct, utime
from math import atan2, sqrt, pi, log

robotO = 0
robotP2 = 1

robot = robotP2

#Thresholds
if robot: #P2_Bot
    thresholds = [(0, 100, 16, 127, 3, 83), #Ball
    (39, 71, -41, 53, 48, 127), #(71, 99, -9, 12, 12, 59), #Yellow Goal
    (0, 27, -20, -6, -20, 4)] # Blue Goal
else: #O_Bot
    thresholds = [(32, 100, 38, 78, 18, 44), #Ball
    (42, 76, -30, 40, 25, 72), #(71, 99, -9, 12, 12, 59), #Yellow Goal
    (22, 34, -24, 21, -29, -5)] # Blue Goal

#LED's
ledRed = LED(2)
ledRed.on()
ledGreen = LED(1)
ledGreen.off()
ledBlue = LED(4)
ledBlue.off()
ledIR = LED(3)
ledIR.off()


global lastTime
global currentTime
lastTime = 500

def blink():
    global lastTime
    global currentTime
    currentTime = pyb.millis()
    if currentTime > (lastTime):
        ledGreen.toggle()
        lastTime = currentTime + 500

#UART Init
uart = UART(3, 9600, timeout_char=10)

#Image Sensor Stuff
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
sensor.set_auto_gain(False) #Must remain false for blob tracking
sensor.set_auto_whitebal(False) #Must remain false for blob tracking
sensor.set_brightness(0)
sensor.set_contrast(3)
sensor.skip_frames(time = 1000) #Start Delay
clock = time.clock()

#LED's all turn off after boot up is done
ledRed.off()
ledGreen.off()
ledBlue.off()

#Main Loop
while(True):
    clock.tick()
    #blink()

    #Reset Variables
    x = 0
    y = 0
    strength = 0
    goalAsize = 0
    goalDsize = 0

    #Find Ball
    img = sensor.snapshot()
    img.draw_cross(int(img.width() / 2), int(img.height() / 2))



    # find the ball
    balls = img.find_blobs([thresholds[0]], x_stride=2, y_stride=2, area_threshold=1, pixel_threshold=1, merge=False)
    if(len(balls) > 0):
        ball = sorted(balls, key= lambda ball: ball.pixels(), reverse=True)[0]

        # do the stuff
        x = -(ball.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
        y = ball.cy() - (img.height() / 2)
        angle = (atan2(y,x) * (180 / pi) - 90)%360
        strength = sqrt(x**2 + y**2)
        if angle > 45 and angle < 315:
            if strength < 60:
                angle = 65506
                strength = 0
            else:
                img.draw_cross(ball.cx(), ball.cy())
        else:
            img.draw_cross(ball.cx(), ball.cy())
            #img.draw_cross(int(img.width()/2), img.height() - int(img.height() / 8))

        # for ball in img.find_blobs([thresholds[0]], x_stride=2, y_stride=2, area_threshold=1, pixel_threshold=1, merge=False):
        #     img.draw_cross(ball.cx(), ball.cy())
        #     x = -(ball.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
        #     y = ball.cy() - (img.height() / 2)
        #     angle = (atan2(y,x) * (180 / pi) - 90)%360
        #     strength = sqrt(x**2 + y**2)

    # find the goals
    # goal A
    goalsA = img.find_blobs([thresholds[1]], x_stride=10, y_stride=10, area_threshold=50, pixel_threshold=50, merge=True)
    if(len(goalsA) > 0):
        goalA = sorted(goalsA, key= lambda goal: goal.pixels(), reverse=True)[0]

        if(sqrt(goalA.pixels())>10):
            x = -(goalA.cx() - (img.width() / 2))
            y = goalA.cy() - (img.height() / 2)
            goalAangle = (atan2(y,x) * (180 / pi) - 90)%360
            goalAsize = 2*(sqrt(x**2 + y**2)) #sqrt(goalA.pixels())
            #print(goalAsize)
            img.draw_rectangle(goalA.rect())
            img.draw_cross(goalA.cx(), goalA.cy())

    # goal D
    goalsD = img.find_blobs([thresholds[2]], x_stride=10, y_stride=10, area_threshold=50, pixel_threshold=50, merge=True)
    if(len(goalsD)):
        goalD = sorted(goalsD, key= lambda goal: goal.pixels(), reverse=True)[0]

        if(sqrt(goalD.pixels())>10):
            x = -(goalD.cx() - (img.width() / 2))
            y = goalD.cy() - (img.height() / 2)
            goalDangle = (atan2(y,x) * (180 / pi) - 90)%360
            goalDsize = 2*(sqrt(x**2 + y**2)) #sqrt(goalD.pixels())
            #print(goalDsize)
            img.draw_rectangle(goalD.rect())
            img.draw_cross(goalD.cx(), goalD.cy())

    # for goal in img.find_blobs(thresholds, x_stride=10, y_stride=10, area_threshold=50, pixel_threshold=50, merge=True):
    #     x = -(goal.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
    #     y = goal.cy() - (img.height() / 2)
    #     s = sqrt(goal.pixels())
    #     if goal.code() == 2 and s > 10: #2^1
    #         img.draw_rectangle(goal.rect())
    #         img.draw_cross(goal.cx(), goal.cy())
    #         goalAsize =  sqrt(goal.pixels())
    #         goalAangle = (atan2(y,x) * (180 / pi) - 90)%360
    #
    #     if goal.code() == 4 and s > 10: #2^2
    #         img.draw_cross(goal.cx(), goal.cy())
    #         goalDsize =  sqrt(goal.pixels())
    #         goalDangle = (atan2(y,x) * (180 / pi) - 90)%360

    #If not seeing ball, angle = 65506, else calculate ball angle
    if strength == 0: angle = 500
    if goalAsize == 0: goalAangle = 500
    if goalDsize == 0: goalDangle = 500

    ballData = [angle, strength]
    goalAdata = [int(goalAangle),int(goalAsize)]
    goalDdata = [int(goalDangle),int(goalDsize)]

    #print(goalAsize)



    ##### Create Buffer to Send over Serial #####

    sendBuff = [42,0,0,0,0,0,0,0,0,0,72]
    sendBuff[0] = 42
    sendBuff[10] = 72

    if angle <= 255:
        sendBuff[1] = int(angle)
        sendBuff[2] = 0
    else:
        sendBuff[1] = 255
        sendBuff[2] = int(angle % 255)

    if goalAdata[0] <= 255:
        sendBuff[3] = int(goalAdata[0])
        sendBuff[4] = 0
    else:
        sendBuff[3] = 255
        sendBuff[4] = int(goalAdata[0] % 255)

    sendBuff[5] = goalAdata[1]

    if goalDdata[0] <= 255:
        sendBuff[6] = int(goalDdata[0])
        sendBuff[7] = 0
    else:
        sendBuff[6] = 255
        sendBuff[7] = int(goalDdata[0] % 255)

    sendBuff[8] = goalDdata[1]

    sendBuff[9] = int(strength)

    for i in range(0,10):
        if sendBuff[i] == 42 and i != 0:
            sendBuff[i] = 43

    ##### Send Buffer Over Serial #####
    for buf in sendBuff:
        while True:
            try:
                uart.writechar(buf)
                break
            except Exception as e:
                print(e)
                pass

    # uart.writechar(sendBuff[0])
    # uart.writechar(sendBuff[1])
    # uart.writechar(sendBuff[2])
    # uart.writechar(sendBuff[3])
    # uart.writechar(sendBuff[4])
    # uart.writechar(sendBuff[5])
    # uart.writechar(sendBuff[6])
    # uart.writechar(sendBuff[7])
    # uart.writechar(sendBuff[8])
    # uart.writechar(sendBuff[9])

    #print(sendBuff)

    #pyb.delay(1)

    #Prints
    #print("Angle:")
    #print(angle)
    #print(angleOrbit)
    #print()
    #print("Strength:")
    #print(strength)
    #print()
    #print("Orbit Angle:")
    #print(orbitAngle)
    #print(clock.fps())
