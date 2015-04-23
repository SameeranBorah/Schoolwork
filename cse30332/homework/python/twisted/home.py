#John F. Lake, Jr. 
#Home listens on port 9001 for a client (from work)
from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class Data(LineReceiver):
	def dataReceived(self,data):
		clf.getProt().sendData(data)
	def sendData(self,arg):
		self.transport.write(arg)
	

class DataFactory(Factory):
	def __init__(self):
		self.data = {}
		self.prot = Data()
	def buildProtocol(self, addr):
		return self.prot
	def getProt(self):
		return self.prot

class Client(LineReceiver):
	def __init__(self, data):
		self.data = data
	def connectionMade(self):
		#need command factor to send message
		cf.getProt().sendData("data")
	def dataReceived(self,data):
		df.getProt().sendData(data)
	def sendData(self,data):
		self.transport.write(data)

class ClientFactory(Factory):
	def __init__(self):
		self.data = {}
		self.clProt = Client(self.data)
	def buildProtocol(self, addr):
		return self.clProt
	def getProt(self):
		return self.clProt


class Command(LineReceiver):
	def __init__(self, data):
		self.data = data
	def lineReceived(self, line):
		self.sendLine(line)
	def sendData(self,arg):
		if arg == "data":
			self.sendLine(arg);
			#listen on data port 
			reactor.listenTCP(9323, df)
		else:
			df.getProt().sendData(arg)
class CommandFactory(Factory):
	def __init__(self):
		self.data = {}
		self.comProt = Command(self.data)
	def buildProtocol(self, addr):
		return self.comProt
	def getProt(self):
		return self.comProt



cf = CommandFactory()
df = DataFactory()
clf = ClientFactory()


#Listen for the work command connection
reactor.listenTCP(9321, cf)
reactor.listenTCP(9322, clf)

reactor.run()










