#John F. Lake, Jr. 
#CSE 30332
#This is the file that establishes the command connection
from twisted.internet.protocol import Factory
from twisted.internet.protocol import ClientFactory
from twisted.internet.protocol import Protocol
from twisted.internet import reactor


class Command(Protocol):
	def dataReceived(self,data):
		print data
	def connectionMade(self):
		print "Connected!!!"
		self.transport.write("This is from your work.!\r\n")
	def connectionLost(self,data):
		print "lost 'em"

class CommandFactory(ClientFactory):
	def buildProtocol(self,addr):
		return Command()


#Connect on the command port
reactor.connectTCP('student00.cse.nd.edu',9001,CommandFactory())
reactor.connectTCP
reactor.run()
