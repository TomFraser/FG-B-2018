import image, sensor, time
from math import atan2, sqrt, pi

class Finder:

    def __init__(self):
         self.ROBOT_O = 0
         self.ROBOT_P2 = 1

    def init(self, robot_):
        self.robot = robot_
        if self.robot == self.ROBOT_O: #O_bot
            self.thresholds = [(35, 45, 40, 60, 40, 60), #Ball
            (42, 76, -30, 40, 25, 72), #(71, 99, -9, 12, 12, 59), #Yellow Goal
            (22, 34, -24, 21, -29, -5)] # Blue Goal
        elif self.robot == self.ROBOT_P2: #P2_bot
            self.thresholds = [(0, 100, 16, 127, 3, 83), #Ball
            (39, 71, -41, 53, 48, 127), #Yellow Goal
            (0, 27, -20, -6, -20, 4)] # Blue Goal


        # sensor setup
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
        sensor.set_auto_gain(True) #Must remain false for blob tracking
        sensor.set_auto_whitebal(False) #Must remain false for blob tracking
        sensor.set_brightness(0)
        sensor.set_contrast(0)
        sensor.skip_frames(time = 1000) #Start Delay


    def takeSnapshot(self, center=False):
        self.img = sensor.snapshot()
        if(center): self.img.draw_cross(int(self.img.width() / 2), int(self.img.height() / 2))

    def calcAngDist(self, object):
        if(object == 0):
            return (65506, 65506)
        x = -(object.cx() - (self.img.width() / 2))
        y =  object.cy() - (self.img.height() / 2)
        angle = (atan2(y,x) * (180 / pi) - 90)%360
        dist = (sqrt(x**2 + y**2))
        return (angle, dist)


    def findObjects(self, markBall=False, markGoals=False):
        balls = self.img.find_blobs([self.thresholds[0]], x_stride=2, y_stride=2, area_threshold=1, pixel_threshold=1, merge=False)

        # yGoals = self.img.find_blobs([self.thresholds[1]], x_stride=10, y_stride=10, area_threshold=1, pixel_threshold=1, merge=False)
        # bGoals = self.img.find_blobs([self.thresholds[2]], x_stride=10, y_stride=10, area_threshold=1, pixel_threshold=1, merge=False)

        # ---- Goal Blobs method below ---- (i dont know if its faster than two seaparate calls like above)
        goalBlobs = self.img.find_blobs(self.thresholds[1:], x_stride=10, y_stride=10, area_threshold=1, pixel_threshold=1, merge=False)


        # codes:
        # ball: 1
        # yellow goal: 2
        # blue goal: 4
        yGoals = []
        bGoals = []
        for blob in goalBlobs:
            if blob.code() == 2:
                yGoals.append(blob)
            elif blob.code() == 4:
                bGoals.append(blob)


        if len(balls) > 0:
            ball = sorted(balls, key= lambda x: x.pixels(), reverse=True)[0]
        else:
            ball = 0

        if len(yGoals) > 0:
            yGoal = sorted(yGoals, key= lambda x: x.pixels(), reverse=True)[0]
        else:
            yGoal = 0

        if len(bGoals) > 0:
            bGoal = sorted(bGoals, key= lambda x: x.pixels(), reverse=True)[0]
        else:
            bGoal = 0

        ballAngle, ballDist = self.calcAngDist(ball)
        yGoalAngle, yGoalDist = self.calcAngDist(yGoal)
        bGoalAngle, bGoalDist = self.calcAngDist(bGoal)

        if(markBall and ball):
            self.img.draw_cross(ball.cx(), ball.cy())

        if(markGoals):
            if(yGoal):
                self.img.draw_rectangle(yGoal.rect())
                self.img.draw_rectangle(bGoal.rect())
            if(bGoal):
                self.img.draw_cross(yGoal.cx(), yGoal.cy())
                self.img.draw_cross(bGoal.cx(), bGoal.cy())

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
#f.takeSnapshot()
#f.findObjects(False, False)
