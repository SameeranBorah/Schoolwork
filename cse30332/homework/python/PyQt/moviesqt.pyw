from PyQt4.QtCore import *
from PyQt4.QtGui import *

import os
import sys
import requests
import json

class MoviesQT(QMainWindow):
	def __init__(self):
		super(MoviesQT, self).__init__()
		self.central = MoviesCentral(parent = self)
		self.setCentralWidget(self.central)

		userAction = QAction("View Profile", self)
		self.connect(userAction, SIGNAL("triggered()"), self.view_profile)

		self.user_menu = self.menuBar().addMenu("User")
		self.user_menu.addAction(userAction)
		

	def view_profile(self):
		msgbox = QMessageBox()
		msgbox.setText("garfield is a cat")
		msgbox.exec_()  # COME BACK THIS LINE IN A SECOND

class MoviesCentral(QWidget):
	def __init__(self, parent=None):
		super(MoviesCentral, self).__init__(parent)
		self.titlelbl = QLabel("garfield")

		layout = QGridLayout()
		layout.addWidget(self.titlelbl)
		self.setLayout(layout)

app = QApplication(sys.argv)
gui = MoviesQT()
gui.show()
app.exec_()


