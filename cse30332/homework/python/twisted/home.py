#John F. Lake, Jr. 
#Home listens on port 9001 for a client (from work)

from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver
from twisted.internet import reactor

class Home(LineReceiver):
	def __init__(self, data):
		self.data = data

	def connectionMade(self):
		print "CONNECTED!"

	def lineReceived(self, line):
		self.sendLine(line)
		print line


class HomeFactory(Factory):
	def __init__(self):
		self.data = {}
	def buildProtocol(self, addr):
		return Home(self.data)


reactor.listenTCP(9001, HomeFactory())
reactor.run()










