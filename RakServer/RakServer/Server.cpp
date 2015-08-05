#include "Server.h"
#include "easylogging++.h"
#include "NetworkListener.h"
#include "ConfigLoader.h"

void Server::startMainNetworkThread(Server* instance, int port, int maxPlayers){
	instance->peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet *packet;

	RakNet::SocketDescriptor sd(port, 0);
	instance->peer->Startup(maxPlayers, &sd, 1);
	LOG(INFO) << "Starting the server...";
	instance->peer->SetMaximumIncomingConnections(maxPlayers);
	LOG(INFO) << "Server has been started! Listening for conections...";
	instance->networkRunning = true;
	while (instance->networkRunning)
	{
		Sleep(1);
		for (packet = instance->peer->Receive(); packet; instance->peer->DeallocatePacket(packet), packet = instance->peer->Receive())
		{
			instance->listener->handle(packet);
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(instance->peer);
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
