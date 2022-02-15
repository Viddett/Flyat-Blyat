import sys
from mainloop import mainloop

from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
#from PyQt5.QtCore import QObject


# Setup gui
app = QGuiApplication(sys.argv)
engine = QQmlApplicationEngine()
engine.quit.connect(app.quit)
engine.load('main.qml')


# Start main loop
backend = mainloop()
engine.rootObjects()[0].setProperty('backend', backend)

# Start gui
sys.exit(app.exec())
