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

	void setPeer(RakNet::RakPeerInterface* i)
	{
		_peer = i;
	}

	RakNet::RakPeerInterface* getPeer(){
		return _peer;
	};

	NetworkListener* getListener(){
		return _listener;
	};

	void setThread(std::thread* trd)
	{
		_networkTrd = trd;
	};

	std::thread* getThread()
	{
		return _networkTrd;
	};

	void setRunning(bool r)
	{
		_networkRunning = r;
	}

	bool getRunning()
	{
		return _networkRunning;
	}

	map<RakNet::RakNetGUID, ConnectedClient>* getConnections()
	{
		return &_connections;
	}

	Server(NetworkListener * lis){
		this->_listener = lis;
	};

	static void startMainNetworkThread(Server*, int, int);

	~Server(){};
	
    void addClient(RakNet::RakNetGUID, ConnectedClient);
    
	bool hasClient(RakNet::RakNetGUID);
    
	ConnectedClient* getClient(RakNet::RakNetGUID);
	
	void removeClient(RakNet::RakNetGUID);

};

