#include "Server.h"
#include "easylogging++.h"
#include "NetworkListener.h"
#include "ConfigLoader.h"

void Server::startMainNetworkThread(Server* instance, int port, int maxPlayers){
	instance->setPeer(RakNet::RakPeerInterface::GetInstance());
	RakNet::Packet *packet;

	RakNet::SocketDescriptor sd(port, 0);
	instance->getPeer()->Startup(maxPlayers, &sd, 1);
	LOG(INFO) << "Starting the server...";
	instance->getPeer()->SetMaximumIncomingConnections(maxPlayers);
	LOG(INFO) << "Server has been started! Listening for conections...";
	instance->setRunning(true);
	while (instance->getRunning())
	{
		Sleep(1);
		for (packet = instance->getPeer()->Receive(); packet; instance->getPeer()->DeallocatePacket(packet), packet = instance->getPeer()->Receive())
		{
			instance->getListener()->handle(packet);
		}
	}
	instance->getPeer()->Shutdown(10.0);
	RakNet::RakPeerInterface::DestroyInstance(instance->getPeer());
}

bool Server::hasClient(RakNet::RakNetGUID guid)
{
	if (getClient(guid) == nullptr)
		return false;
	return true;
}

ConnectedClient* Server::getClient(RakNet::RakNetGUID guid){
	for (map<RakNet::RakNetGUID, ConnectedClient>::iterator ii = this->_connections.begin(); ii != this->_connections.end(); ++ii)
	{
		if ((*ii).first == guid) {
			return &(*ii).second;
		}
	}
	return NULL;
}

void Server::addClient(RakNet::RakNetGUID guid, ConnectedClient cl)
{
	this->_connections.insert(pair<RakNet::RakNetGUID, ConnectedClient>(guid, cl));
}

void Server::removeClient(RakNet::RakNetGUID guid)
{
	for (map<RakNet::RakNetGUID, ConnectedClient>::iterator ii = this->_connections.begin(); ii != this->_connections.end(); ++ii)
	{
		if ((*ii).first == guid) {
			this->_connections.erase((*ii).first);
			return;
		}
	}
	LOG(INFO) << "There's no client with given guid!";
}
