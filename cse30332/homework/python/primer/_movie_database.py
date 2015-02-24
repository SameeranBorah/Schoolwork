#John F. Lake, Jr. 
#Python Primer





class _movie_database:

	def __init__(self):
		#Movies will have the MID as the first
		self.movies = {}
		self.users = {}
		self.ratings = {}
		self.avg_ratings = {}




	# Loads in a movies file
	def load_movies(self,movie_file):
		self.movies = {}
		movieFile = open(movie_file)
		for line in movieFile:
			
			movieInfo = line.rstrip('\n').split("::")
			self.movies[movieInfo[0]] = []
			self.movies[movieInfo[0]] = movieInfo
			self.ratings[movieInfo[0]] = {}
		

	#Gets the movie at movie id (mid) from the movie dictionary
	def get_movie(self,mid):
		if str(mid) in self.movies.keys():
			mo = []
			mo = self.movies[str(mid)]
			print mo
			return mo[1:]
		else:
			return None
		

	#Simply returns all of the movie IDs:
	def movies(self):
		return self.movies.keys()

	#Set a movie to have specific information: 
	def set_movie(self,mid,info):
		input = []
		input.append(mid)
		input.append(info[0])
		input.append(info[1])
		self.movies[str(mid)] = input

	#Remove a movie from the dictionary:
	def delete_movie(self,mid):
		if str(mid) in self.movies.keys():
			del self.movies[str(mid)]

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
	def get_user(self,uid):
		if str(uid) in self.users.keys():
			u = []
			u = self.users[str(uid)]
			return u[1:]
		else:
			return None

	#Get all of the user ids in a list: 
	def get_users(self):
		return self.users.keys()

	#Set a user to have specific information:
	def set_user(self,uid, info):
		input = []
		input.append(uid)
		input.append(info[0])
		input.append(info[1])
		input.append(info[2])
		input.append(info[3])
		self.users[str(uid)] = input


	#Delete a particular user: 
	def delete_user(self,uid):
		if str(uid) in self.users.keys():
			del self.users[str(uid)]


	#Load in the ratings from a file
	def load_ratings(self,ratings_file):
		ratFile = open(ratings_file)
		for line in ratFile:
			r = line.split("::")
			
			#r[1] is the movie ID, and r[0] is the user ID
			self.ratings[r[1]][r[0]] = r[2]


		

	#Get the average rating for a particular movie:
	def get_rating(self,mid):
		#If the movie exists: 
		if str(mid) in self.ratings.keys():
			avgRating = 0
			num = 0

			#If the ratings entry is empty, then there aren't any ratings. 
			if self.ratings[str(mid)].keys() == {}:
				print "No ratings for this movie."

			#Otherwise, calculate the average ranking: 
			else:

				#For each user that has rated this movie, add their rating and average all of them
				for user in self.ratings[str(mid)].keys():
					avgRating = avgRating + int(self.ratings[str(mid)][user])
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
		for mov in self.movies.keys():
			r = self.get_rating(mov)
			self.avg_ratings[mov] = r
		highestNum = 0
		lowestMid = 0
		for mid in self.avg_ratings.keys():

			if float(self.avg_ratings[str(mid)]) > highestNum: 
				highestNum = float(self.avg_ratings[str(mid)])
				lowestMid = int(mid)
			elif float(self.avg_ratings[str(mid)]) == highestNum: 
				if int(mid) < lowestMid:
					lowestMid = int(mid)
	
		return lowestMid	
			
	def set_user_movie_rating(self,uid,mid,rating):
		if str(mid) in self.ratings.keys():
			 self.ratings[str(mid)][str(uid)] = int(rating)
	def get_user_movie_rating(self,uid,mid):
		if str(mid) in self.ratings.keys():
			if str(uid) in self.ratings[str(mid)].keys():
				return int(self.ratings[str(mid)][str(uid)])
	def delete_all_ratings(self):
		self.ratings = {}



