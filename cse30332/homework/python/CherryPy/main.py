#John F. Lake, Jr. 
#CherryPy Primer
import cherrypy
import re,json


class DictionaryController(object):
	def __init__(self):
		self.myd = dict()

	def GET(self,key):
		output = {'result':'success'}
		try:
			value = self.myd[key]
			output['value'] = value
		except KeyError as ex:
			output['result'] = 'error'
			output['message'] = 'key not found'

		key = str(key)
		output['key'] = key
		return json.dumps(output,encoding = 'latin-1')

	def GET_ALL(self):
		output = {'result':'success'}
		output['entries'] = self.myd
		return json.dumps(output,encoding = 'latin-1')

	def PUT(self,key):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		self.myd[key] = v['value']
		return json.dumps(output,encoding = 'latin-1')

	def POST(self,key,val):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		self.myd[key] = v['value']
		return json.dumps(output,encoding = 'latin-1')

	def DELETE(self,key):
		output = {'result':'success'}
		del self.myd[key]
		return json.dumps(output,encoding = 'latin-1')
	def DELETE_ALL(self):
		output = {'result':'success'}
		self.myd = dict()
		return json.dumps(output,encoding = 'latin-1')


def start_service():

	dictionaryController = DictionaryController()

	dispatcher = cherrypy.dispatch.RoutesDispatcher()


	#GET:
	dispatcher.connect('dict_get', '/dictionary/:key',controller=dictionaryController,
				action = 'GET',conditions=dict(method=['GET']))

	dispatcher.connect('dict_get_all','/dictionary/',controller=dictionaryController, 
				action = 'GET_ALL',conditions=dict(method=['GET']))

	#PUT
	dispatcher.connect('dict_put','/dictionary/:key',controller=dictionaryController, 
				action = 'PUT',conditions=dict(method=['PUT']))

	#POST
	dispatcher.connect('dict_post','/dictionary/',controller=dictionaryController, 
				action = 'POST',conditions=dict(method=['POST']))

	#DELETE
	dispatcher.connect('dict_del','/dictionary/:key',controller=dictionaryController, 
				action = 'DELETE',conditions=dict(method=['DELETE']))
	dispatcher.connect('dict_del_all','/dictionary/',controller=dictionaryController, 
				action = 'DELETE_ALL',conditions=dict(method=['DELETE']))

	#Configuration
	conf = {'global': {'server.socket_host': '127.0.0.1', 'server.socket_port':40041},
		'/'	: {'request.dispatch':dispatcher}}

	cherrypy.config.update(conf)
	app = cherrypy.tree.mount(None,config=conf)
	cherrypy.quickstart(app)
	
if __name__ == '__main__':
	start_service()
