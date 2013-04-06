from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor

class DispenserServer(Protocol):
	tank1 = "Full"
	tank2 = "Full"

	def connectionMade(self):
		self.factory.clients.append(self)
	
	def connectionLost(self, reason):
		self.factory.clients.remove(self)
	
	def dataReceived(self, data):
		a = data.split(':')
		if len(a) > 1:
			command = a[0]
			content = a[1]
			msg = ""
			print "Command: " + command + " Content: " + content

		if command == "SetWaterLevel1":
			DispenserServer.tank1 = content
			msg = "Data received"
					
		elif command == "GetWaterLevel1":
			msg = DispenserServer.tank1

		if command == "SetWaterLevel2":
			msg = "Data received"
			DispenserServer.tank2 = content
					
		elif command == "GetWaterLevel2":
			msg = DispenserServer.tank2

		print "Sending message: " + msg
            
		for c in self.factory.clients:
			c.message(msg)
    
	def message(self, message):
		self.transport.write(message)


factory = Factory()
factory.protocol = DispenserServer
factory.clients = []

reactor.listenTCP(4321, factory)
print "Server started"
reactor.run()

