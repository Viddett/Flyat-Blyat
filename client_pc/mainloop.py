import sys
from PyQt5.QtCore import QObject, QTimer, pyqtSignal, pyqtSlot
from Gamepad import XboxController
import serial
import struct

gamepad = XboxController()


class mainloop(QObject):

    ser = None
    controlUpdate = pyqtSignal(float, float, float)
    comPortUpdate = pyqtSignal(str)
    comBoxClear = pyqtSignal()

    @pyqtSlot()
    def refreshComPorts(self):
        if (self.ser is not None):
            if (self.ser.isOpen()):
                self.ser.close()

        self.getAvailableComPorts()

    @pyqtSlot(str)
    def setComPort(self, comPort):
        self.ser = serial.Serial(comPort, 9600)

    def __init__(self):
        super().__init__()
        self.pollTimer = QTimer()
        self.pollTimer.timeout.connect(self.poll)
        self.pollTimer.start(10)

        self.sendSerialTimer = QTimer()
        self.sendSerialTimer.timeout.connect(self.doSerial)
        self.sendSerialTimer.start(25)

    def setup(self):
        self.getAvailableComPorts()

    def poll(self):
        pass

    def doSerial(self):
        # GAMEPAD STUFF
        roll, pitch, speed = gamepad.read()
        # pitch, roll, speed, mode, seq (float,float,float,int,int)
        roll = float(roll)
        pitch = float(pitch)
        speed = float(speed)
        mode = 1337
        seq = 1338
        # WARNING: mode and seq is 2 bytes each (short) CHECK OVERFLOW!
        if (self.ser is not None and self.ser.isOpen()):
            pkt = bytearray(struct.pack('fffhh', roll, pitch, speed, mode, seq))
            self.ser.write(pkt)

        self.controlUpdate.emit(pitch, roll, speed)

    def getAvailableComPorts(self):
        ports = ['COM%s' % (i + 1) for i in range(256)]
        result = []
        self.comBoxClear.emit()
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                self.comPortUpdate.emit(port)
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result

