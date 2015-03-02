#John F. Lake, Jr. 
#Web Service Primer

import requests
import json


class _webservice_primer:

	def __init__(self,apikey):
		print "Initializing."
		self.API_KEY = apikey
		self.SITE_URL = 'heep://student00.cse.nd.edu:40001'
		self.MOVIES_URL = self.SITE_URL + '/movies/'
		self.RESET_URL = self.SITE_URL + '/reset/'

	def get_movie(self,movie_id):
		print "Getting movie %s" % movie_id
	def set_movie_title(self,movie_id,title):
		print "Setting the title of %s as %s" % (movie_id,title)

	def delete_movie(self,movie_id):
		print "deleting %s" % movie_id
	def reset_movie(self,movie_id):
		print "Resetting %s" % movie_id


if __name__ == "__main__":
	MID = 1

