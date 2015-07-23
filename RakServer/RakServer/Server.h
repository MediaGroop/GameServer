#pragma once
#include "stdafx.h"
#include <thread>
#include "ConnectedClient.h"
#include <map>
#include "NetworkListener.h"
using namespace std;

class Server
{
public:
	Server(NetworkListener * lis){
		this->listener = lis;
	};

	static void startMainNetworkThread(Server*, int, int);

	~Server(){};

	RakNet::RakPeerInterface *peer;
	NetworkListener* listener;

	std::thread *networkTrd;
	bool networkRunning = false;

	map<RakNet::RakNetGUID, ConnectedClient> _connections;
	
    void addClient(RakNet::RakNetGUID, ConnectedClient);
    bool hasClient(RakNet::RakNetGUID);
    ConnectedClient* getClient(RakNet::RakNetGUID);
	void removeClient(RakNet::RakNetGUID);

};

