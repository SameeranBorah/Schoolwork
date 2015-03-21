import cherrypy
from _movie_database import _movie_database
import json


class Movies(object):


	def __init__(self):
		self.myDB = _movie_database()
		self.myDB.delete_all_ratings()
                self.myDB.load_movies('ml-1m/movies.dat')
                self.myDB.load_users('ml-1m/users.dat')
                self.myDB.load_ratings('ml-1m/ratings.dat')

	def GET(self,id=None):
		output = {'result':'success'}
		try:
			mov = self.myDB.get_movie(id)
			output['id'] = id
			output['genres'] = mov[1]
			output['title'] = mov[0]
		except KeyError as ex:
			output['result'] = 'error'
			output['message'] = 'key not found'

		return json.dumps(output,encoding = 'latin-1')

	def PUT(self,id=None):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		self.myDB[id] = v['value']
		return json.dumps(output,encoding = 'latin-1')

	def GET_ALL(self):
		output = {'result':'success'}
		output['movies'] = []
		for key in self.myDB.get_movies():
			mov = self.myDB.get_movie(key)
			info = {}
			info['id'] = key
			info['genres'] = mov[1]
			info['title'] = mov[0]
			#TODO: Implement images (need to update _movie_database.py)
			if mov is not None:
				output['movies'].append(info)
		return json.dumps(output,encoding = 'latin-1')

	def POST(self):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		self.myDB[v['key']] = v['value']
		return json.dumps(output,encoding = 'latin-1')


	def DELETE(self,id):
		output = {'result':'success'}
		del self.myDB[id]
		return json.dumps(output,encoding = 'latin-1')

	def DELETE_ALL(self):
		output = {'result':'success'}
		self.myDB = dict()
		return json.dumps(output,encoding = 'latin-1')

	def RESET(self,id):
		output = {'result':'success'}
		return json.dumps(output,encoding = 'latin-1')
	def RESET_ALL(self):
		output = {'result':'success'}
		self.myDB.__init__()
		self.myDB.load_movies('ml-1m/movies.dat')
		self.myDB.load_users('ml-1m/users.dat')
		self.myDB.load_ratings('ml-1m/ratings.dat')
		return json.dumps(output,encoding = 'latin-1')
		
