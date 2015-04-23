#John F. Lake, Jr. 
#Home listens on port 9001 for a client (from work)

from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class Command(LineReceiver):
	def __init__(self, data):
		self.data = data
	def connectionMade(self):
		print "Command Connected!"
	def lineReceived(self, line):
		self.sendLine(line)
		print line
	def sendData(self):
		self.sendLine("data");

class CommandFactory(Factory):
	def __init__(self):
		self.data = {}
		self.comProt = Command(self.data)
	def buildProtocol(self, addr):
		return self.comProt
	def getProt(self):
		return self.comProt

class Client(LineReceiver):
	def __init__(self, data):
		self.data = data
	def connectionMade(self):
		print "SSH connected"
		#need command factor to send message
		cf.getProt().sendData()
		
	def lineReceived(self, line):
		self.sendLine(line)
		print line

class ClientFactory(Factory):
	def __init__(self):
		self.data = {}
		self.clProt = Client(self.data)
	def buildProtocol(self, addr):
		return self.clProt

	def getProt(self):
		return self.clProt


cf = CommandFactory()

clf = ClientFactory()


#Listen for the work command connection
reactor.listenTCP(9001, cf)
reactor.listenTCP(9002, clf)

reactor.run()










