#John F. Lake, Jr. 
#CSE30332
#This should run on student00

#PORTS:
#9321: Command connection
#9322: Client connection (when you call ssh on localhost of student00)
#9323: Data connection

#The command I use for SSH is "ssh localhost -p 9322 -l jlake2"

from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

#Data Protocol
class Data(LineReceiver):
	#Forward data to client connection
	def dataReceived(self,data):
		clf.getProt().sendData(data)
	#Send data along data connection
	def sendData(self,arg):
		self.transport.write(arg)

#Factory for Data connection
class DataFactory(Factory):
	def __init__(self):
		self.prot = Data()
	def buildProtocol(self, addr):
		return self.prot
	def getProt(self):
		return self.prot

#Client Protocol
class Client(LineReceiver):
	def connectionMade(self):
		#need command factory to send message
		cf.getProt().sendData("data")
	#Forward data to data connection: 
	def dataReceived(self,data):
		df.getProt().sendData(data)
	#Send data to client connection
	def sendData(self,data):
		self.transport.write(data)

#Factory for client connection
class ClientFactory(Factory):
	def __init__(self):
		self.clProt = Client()
	def buildProtocol(self, addr):
		return self.clProt
	def getProt(self):
		return self.clProt

#Command protocol
class Command(LineReceiver):
	#How we establish the data connection: send "data" over command connection and listen
	def sendData(self,arg):
		if arg == "data":
			self.sendLine(arg);
			reactor.listenTCP(9323, df)
		else:
			df.getProt().sendData(arg)

#Factory for command connection:
class CommandFactory(Factory):
	def __init__(self):
		self.comProt = Command()
	def buildProtocol(self, addr):
		return self.comProt
	def getProt(self):
		return self.comProt

#Make all of the factory objects: 
cf = CommandFactory()
df = DataFactory()
clf = ClientFactory()

#Listen for the work command connection
reactor.listenTCP(9321, cf)

#Listen for the client connection (which will be ssh)
reactor.listenTCP(9322, clf)
reactor.run()
