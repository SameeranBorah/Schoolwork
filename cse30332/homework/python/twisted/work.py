#John F. Lake, Jr. 
#CSE 30332
#This is the file that establishes the command connection
from twisted.internet.protocol import Factory
from twisted.internet.protocol import ClientFactory
from twisted.protocols.basic import LineReceiver
from twisted.internet.protocol import Protocol
from twisted.internet import reactor


class SSH(LineReceiver):
	def dataReceived(self,data):
		df.getProt().sendData(data)
	def sendData(self,data):
		self.transport.write(data)
	

class SSHFactory(ClientFactory):
	def __init__(self):
		self.prot = SSH()
	def buildProtocol(self,addr):
		return self.prot
	def getProt(self):
		return self.prot
		

class Data(LineReceiver):
	def connectionMade(self):
		reactor.connectTCP('student03.cse.nd.edu',22,ssh)

	def dataReceived(self,data):
		ssh.getProt().sendData(data)
	def sendData(self,data):
		self.transport.write(data)

class DataFactory(ClientFactory):
	def __init__(self):
		self.prot = Data()
	def buildProtocol(self,addr):
		return self.prot
	def getProt(self):
		return self.prot


class Command(Protocol):
	def dataReceived(self,data):
		#if they send "data", connect to data port
		if data == "data\r\n":
			reactor.connectTCP('student00.cse.nd.edu',9323,df)

class CommandFactory(ClientFactory):
	def buildProtocol(self,addr):
		return Command()

ssh = SSHFactory()
df = DataFactory()


#Connect on the command port
reactor.connectTCP('student00.cse.nd.edu',9321,CommandFactory())
reactor.run()
