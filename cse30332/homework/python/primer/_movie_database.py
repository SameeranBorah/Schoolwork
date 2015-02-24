#John F. Lake, Jr. 
#Python Primer
#This is a class with methods to construct a database for rating movies





class _movie_database:

	#Initialization method:
	def __init__(self):
		#Set movies, users, ratings, and avg_ratings to by empty dictionaries
		self.movies = {}
		self.users = {}
		self.ratings = {}
		self.avg_ratings = {}




	# Loads in a movies file
	def load_movies(self,movie_file):
		self.movies = {}
		movieFile = open(movie_file)
		for line in movieFile:

			#Remove the newline character: 
			movieInfo = line.rstrip('\n').split("::")

			#Set the movie info for that particular movie id (which is movieInfo[0])
			self.movies[movieInfo[0]] = []
			self.movies[movieInfo[0]] = movieInfo

			#Set the ratings for that particular movie to be an empty dictionary
			self.ratings[movieInfo[0]] = {}
		

	#Gets the movie at movie id (movieID) from the movie dictionary
	def get_movie(self,movieID):

		#If the movie ID 
		if str(movieID) in self.movies.keys():
			mo = []
			mo = self.movies[str(movieID)]
			return mo[1:]
		else:
			return None
		

	#Simply returns all of the movie IDs:
	def movies(self):
		return self.movies.keys()

	#Set a movie to have specific information: 
	def set_movie(self,movieID,info):
		input = []
		input.append(movieID)
		input.append(info[0])
		input.append(info[1])
		self.movies[str(movieID)] = input

	#Remove a movie from the dictionary:
	def delete_movie(self,movieID):
		if str(movieID) in self.movies.keys():
			del self.movies[str(movieID)]

	#Load in users from the users file
	def load_users(self,users_file):
		self.users = {}
		uFile = open(users_file)
		for line in uFile:
			userInfo = line.rstrip('\n').split("::")
			userInfo[2] = int(userInfo[2])
			userInfo[3] = int(userInfo[3])
			
			self.users[userInfo[0]] = []
			self.users[userInfo[0]] = userInfo

	#Get a particular user from their ID: 
	def get_user(self,userID):
		if str(userID) in self.users.keys():
			u = []
			u = self.users[str(userID)]
			return u[1:]
		else:
			return None

	#Get all of the user ids in a list: 
	def get_users(self):
		return self.users.keys()

	#Set a user to have specific information:
	def set_user(self,userID, info):
		input = []
		input.append(userID)
		input.append(info[0])
		input.append(info[1])
		input.append(info[2])
		input.append(info[3])
		self.users[str(userID)] = input


	#Delete a particular user: 
	def delete_user(self,userID):
		if str(userID) in self.users.keys():
			del self.users[str(userID)]


	#Load in the ratings from a file
	def load_ratings(self,ratings_file):
		ratFile = open(ratings_file)
		for line in ratFile:
			r = line.split("::")
			
			#r[1] is the movie ID, and r[0] is the user ID
			self.ratings[r[1]][r[0]] = r[2]


		

	#Get the average rating for a particular movie:
	def get_rating(self,movieID):
		#If the movie exists: 
		if str(movieID) in self.ratings.keys():
			avgRating = 0
			num = 0

			#If the ratings entry is empty, then there aren't any ratings. 
			if self.ratings[str(movieID)].keys() == {}:
				print "No ratings for this movie."

			#Otherwise, calculate the average ranking: 
			else:

				#For each user that has rated this movie, add their rating and average all of them
				for user in self.ratings[str(movieID)].keys():
					avgRating = avgRating + int(self.ratings[str(movieID)][user])
					num += 1

				if num == 0:
					return avgRating
				else: 
					avgRating/=(num*1.0)
					return avgRating
		else:
			return None


	#Returns the film with the highest rating: 
	def get_highest_rated_movie(self):

		#Loop to get all of the average ratings together in a list
		for mov in self.movies.keys():
			r = self.get_rating(mov)
			self.avg_ratings[mov] = r

		
		highestNum = 0
		lowestMid = 0

		#Go through each movie and find the best rated one.  Ties are broken by the lower movie ID
		for movieID in self.avg_ratings.keys():

			if float(self.avg_ratings[str(movieID)]) > highestNum: 
				highestNum = float(self.avg_ratings[str(movieID)])
				lowestMid = int(movieID)
			elif float(self.avg_ratings[str(movieID)]) == highestNum: 
				if int(movieID) < lowestMid:
					lowestMid = int(movieID)
	
		return lowestMid	
			

	#Set a particular movie rating for a user
	def set_user_movie_rating(self,userID,movieID,rating):
		if str(movieID) in self.ratings.keys():
			 self.ratings[str(movieID)][str(userID)] = int(rating)

	#Get a user's rating for a particular movie: 
	def get_user_movie_rating(self,userID,movieID):
		if str(movieID) in self.ratings.keys():
			if str(userID) in self.ratings[str(movieID)].keys():
				return int(self.ratings[str(movieID)][str(userID)])


	#Self-explanatory: 
	def delete_all_ratings(self):
		self.ratings = {}



