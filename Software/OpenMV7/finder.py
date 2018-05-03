import image, sensor, time
from math import atan2, sqrt, pi

class Finder:

    def __init__(self):
         self.ROBOT_O = 0
         self.ROBOT_P2 = 1

    def init(self, robot_):
        self.robot = robot_
        if self.robot == self.ROBOT_O: #O_bot
            self.thresholds = [(28, 73, 25, 83, 7, 55), #Ball
            (44, 100, -9, 20, 6, 127),  #Yellow Goal
            (0, 41, -128, 19, -128, -23)] # Blue Goal
        elif self.robot == self.ROBOT_P2: #P2_bot
            self.thresholds = [(0, 100, 16, 127, 3, 83), #Ball
            (39, 71, -41, 53, 48, 127), #Yellow Goal
            (0, 27, -20, -6, -20, 4)] # Blue Goal

        # sensor setup
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
        sensor.skip_frames(time=2000)

        sensor.set_auto_whitebal(False, rgb_gain_db=(-6.02073, -6.02073, 1.717804)) #Must remain false for blob tracking
        sensor.set_auto_exposure(False, exposure_us=5000)
        sensor.skip_frames(time=500)

        curr_gain = sensor.get_gain_db()
        sensor.set_auto_gain(False, gain_db=curr_gain*1.3) #Must remain false for blob tracking

        sensor.set_brightness(0)
        sensor.set_contrast(3)

        sensor.skip_frames(time=500)


    def takeSnapshot(self, center=False):
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


    def findObjects(self, markBall=False, markYellow=False, markBlue=False, minDist=40, maxDist=130):
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
#f.takeSnapshot()
#while True:
    #f.takeSnapshot()
    #f.findObjects(True, False, False)
