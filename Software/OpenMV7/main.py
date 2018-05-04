from ledController import LEDController
from sender import Sender
from finder import Finder
import time

ledController = LEDController()

sender = Sender()
sender.init(initSend=[65506, 65506, 65506, 65506, 65506, 655065])

clock = time.clock()

finder = Finder()
finder.init(finder.ROBOT_O)

ledController.on(ledController.LED_RED)
# all leds off after init
ledController.allOff()

while True:
    #clock.tick()
    # ledController.blink()
    finder.takeSnapshot() # (draw center cross)
    data = finder.findObjects() # (mark ball, mark yellow, mark blue)
    sender.sendData(data)

    #print(data)
    #fps checking
    #print(clock.fps())
