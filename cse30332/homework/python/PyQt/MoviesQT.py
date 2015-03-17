#John F. Lake, Jr. 
#CSE30332
#My PyQt movies program
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import os
import sys
import requests
import json

#Main class that holds everything else.
class MoviesQT(QMainWindow):
	
	#initialize
	def __init__(self):
		super(MoviesQT,self).__init__()
		self.setWindowTitle("Movie Recommender")
		self.resize(600,600)
		self.central = MoviesCentral(parent = self)
		self.setCentralWidget(self.central)
		self.SITE_URL = 'http://student01.cse.nd.edu:40001'
		self.USERS_URL = self.SITE_URL + '/users/'

		#Set up exit action: 
		exitAction = QAction("Quit",self)
		self.connect(exitAction, SIGNAL("triggered()"), self.exit)
		
		#Set up set user action:
		viewProfAction = QAction("View Profile",self)
		self.connect(viewProfAction, SIGNAL("triggered()"),self.view_profile)
		setUserAction = QAction("Set User",self)
		self.connect(setUserAction, SIGNAL("triggered()"),self.set_user)

		#Set up menu bar: 
		self.file_menu = self.menuBar().addMenu("File")
		self.file_menu.addAction(exitAction)
		self.user_menu = self.menuBar().addMenu("User")
		self.user_menu.addAction(viewProfAction)
		self.user_menu.addAction(setUserAction)

	#Exit the program (Called by File: Quit)
	def exit(self):
		sys.exit(app.exec_())

	#Simply gets the information for the GET call to /users/:user_id
	def view_profile(self):
		msgbox = QMessageBox()
		r = requests.get(self.USERS_URL + str(self.central.uid))
		resp = json.loads(r.content)
		msgbox.setText("Profile\n Gender: %s\n Age: %s\nZIP: %s" % (resp['gender'],resp['age'],resp['zipcode']))
		msgbox.exec_() 

	#A simple input dialog to prompt the user for the user ID
	def set_user(self):
		input = QInputDialog()
		text,ok = input.getText(self, 'Set User','Enter the User ID:')
		if ok:	
			self.central.uid = int(text)
		self.central.get_movie()

		#Reset the movie lists:
		self.central.goodMovies.setParent(None)
		self.central.badMovies.setParent(None)
		self.central.goodMovies = 0
		self.central.goodMovies = QListWidget()
		self.central.badMovies = 0
		self.central.badMovies = QListWidget()
		self.central.layout.addWidget(self.central.goodMovies,5,0)
		self.central.layout.addWidget(self.central.badMovies,5,2)
			

class MoviesCentral(QWidget):
	def __init__(self,parent=None):
		super(MoviesCentral,self).__init__(parent)

		#Set up everything
		self.uid = 1
		self.SITE_URL = 'http://student01.cse.nd.edu:40001'
		self.RECOMMENDATIONS_URL = self.SITE_URL + '/recommendations/'
		self.MOVIES_URL = self.SITE_URL + '/movies/'
		self.IMG_URL = '/afs/nd.edu/user37/cmc/Public/cse332_sp15/cherrypy/data/images/'
		self.RATINGS_URL = self.SITE_URL + '/ratings/'

		#Construct the GUI Elements
		self.movieTitle = QLabel("MOVIETITLE")
		self.upButton = QPushButton("UP")
		self.downButton = QPushButton("DOWN")
		self.upButton.clicked.connect(self.up_pressed)
		self.downButton.clicked.connect(self.down_pressed)
		self.goodLabel = QLabel("Good Movies:")
		self.badLabel = QLabel("Bad Movies:")
		self.badMovies = QListWidget()
		self.goodMovies = QListWidget()
		self.moviePic = QLabel(self)
		self.type = QLabel(self)
		self.rating = QLabel(self)


		#Put all of the elements in a grid layout
		self.layout = QGridLayout()
		self.layout.addWidget(self.movieTitle,0,1)
		self.layout.addWidget(self.upButton,1,0)
		self.layout.addWidget(self.moviePic,1,1)
		self.layout.addWidget(self.downButton, 1,2)
		self.layout.addWidget(self.type,2,1)
		self.layout.addWidget(self.rating,3,1)
		self.layout.addWidget(self.badLabel,4,2)
		self.layout.addWidget(self.goodLabel,4,0)
		self.layout.addWidget(self.badMovies,5,2)
		self.layout.addWidget(self.goodMovies,5,0)
		self.setLayout(self.layout)
		self.get_movie()

	#Down and up buttons to send put requests to the recommendations resource
	def down_pressed(self):
		input = {'movie_id':str(self.mid), 'rating': str(1), 'apikey':"AaD72Feb3"}
		r = requests.put(self.RECOMMENDATIONS_URL + str(self.uid),data=json.dumps(input))
		resp = json.loads(r.content)
		title = self.movieTitle.text()
		self.badMovies.addItem(str(title))
		self.get_movie()
	def up_pressed(self):
		input = {'movie_id':str(self.mid), 'rating': str(5), 'apikey':"AaD72Feb3"}
		r = requests.put(self.RECOMMENDATIONS_URL + str(self.uid),data=json.dumps(input))
		title = self.movieTitle.text()
		resp = json.loads(r.content)
		self.goodMovies.addItem(str(title))
		self.get_movie()

	#Get all the information to show for the current movie recommended
	def get_movie(self):

		#Get the movie_id of the recommended movie: 
		r = requests.get(self.RECOMMENDATIONS_URL +str(self.uid))
		resp = json.loads(r.content)
		self.mid = resp['movie_id']

		#Get all the info (picture, title, etc) for that movie
		r = requests.get(self.MOVIES_URL + str(self.mid))
		resp = json.loads(r.content)
		pic = QPixmap(self.IMG_URL + resp['img'])
		self.moviePic.setPixmap(pic)
		self.movieTitle.setText(resp['title'])
		self.type.setText(resp['genres'])
		
		#Get the rating for the film:
		r = requests.get(self.RATINGS_URL + str(self.mid))
		resp = json.loads(r.content)
		self.rating.setText(str(resp['rating']))

#Main function: 
if __name__ == "__main__":
	app = QApplication(sys.argv)
	gui = MoviesQT()
	gui.show()
	sys.exit(app.exec_())
