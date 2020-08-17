import sys
import time

import can
import mcp2515
import RPi.GPIO as GPIO
import spidev
from gp import Ui_MainWindow
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

GPIO.setmode(GPIO.BCM)
GPIO.setup(24, GPIO.IN)
GPIO.add_event_detect(24, GPIO.FALLING, callback=can.RX_interrupt)
filters = [65, 75, 20]
can.init(filters)


class RX(QThread):
    show_update = pyqtSignal()
    progressbar_update = pyqtSignal(int)
    updateprogress = 0

    def run(self):
        while 1:
            length = len(can.RX_msg)
            for i in range(length):
                if can.RX_msg[0]["ID"] == 65:
                    # send update request to mailbox
                    self.show_update.emit()
                elif can.RX_msg[0]["ID"] == 75:
                    # update the progress bar
                    updateprogress = can.RX_msg[0]["data"][0]
                    print("update progress  = ", updateprogress)
                    self.progressbar_update.emit(updateprogress)
                elif can.RX_msg[0]["ID"] == 20:
                    # Display GSM Busy on Text Browser
                    self.textBrowser_2.setText(
                        "GSM Busy, Cannnot complete action")

                del can.RX_msg[0]


class Main(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(Main, self).__init__(parent)
        QMainWindow.__init__(self)
        self.setupUi(self)

        self.myThread = RX(self)
        self.myThread.start()
        self.myThread.show_update.connect(self.Show_New_Update)
        self.myThread.progressbar_update.connect(self.Update_Progress_Bar)
        self.UI_Changes()
        self.Handel_Buttons()
        self.Open_USERS_Tab()

    def UI_Changes(self):
        # UI Changes in Login
        self.tabWidget.tabBar().setVisible(False)
        self.tabWidget_3.tabBar().setVisible(False)
        self.setWindowTitle("CAR_FOTA_Team")

    def Handel_Buttons(self):
        # Handel All Buttons In Our App
        self.pushButton.clicked.connect(self.Open_Gallery_Tab)
        self.pushButton_7.clicked.connect(self.Open_USERS_Tab)
        self.pushButton_2.clicked.connect(self.Open_FOTA_Tab)
        self.pushButton_14.clicked.connect(self.Open_FOTA_Tab)
        self.pushButton_18.setEnabled(False)
        self.pushButton_19.setEnabled(False)
        self.pushButton_18.clicked.connect(self.Accept_Update)
        self.pushButton_19.clicked.connect(self.Reject_Update)
        self.pushButton_20.clicked.connect(self.Open_DIAGS_Tab)
        self.pushButton_21.clicked.connect(self.Send_diagnostics_click)

    def Open_Gallery_Tab(self):
        self.tabWidget.setCurrentIndex(0)

    def Open_USERS_Tab(self):
        self.tabWidget.setCurrentIndex(6)
        self.tabWidget_2.setCurrentIndex(0)

    def Open_FOTA_Tab(self):
        self.tabWidget.setCurrentIndex(4)
        self.tabWidget_3.setCurrentIndex(0)
        self.tabWidget_4.setCurrentIndex(0)
        self.textBrowser.setText("Hello There!")

    def Open_DIAGS_Tab(self):
        self.tabWidget.setCurrentIndex(5)

    def Show_New_Update(self):
        self.textBrowser.setText("New Update Available")
        self.pushButton_18.setEnabled(True)
        self.pushButton_19.setEnabled(True)

    def Accept_Update(self):
        self.textBrowser.setText("Update In Progress")
        self.pushButton_18.setEnabled(False)
        self.pushButton_19.setEnabled(False)
        self.progressBar.setValue(0)
        msg = {
            "ID": 70,
            "format": "standard_format",
            "type": "remote_frame",
            "length": 0,
            "data": [0, 0, 0, 0, 0, 0, 0, 0],
        }
        can.transmit_buffer0(msg)

    def Reject_Update(self):
        self.textBrowser.setText("Update Cancelled")
        self.pushButton_18.setEnabled(False)
        self.pushButton_19.setEnabled(False)

    #        msg = {'ID':30, 'format':'standard_format', 'type':'data_frame', 'length':8, 'data':[1,2,3,4,5,6,7,8]}
    #        can.transmit_buffer0(msg)

    def Update_Progress_Bar(self, x):
        self.progressBar.setValue(x)
        if x == 100:
            self.textBrowser.setText("Update Completed")

    def Send_diagnostics_click(self):
        self.textBrowser_2.setText("Sending Diag in Progress")
        msg = {
            "ID": 25,
            "format": "standard_format",
            "type": "remote_frame",
            "length": 0,
            "data": [0, 0, 0, 0, 0, 0, 0, 0],
        }
        can.transmit_buffer0(msg)


###############################################################################

## message_box = self.textBrowser.text()

# pass

#######################################################

# def Handel_UPdate_Button(self):
# Handel UPdateButton Updates
# pass

#######################################################################################

# def Handel_Later_Button(self):
# Handel LaterButton Updates
# pass

#######################################################################################
# def Handel_Progress_bar(self):
# Handel Progressbar Updates
# pass


#######################################################################################
def main():
    app = QApplication(sys.argv)
    window = Main()
    window.show()
    app.exec_()


if __name__ == "__main__":
    main()
