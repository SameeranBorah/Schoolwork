#John F. Lake, Jr. 
#CSE30332
#This can run on any machine (ideally student01 though)


#PORTS:
#9321: Command connection
#9323: Data connection
#22: SSH Connection (connects to student03)


from twisted.internet.protocol import Factory
from twisted.internet.protocol import ClientFactory
from twisted.protocols.basic import LineReceiver
from twisted.internet.protocol import Protocol
from twisted.internet import reactor

#SSH Protocol
class SSH(LineReceiver):
	#Forward data to data connection
	def dataReceived(self,data):
		df.getProt().sendData(data)
	#Send data along SSH connection
	def sendData(self,data):
		self.transport.write(data)
	
#Factory for SSH connection
class SSHFactory(ClientFactory):
	def __init__(self):
		self.prot = SSH()
	def buildProtocol(self,addr):
		return self.prot
	def getProt(self):
		return self.prot
		
#Data protocol
class Data(LineReceiver):
	def connectionMade(self):
		reactor.connectTCP('student03.cse.nd.edu',22,ssh)
	#Forward from data to ssh connection: 
	def dataReceived(self,data):
		ssh.getProt().sendData(data)
	#Send data along data connection
	def sendData(self,data):
		self.transport.write(data)

#Factory for Data connection
class DataFactory(ClientFactory):
	def __init__(self):
		self.prot = Data()
	def buildProtocol(self,addr):
		return self.prot
	def getProt(self):
		return self.prot

#Command protocol
class Command(Protocol):
	def dataReceived(self,data):
		#if they send "data", connect to data port
		if data == "data\r\n":
			reactor.connectTCP('student00.cse.nd.edu',9323,df)
#Factory for command connection
class CommandFactory(ClientFactory):
	def buildProtocol(self,addr):
		return Command()

#Make the necessary factories
ssh = SSHFactory()
df = DataFactory()

#Connect on the command port
reactor.connectTCP('student00.cse.nd.edu',9321,CommandFactory())
reactor.run()
