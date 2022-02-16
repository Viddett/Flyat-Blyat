import sys
import time
from mainloop import mainloop

from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine

# Setup gui
app = QGuiApplication(sys.argv)
engine = QQmlApplicationEngine()
engine.quit.connect(app.quit)
engine.load('main.qml')

time.sleep(1)  # Avoid frequent start crash

# Start main loop
backend = mainloop()
engine.rootObjects()[0].setProperty('backend', backend)
backend.setup()


# Start gui
sys.exit(app.exec())
