from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot
from gamepad import XboxController
import serial
import struct


class SerialCom(QObject):
    ser = None
    gamepad = XboxController()

    # Signals
    controlUpdate = pyqtSignal(float, float, float)
    comPortUpdate = pyqtSignal(str)
    comBoxClear = pyqtSignal()
    gamepadStatus = pyqtSignal(bool)

    # Slots
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

    def setup(self):
        self.getAvailableComPorts()

    def poll(self):
        # GAMEPAD STUFF
        roll, pitch, speed = self.gamepad.read()
        self.gamepadStatus.emit(self.gamepad.isConnected())
        # pitch, roll, speed, mode, seq (float,float,float,int,int)
        roll = float(roll)
        pitch = float(pitch)
        speed = float(speed)
        mode = 1337
        seq = 1338
        self.controlUpdate.emit(round(pitch, 2), round(roll, 2), round(speed, 2))
        # WARNING: mode and seq is 2 bytes each (short) CHECK OVERFLOW!
        if (self.ser is not None and self.ser.isOpen()):
            pkt = bytearray(struct.pack('fffhh', roll, pitch, speed, mode, seq))
            self.ser.write(pkt)

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
