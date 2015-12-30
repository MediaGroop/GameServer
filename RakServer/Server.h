#pragma once
#include "stdafx.h"
#include <thread>
#include "ConnectedClient.h"
#include <map>
#include "NetworkListener.h"
using namespace std;

class Server
{
private:
	RakNet::RakPeerInterface *_peer;
	NetworkListener* _listener;

	std::thread *_networkTrd;
	bool _networkRunning = false;

	map<RakNet::RakNetGUID, ConnectedClient> _connections;
public:

	void setPeer(RakNet::RakPeerInterface* i);

	RakNet::RakPeerInterface* getPeer();

	NetworkListener* getListener();

	void setThread(std::thread* trd);

	std::thread* getThread();

	void setRunning(bool r);

	bool getRunning();

	map<RakNet::RakNetGUID, ConnectedClient>* getConnections();

	Server(NetworkListener * lis);

	static void startMainNetworkThread(Server*, int, int);

	~Server(){};
	
    void addClient(RakNet::RakNetGUID, ConnectedClient);
    
	bool hasClient(RakNet::RakNetGUID);
    
	ConnectedClient* getClient(RakNet::RakNetGUID);
	
	void removeClient(RakNet::RakNetGUID);

};

