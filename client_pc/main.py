import sys
from serialCom import SerialCom

from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from PyQt5.QtCore import QObject, QTimer

app = QGuiApplication(sys.argv)
engine = QQmlApplicationEngine()
engine.quit.connect(app.quit)
engine.load('main.qml')


class Backend(QObject):

    def __init__(self):
        super().__init__()
        self.pollTimer = QTimer()
        self.serialCom = SerialCom()

    def setup(self):
        engine.rootObjects()[0].setProperty('serialCom', self.serialCom)
        self.serialCom.setup()
        self.pollTimer.timeout.connect(self.poll)
        self.pollTimer.start(10)

    def poll(self):
        self.serialCom.poll()


backend = Backend()
backend.setup()
sys.exit(app.exec())
