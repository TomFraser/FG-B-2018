from ledController import LEDController
from sender import Sender
from finder import Finder
import time

ledController = LEDController()
# red led on for init
ledController.on(ledController.LED_RED)

clock = time.clock()

sender = Sender()
sender.init()

finder = Finder()
finder.init(finder.ROBOT_O)

# all leds off after init
ledController.allOff()

while True:
    clock.tick()
    #ledController.blink()
    finder.takeSnapshot(False) # (draw center cross)
    data = finder.findObjects(False, False) # (mark ball, mark goals)
    #sender.sendData(data)

    #fps checking
    #print(clock.fps())
