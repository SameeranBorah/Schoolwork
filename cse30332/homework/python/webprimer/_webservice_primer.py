#John F. Lake, Jr. 
#Web Service Primer

import requests
import json

class _webservice_primer:


	#Init function with all of the necessary information hardcoded (URLS for each resource.)
	def __init__(self,apikey):
		self.API_KEY = apikey
		self.SITE_URL = 'http://student00.cse.nd.edu:40001'
		self.MOVIES_URL = self.SITE_URL + '/movies/'
		self.RESET_URL = self.SITE_URL + '/reset/'


	#Get a movie with a particular ID.  You don't need the API Key to call a GET request
	def get_movie(self,movie_id):
		mid = str(movie_id)
		r = requests.get(self.MOVIES_URL + mid)
		resp = json.loads(r.content)
		return resp


	#Set a movie with a particular ID to have a specific title. Uses PUT 
	def set_movie_title(self,movie_id,title):
		movie = self.get_movie(movie_id)
		movie['title'] = title
		movie['apikey'] = self.API_KEY
		r = requests.put(self.MOVIES_URL + str(movie_id),data = json.dumps(movie))


	#Delete a movie:  Uses DELETE
	def delete_movie(self,movie_id):
		mydata = {}
		mydata['apikey'] = self.API_KEY
		r = requests.delete(self.MOVIES_URL +str(movie_id),data = json.dumps(mydata))
		resp = json.loads(r.content)
		return resp


	#Reset function: Uses PUT
	def reset_movie(self,movie_id):
		mydata = {}
		mydata['apikey'] = self.API_KEY
		r = requests.put(self.RESET_URL + str(movie_id),data = json.dumps(mydata))
		resp = json.loads(r.content)
		return resp


#Main function, with my movie ID and API key hard coded:
if __name__ == "__main__":
	MID = 42
	API_KEY = 'q902dt4F2X'
	ws = _webservice_primer(API_KEY)

	movie = ws.get_movie(MID)

	#If it's a success, print the movie that you retrieved. Otherwise, print the error.
	if movie['result'] == 'success':
		print "Title:\t%s" % movie['title']
	else:
		print "Error:\t%s" % movie['title']
		

