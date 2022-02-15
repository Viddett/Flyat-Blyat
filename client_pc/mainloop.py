from PyQt5.QtCore import QTimer


class mainloop:
    def __init__(self):
        self.timer = QTimer()
        self.timer.timeout.connect(self.poll)
        self.timer.start(10)

    def poll(self):
        pass
