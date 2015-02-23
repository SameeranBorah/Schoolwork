#John F. Lake, Jr. 
#Python Primer





class _movie_database:

	def __init__(self):
		self.movies = {}
		self.users = {}
		self.ratings = {}




	# Loads in a movies file
	def load_movies(self,movie_file):
		self.movies = {}
		movieFile = open(movie_file)
		for line in movieFile:
			movieInfo = line.split("::")
			self.movies[movieInfo[0]] = []
			self.movies[movieInfo[0]] = movieInfo
		
	def get_movie(self,mid):
		if str(mid) in self.movies.keys():
			mo = []
			mo = self.movies[str(mid)]
			return mo[1:]
		else:
			print "There is no such movie."
			return []
		
	def movies(self):
		keys = []
		for key in self.movies.keys():
			keys.append(key)
		return keys	
	def set_movie(self,mid,info):
		self.movies[str(mid)] = info
	def delete_movie(self,mid):
		del self.movies[str(mid)]
	def load_users(self,users_file):
		self.users = {}
		uFile = open(users_file)
		for line in uFile:
			userInfo = line.split("::")
			self.users[userInfo[0]] = []
			self.users[userInfo[0]] = userInfo
	def get_user(self,uid):
		if str(uid) in self.users.keys():
			u = []
			u = self.users[str(uid)]
			return u[1:]
		else:
			print "There is no such user."
			return []

	def get_users(self):
		keys = []
		for key in self.users.keys():
			keys.append(key)
		return keys	

	def set_user(self,uid, info):
		self.users[str(uid)] = info
	def delete_user(self,uid):
		del self.users[str(uid)]
	def load_ratings(self,ratings_file):
		print "loadRat"
	def get_rating(self,mid):
		print "getRat"
	def get_highest_rated_movie(self):
		print "getHighest"
	def set_user_movie_rating(self,uid,mid,rating):
		print "setUserMovieRat"
	def get_user_movie_rating(self,uid,mid):
		print "getUserMovieRat"
	def delete_all_ratings(self):
		print "deleteRats"



