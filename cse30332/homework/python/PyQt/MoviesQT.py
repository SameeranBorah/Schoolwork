#John F. Lake, Jr. 
#My PyQt movies program

from PyQt4.QtCore import *
from PyQt4.QtGui import *
import os
import sys
import requests
import json

class MoviesQT(QMainWindow):
	def __init__(self):
		super(MoviesQT,self).__init__()
		self.setWindowTitle("Movie Recommender")
		self.central = MoviesCentral(parent = self)
		self.setCentralWidget(self.central)
		self.SITE_URL = 'http://student00.cse.nd.edu:40001'
		self.RECOMMENDATIONS_URL = self.SITE_URL + '/recommendations/'
		#Set up exit action: 
		exitAction = QAction("Quit",self)
		self.connect(exitAction, SIGNAL("triggered()"), self.exit)

		#Set up menu bar: 
		self.file_menu = self.menuBar().addMenu("File")
		self.file_menu.addAction(exitAction)

	def exit(self):
		sys.exit(app.exec_())
		

class MoviesCentral(QWidget):
	def __init__(self,parent=None):
		super(MoviesCentral,self).__init__(parent)
		self.uid = 5


#Main function: 
if __name__ == "__main__":
	app = QApplication(sys.argv)
	gui = MoviesQT()
	gui.show()
	sys.exit(app.exec_())
