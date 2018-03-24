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
