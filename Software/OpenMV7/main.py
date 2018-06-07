## ===================== FINDER ===========================
import image, sensor, time
from math import atan2, sqrt, pi

class Finder:

    def __init__(self):
         self.ROBOT_O = 0
         self.ROBOT_P2 = 1

    def init(self, robot_):
        self.robot = robot_
        if self.robot == self.ROBOT_O: #O_bot
            self.thresholds = [(46, 79, 33, 78, -8, 72), #Ball
            (65, 100, -40, 127, 36, 127),  #Yellow Goal
            (50, 69, -22, -3, -53, -17)] # Blue Goal
        elif self.robot == self.ROBOT_P2: #P2_bot
            self.thresholds = [(45, 71, 21, 68, 5, 76), #Ball
            (39, 71, -41, 53, 48, 127), #Yellow Goal
            (27, 44, -30, 7, -45, -6)] # Blue Goal


        # sensor setup
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
        #sensor.set_windowing((70, 0, 180, 179))
        sensor.set_windowing((77,8,186,187))

        sensor.skip_frames(time=2000)

        sensor.set_auto_exposure(False)
        sensor.set_auto_whitebal(False)
        # Need to let the above settings get in...
        sensor.skip_frames(time = 500)

        # === GAIN ===
        curr_gain = sensor.get_gain_db()
        sensor.set_auto_gain(False, gain_db=curr_gain)

        # === EXPOSURE ===
        curr_exposure = sensor.get_exposure_us()
        sensor.set_auto_exposure(False, exposure_us = int(curr_exposure))

        # === WHITE BAL ===
        sensor.set_auto_whitebal(False, rgb_gain_db=(-6.02073, -4.99849, 1.260288)) #Must remain false for blob tracking

        sensor.set_brightness(1)
        sensor.set_contrast(0)
        sensor.set_saturation(2)

        sensor.skip_frames(time=500)


    def takeSnapshot(self, center=True):
        self.img = sensor.snapshot()
        if(center): self.img.draw_cross(int(self.img.width() / 2), int(self.img.height() / 2))

    def calcAngDist(self, object):
        if(not object):
            return (65506, 65506)
        x = -(object.cx() - (self.img.width() / 2))
        y =  object.cy() - (self.img.height() / 2)
        angle = (atan2(-y,x) * (180 / pi) - 90)%360
        dist = (sqrt(x**2 + y**2))
        return (angle, dist)


    def findObjects(self, markBall=False, markYellow=False, markBlue=False, minDist=40, maxDist=160):
        balls = self.img.find_blobs([self.thresholds[0]], x_stride=2, y_stride=2, area_threshold=1, pixel_threshold=2, merge=False)

        # yGoals = self.img.find_blobs([self.thresholds[1]], x_stride=10, y_stride=10, area_threshold=1, pixel_threshold=1, merge=False)
        # bGoals = self.img.find_blobs([self.thresholds[2]], x_stride=10, y_stride=10, area_threshold=1, pixel_threshold=1, merge=False)

        # ---- Goal Blobs method below ---- (i dont know if its faster than two seaparate calls like above)
        goalBlobs = self.img.find_blobs(self.thresholds[1:], x_stride=10, y_stride=10, area_threshold=1, pixel_threshold=10, merge=False)


        # codes:
        # ball: 1
        # yellow goal: 2
        # blue goal: 4
        yGoals = []
        bGoals = []
        for blob in goalBlobs:
            if blob.code() == 1:
                yGoals.append(blob)
            elif blob.code() == 2:
                bGoals.append(blob)

        ballAngle = yGoalAngle = bGoalAngle = 65506
        ballDist = yGoalDist = bGoalDist = 65506
        ball = yGoal = bGoal = None

        if len(balls) > 0:
            for obj in sorted(balls, key= lambda x: x.pixels(), reverse=True):
                ballAngle, ballDist = self.calcAngDist(obj)
                if(ballDist > minDist and ballDist < maxDist):
                    ball = obj
                    break

        if len(yGoals) > 0:
            for obj in sorted(yGoals, key= lambda x: x.pixels(), reverse=True):
                yGoalAngle, yGoalDist = self.calcAngDist(obj)
                if(yGoalDist > minDist and yGoalDist < maxDist):
                    yGoal = obj
                    break

        if len(bGoals) > 0:
            for obj in sorted(bGoals, key= lambda x: x.pixels(), reverse=True):
                bGoalAngle, bGoalDist = self.calcAngDist(obj)
                if(bGoalDist > minDist and bGoalDist < maxDist):
                    bGoal = obj
                    break


        if(markBall and ball):
            self.img.draw_cross(ball.cx(), ball.cy())

        if(yGoal and markYellow):
            self.img.draw_rectangle(yGoal.rect())
            self.img.draw_cross(yGoal.cx(), yGoal.cy())
        if(bGoal and markBlue):
            self.img.draw_cross(bGoal.cx(), bGoal.cy())
            self.img.draw_rectangle(bGoal.rect())

        # output must be a list in order:
        # 0. ball angle
        # 1. ball distance
        # 2. yellow goal angle
        # 3. yellow goal distance
        # 4. blue goal angle
        # 5. blue goal distance

        return [ballAngle, ballDist, yGoalAngle, yGoalDist, bGoalAngle, bGoalDist]

#test code
#f = Finder()
#f.init(f.ROBOT_O)
#f.takeSnapshot()k
#while True:
    #f.takeSnapshot()
    #f.findObjects(True, False, False)

## ========================= LED CONTROLLER ===========================
from pyb import LED, millis

class LEDController:

    def __init__(self):
        self.LED_GREEN = 2
        self.LED_RED = 1
        self.LED_IR = 4
        self.LED_BLUE = 3

        self.ledRed = LED(self.LED_RED)
        self.ledGreen = LED(self.LED_GREEN)
        self.ledBlue = LED(self.LED_BLUE)
        self.ledIR = LED(self.LED_IR)

        self.ledGreen.off()
        self.ledRed.off()
        self.ledIR.off()
        self.ledBlue.off()


        # blink var
        self.lastTime = 500

    def allOff(self):
        self.ledGreen.off()
        self.ledRed.off()
        self.ledIR.off()
        self.ledBlue.off()

    def on(self, led):
        if(led == self.LED_RED):
            self.ledRed.on()
        elif(led == self.LED_GREEN):
            self.ledGreen.on()
        elif(led == self.LED_IR):
            self.ledIR.on()
        elif(led == self.LED_BLUE):
            self.ledBlue.on()

    def off(self, led):
        if(led == self.LED_RED):
            self.ledRed.off()
        elif(led == self.LED_GREEN):
            self.ledGreen.off()
        elif(led == self.LED_IR):
            self.ledIR.off()
        elif(led == self.LED_BLUE):
            self.ledBlue.off()

    def toggle(self, led):
        if(led == self.LED_RED):
            self.ledRed.toggle()
        elif(led == self.LED_GREEN):
            self.ledGreen.toggle()
        elif(led == self.LED_IR):
            self.ledIR.toggle()
        elif(led == self.LED_BLUE):
            self.ledBlue.toggle()

    def blink(self):
        currentTime = millis()
        if currentTime > (self.lastTime):
            self.ledGreen.toggle()
            self.lastTime = currentTime + 500

## =================== SENDER ==============================
from pyb import UART

class Sender():

    def init(self, bus=3, baud=9600, tout_c=10, initSend=None):
        self.uart = UART(bus, baud, timeout_char=tout_c)
        if(initSend):
            self.sendData(initSend)

    def sendData(self, data):
        # data is a list in the format:
        # 0. ball angle
        # 1. ball distance
        # 2. yellow goal angle
        # 3. yellow goal distance
        # 4. blue goal angle
        # 5. blue goal distance

        # convert everything into integers to send
        data = [round(x) for x in data]

        # data buffer that will get populated with bytes to send (just has sync char at the start)
        sendBuff = [42]

        # set up data buffer in BIG ENDIAN format
        for d in data:
            sendBuff.append(d >> 8) #msb
            sendBuff.append(d & 0x00ff) #lsb

        # make sure nothing pretends to be the sync char
        for i in range(1, len(sendBuff)):
            if(sendBuff[i] == 42): sendBuff[i] = 43

        # send the data
        for buf in sendBuff:
            while True:
                try:
                    self.uart.writechar(buf)
                    break
                except Exception as e:
                    print(e)
                    pass

#test code
#s = Sender()
#s.init()
#s.sendData([65506, 65506, 65506, 65506, 65506, 65506])

## ========================== MAIN =============================

ledController = LEDController()

sender = Sender()
sender.init(initSend=[65506, 65506, 65506, 65506, 65506, 655065])

clock = time.clock()

finder = Finder()
finder.init(finder.ROBOT_O)

ledController.on(ledController.LED_RED)
sensor.skip_frames(time=500)

# all leds off after init
ledController.allOff()

while True:
    #clock.tick()
    # ledController.blink()
    finder.takeSnapshot() # (draw center cross)
    data = finder.findObjects(True, True, True) # (mark ball, mark yellow, mark blue)
    sender.sendData(data)

    #print(data)
    #fps checking
    #print(clock.fps())
