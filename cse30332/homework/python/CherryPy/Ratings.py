import cherrypy
from _movie_database import _movie_database
import json


class Ratings(object):

	@cherrypy.tools.json_in()
	def __init__(self,DB):
		self.API_KEY = 'AAAAAAAB'
		self.myDB = DB
		self.myDB.delete_all_ratings()
                self.myDB.load_movies('ml-1m/movies.dat')
                self.myDB.load_users('ml-1m/users.dat')
                self.myDB.load_ratings('ml-1m/ratings.dat')
		self.myDB.load_posters('images.dat')
	
	
	def GET(self,id=None):
		output = {'result':'success'}
		mov = self.myDB.get_rating(id)
		if mov is None:
			output['result'] = 'error'
			output['message'] = 'key not found'
		else:
			output['movie_id'] = int(id)
			output['rating'] = float(mov)

		return json.dumps(output,encoding = 'latin-1')

