from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot
from gamepad import XboxController
import serial
import struct


class SerialCom(QObject):
    ser = None
    gamepad = XboxController()
    rollTrim = pitchTrim = speedTrim = 0

    # Signals
    pitchUpdate = pyqtSignal(float)
    pitchTrimUpdate = pyqtSignal(float)
    rollUpdate = pyqtSignal(float)
    rollTrimUpdate = pyqtSignal(float)
    speedUpdate = pyqtSignal(float)
    speedTrimUpdate = pyqtSignal(float)
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

    @pyqtSlot(str, float)
    def setTrim(self, type, value):
        match type:
            case "roll":
                self.rollTrim = round(value, 2)
            case "pitch":
                self.pitchTrim = round(value, 2)
            case "speed":
                self.speedTrim = round(value, 2)

    def __init__(self):
        super().__init__()

    def setup(self):
        self.getAvailableComPorts()

    def poll(self):
        # GAMEPAD STUFF
        self.gamepadStatus.emit(self.gamepad.isConnected())
        roll, pitch, speed = self.gamepad.read()
        self.pitchTrim += self.gamepad.readPitchTrim(0.1)
        self.rollTrim += self.gamepad.readRollTrim(0.1)
        self.speedTrim += self.gamepad.readSpeedTrim(0.1)

        roll += self.rollTrim
        pitch += self.pitchTrim
        speed += self.speedTrim

        # pitch, roll, speed, mode, seq (float,float,float,int,int)
        roll = float(roll)
        pitch = float(pitch)
        speed = float(speed)
        mode = 1337
        seq = 1338
        self.pitchUpdate.emit(round(pitch, 2))
        self.pitchTrimUpdate.emit(round(self.pitchTrim, 2))
        self.rollUpdate.emit(round(roll, 2))
        self.rollTrimUpdate.emit(round(self.rollTrim, 2))
        self.speedUpdate.emit(round(speed, 2))
        self.speedTrimUpdate.emit(round(self.speedTrim, 2))
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
