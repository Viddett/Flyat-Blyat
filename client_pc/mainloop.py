from PyQt5.QtCore import QObject, QTimer, pyqtSignal

from Gamepad import XboxController
#import serial
#import struct
#ser = serial.Serial('COM7', 9600)

gamepad = XboxController()


class mainloop(QObject):

    controlUpdate = pyqtSignal(float, float, float)

    def __init__(self):
        super().__init__()
        self.timer = QTimer()
        self.timer.timeout.connect(self.poll)
        self.timer.start(10)

    def poll(self):
        # GAMEPAD STUFF
        roll, pitch, speed = gamepad.read()
        # pitch, roll, speed, mode, seq (float,float,float,int,int)
        roll = float(roll)
        pitch = float(pitch)
        speed = float(speed)
        #print(roll, pitch, speed)
        self.controlUpdate.emit(pitch, roll, speed)
        '''
        mode = 1337
        seq = 1338
        # WARNING: mode and seq is 2 bytes each (short) CHECK OVERFLOW!
        pkt = bytearray(struct.pack('fffhh', roll, pitch, speed, mode, seq))
        ser.write(pkt)
        '''
