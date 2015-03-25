#John F. Lake, Jr. 
#Handler for /recommendations/ and /recommendations/{userID}
import cherrypy
from _movie_database import _movie_database
import json


class Recommendations(object):

	@cherrypy.tools.json_in()

	#Setup data
	def __init__(self,DB):
		self.API_KEY = 'AAAAAAAB'
		self.myDB = DB
		self.myDB.delete_all_ratings()
                self.myDB.load_movies('ml-1m/movies.dat')
                self.myDB.load_users('ml-1m/users.dat')
                self.myDB.load_ratings('ml-1m/ratings.dat')
		self.myDB.load_posters('ml-1m/images.dat')

	
	
	#GET for /recommendations/{userID}
	def GET(self,id=None):
		output = {'result':'success'}
		mov = self.myDB.get_highest_unrated_movie(id)
		if mov is None:
			output['result'] = 'error'
			output['message'] = 'key not found'
		else:
			output['movie_id'] = int(mov)

		return json.dumps(output,encoding = 'latin-1')


	#PUT for /recommendations/{userID}
	def PUT(self,id=None):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		if v['apikey'] == self.API_KEY:
			info = []
			self.myDB.set_user_movie_rating(id,v['movie_id'],v['rating'])
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')

	#DELETE for /recommendations/
	def DELETE(self):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.fp.read())
		if v['apikey'] == self.API_KEY:
			self.myDB.delete_all_ratings()
		else:
			output['result'] = 'failure'

		return json.dumps(output,encoding = 'latin-1')
