import cherrypy
from _movie_database import _movie_database
import json


class Users(object):

	@cherrypy.tools.json_in()
	def __init__(self):
		self.API_KEY = 'AAAAAAAB'
		self.myDB = _movie_database()
		self.myDB.delete_all_ratings()
                self.myDB.load_movies('ml-1m/movies.dat')
                self.myDB.load_users('ml-1m/users.dat')
                self.myDB.load_ratings('ml-1m/ratings.dat')
		self.myDB.load_posters('images.dat')

	
	
	def GET(self,id=None):
		output = {'result':'success'}
		usr = self.myDB.get_usr(id)
		if mov is None:
			output['result'] = 'error'
			output['message'] = 'key not found'
		else:
			output['id'] = id
			output['zipcode'] = usr[2]
			output['age'] =  usr[1]
			output['gender'] = usr[0]
			into['occupation'] = usr[3]

		return json.dumps(output,encoding = 'latin-1')

	def PUT(self,id=None):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		info = []
		info.append(v['gender'])
		info.append(v['age'])
		info.append(id)
		info.append(v['zipcode'])
		info.append(v['occupation'])
		self.myDB.set_user(id,info)
		return json.dumps(output,encoding = 'latin-1')
	def GET_ALL(self):
		output = {'result':'success'}
		output['users'] = []
		for key in self.myDB.get_users():
			usr = self.myDB.get_user(key)
			info = {}
			info['id'] = key
			info['zipcode'] = usr[2]
			info['age'] =  usr[1]
			info['gender'] = usr[0]
			into['occupation'] = usr[3]
			if usr is not None:
				output['users'].append(info)
		return json.dumps(output,encoding = 'latin-1')

	def POST(self):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		info = []
		info.append(v['title'])
		info.append(v['genres'])
		self.myDB.set_movie(id,info)
		return json.dumps(output,encoding = 'latin-1')


	def DELETE(self,id):
		
		v = json.loads(cherrypy.request.body.fp.read())
		output = {'result':'success'}
		print v['apikey']
		print self.API_KEY
		if v['apikey'] == self.API_KEY:
			self.myDB.delete_user(id)
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')

	def DELETE_ALL(self):
		output = {'result':'success'}

		v = json.loads(cherrypy.request.body.fp.read())
		keys = self.myDB.get_users()
		print v['apikey']
		print self.API_KEY
		if str(v['apikey']) is self.API_KEY:
			for key in keys:
				self.myDB.delete_user(key)
		else:
			output['result'] = 'failure'

		return json.dumps(output,encoding = 'latin-1')

		
