#John F. Lake, Jr. 
#Web Service Primer

import requests
import json


class _webservice_primer:

	def __init__(self,apikey):
		#print "Initializing."
		self.API_KEY = apikey
		self.SITE_URL = 'http://student00.cse.nd.edu:40001'
		self.MOVIES_URL = self.SITE_URL + '/movies/'
		self.RESET_URL = self.SITE_URL + '/reset/'

	def get_movie(self,movie_id):
		#print "Getting movie %s" % movie_id
		mid = str(movie_id)
		r = requests.get(self.MOVIES_URL + mid)
		resp = json.loads(r.content)
		return resp
	def set_movie_title(self,movie_id,title):
		#print "Setting the title of %s as %s" % (movie_id,title)
		movie = self.get_movie(movie_id)
		movie['title'] = title
		movie['apikey'] = self.API_KEY
		r = requests.put(self.MOVIES_URL + str(movie_id),data = json.dumps(movie))
	

	def delete_movie(self,movie_id):
		print "deleting %s" % movie_id
		mydata = {}
		mydata['apikey'] = self.API_KEY
		r = requests.delete(self.MOVIES_URL +str(movie_id),data = json.dumps(mydata))
		resp = json.loads(r.content)
		return resp
	

	def reset_movie(self,movie_id):
		#print "Resetting %s" % movie_id
		mydata = {}
		mydata['apikey'] = self.API_KEY
		r = requests.put(self.RESET_URL + str(movie_id),data = json.dumps(mydata))
		resp = json.loads(r.content)
		return resp
		


if __name__ == "__main__":
	MID = 42
	API_KEY = 'q902dt4F2X'
	ws = _webservice_primer(API_KEY)

	movie = ws.get_movie(MID)
	if movie['result'] == 'success':
		print "Title:\t%s" % movie['title']
	else:
		print "Error:\t%s" % movie['title']
		

