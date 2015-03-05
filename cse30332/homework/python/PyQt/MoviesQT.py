#John F. Lake, Jr. 
#My PyQt movies program

import sys
from PyQt4.QtGui import *

class MoviesQT(QMainWindow):
	def __init__(self):
		super(MoviesQT,self).__init__()
		self.setWindowTitle("Movie Recommender")



#Main function: 
if __name__ == "__main__":
	app = QApplication(sys.argv)
	gui = MoviesQT()
	gui.show()
	sys.exit(app.exec_())
