from pyb import UART

class Sender():

    def init(self, bus=3, baud=9600, tout_c=10):
        self.uart = UART(bus, baud, timeout_char=tout_c)
        self.data = []

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

        # set up data buffer in LITTLE ENDIAN format
        for d in data:
            sendBuff.append(d & 0x00ff) #lsb
            sendBuff.append(d >> 8) #msb

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
