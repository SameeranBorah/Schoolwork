# John F. Lake, Jr. 
# CherryPy Assignment
# CSE 30332


#Import the resources
import Movies,Users,Ratings,Recommendations
from _movie_database import _movie_database
import cherrypy
import re,json



def start_service():


	#Make controller and dispatcher objects for all resources
	DB = _movie_database()
	mov = Movies.Movies(DB)
	usr = Users.Users(DB)
	rat = Ratings.Ratings(DB)
	rec = Recommendations.Recommendations(DB)
	dispatcher = cherrypy.dispatch.RoutesDispatcher()


	#MOVIES
	#GET:
	dispatcher.connect('mov_get', '/movies/:id',controller=mov,
				action = 'GET',conditions=dict(method=['GET']))
	dispatcher.connect('mov_get_all','/movies/',controller=mov, 
				action = 'GET_ALL',conditions=dict(method=['GET']))
	#PUT
	dispatcher.connect('mov_put','/movies/:id',controller=mov, 
				action = 'PUT',conditions=dict(method=['PUT']))
	#POST
	dispatcher.connect('mov_post','/movies/',controller=mov, 
				action = 'POST',conditions=dict(method=['POST']))
	#RESET
	dispatcher.connect('mov_res','/reset/:id',controller=mov, action = 'RESET',conditions=dict(method=['PUT']))
	dispatcher.connect('mov_res_all','/reset/',controller=mov,action = 'RESET_ALL',conditions=dict(method=['PUT']))

	#DELETE
	dispatcher.connect('mov_del','/movies/:id',controller=mov, 
				action = 'DELETE',conditions=dict(method=['DELETE']))
	dispatcher.connect('mov_del_all','/movies/',controller=mov, 
				action = 'DELETE_ALL',conditions=dict(method=['DELETE']))


	#USERS:
	
	#GET
	dispatcher.connect('usr_get', '/users/:id',controller=usr,
				action = 'GET',conditions=dict(method=['GET']))
	dispatcher.connect('usr_get_all','/users/',controller=usr, 
				action = 'GET_ALL',conditions=dict(method=['GET']))
	#PUT
	dispatcher.connect('usr_put','/users/:id',controller=usr, 
				action = 'PUT',conditions=dict(method=['PUT']))
	#POST
	dispatcher.connect('usr_post','/users/',controller=usr, 
				action = 'POST',conditions=dict(method=['POST']))

	#DELETE
	dispatcher.connect('usr_del','/users/:id',controller=usr, 
				action = 'DELETE',conditions=dict(method=['DELETE']))
	dispatcher.connect('usr_del_all','/users/',controller=usr, 
				action = 'DELETE_ALL',conditions=dict(method=['DELETE']))

	#RATINGS:

	dispatcher.connect('rat_get','/ratings/:id',controller=rat, 
				action = 'GET',conditions=dict(method=['GET']))
	#RECOMMENDATIONS:

	#DELETE
	dispatcher.connect('rec_del','/recommendations/',controller=rec, action = 'DELETE',conditions=dict(method=['DELETE']))

	#GET
	dispatcher.connect('rec_get', '/recommendations/:id',controller=rec,
				action = 'GET',conditions=dict(method=['GET']))
	#PUT
	dispatcher.connect('rec_put','/recommendations/:id',controller=rec, 
				action = 'PUT',conditions=dict(method=['PUT']))


	#Configuration
	conf = {'global': {'server.socket_host': 'student03.cse.nd.edu', 'server.socket_port':40041},
		'/'	: {'request.dispatch':dispatcher}}


	#Update the configuration and start the server
	cherrypy.config.update(conf)
	app = cherrypy.tree.mount(None,config=conf)
	cherrypy.quickstart(app)
	
if __name__ == '__main__':
	start_service()
