import cherrypy
from _movie_database import _movie_database
import json


class Users(object):

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
		usr = self.myDB.get_user(id)
		if usr is None:
			output['result'] = 'error'
			output['message'] = 'key not found'
		else:
			output['id'] = id
			output['gender'] = usr[0]
			output['age'] =  usr[1]
			output['occupation'] = usr[2]
			output['zipcode'] = usr[3]

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
			info['id'] = int(key)
			info['zipcode'] = usr[3]
			info['age'] =  usr[1]
			info['gender'] = usr[0]
			info['occupation'] = usr[2]
			if usr is not None:
				output['users'].append(info)
		return json.dumps(output,encoding = 'latin-1')

	def POST(self):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		if v['apikey'] == self.API_KEY:
			info = []
			info.append(v['gender'])
			info.append(v['age'])
			info.append(v['occupation'])
			info.append(v['zipcode'])
			userId = self.myDB.add_user(info)
			output['id'] = userId
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')

	def DELETE(self,id):
		
		v = json.loads(cherrypy.request.body.fp.read())
		output = {'result':'success'}
		if v['apikey'] == self.API_KEY:
			self.myDB.delete_user(id)
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')

	def DELETE_ALL(self):
		output = {'result':'success'}

		v = json.loads(cherrypy.request.body.fp.read())
		keys = self.myDB.get_users()
		if str(v['apikey']) == self.API_KEY:
			for key in keys:
				self.myDB.delete_user(key)
		else:
			output['result'] = 'failure'


		return json.dumps(output,encoding = 'latin-1')

		
