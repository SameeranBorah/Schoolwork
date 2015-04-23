#John F. Lake, Jr. 
#CSE 30332
#This is the file that establishes the command connection
from twisted.internet.protocol import Factory
from twisted.internet.protocol import ClientFactory
from twisted.internet.protocol import Protocol
from twisted.internet import reactor


class MyConn(Protocol):
	def dataReceived(self,data):
		print data
	def connectionMade(self):
		print "Connected!!!"
		self.transport.write("You've connected!")
	def connectionLost(self,data):
		print "lost 'em"

class MyConnFactory(ClientFactory):
	def buildProtocol(self,addr):
		return MyConn()


reactor.connectTCP('student00.cse.nd.edu',9001,MyConnFactory())
reactor.run()
