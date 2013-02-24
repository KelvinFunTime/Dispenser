from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor


class IphoneChat(Protocol):
	latestData = "Full"
	
	def connectionMade(self):
		print "Connection made"
		self.factory.clients.append(self)
	
	def connectionLost(self, reason):
	    self.factory.clients.remove(self)
	
	def dataReceived(self, data):
		a = data.split(':')
		if len(a) > 1:
			command = a[0]
			content = a[1]
			
			msg = ""
		if command == "SetWaterLevel":
			self.latestData = content
			msg = "Data received"
					
		elif command == "GetWaterLevel":
			msg = self.latestData

		print "Sending message: " + msg
            
		for c in self.factory.clients:
			c.message(msg)
    
	def message(self, message):
		self.transport.write(message)


factory = Factory()
factory.protocol = IphoneChat
factory.clients = []

reactor.listenTCP(8080, factory)
print "Server started"
reactor.run()

