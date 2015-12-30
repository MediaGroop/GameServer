#pragma once
#include "stdafx.h"
#include "NetworkListener.h"
#include <thread>

class Client
{
private:
	NetworkListener* _listener;

	RakNet::SystemAddress _serverAddress;

	bool _running = false;

	RakNet::RakPeerInterface *_peer;

	std::thread* _networkTrd;

	static void startNetworkTrd(Client*, std::string, int);

public:

	bool getRunning();

	void setRunning(bool r);

	void setPeer(RakNet::RakPeerInterface* i);

	void setServerAddr(RakNet::SystemAddress a);

	void setThread(std::thread* trd);

	RakNet::SystemAddress* getServerAddr();

	std::thread* getThread();

	RakNet::RakPeerInterface* getPeer();

	NetworkListener* getListener();

	Client(NetworkListener * l);

	~Client();

	Client();

	void connect(std::string host, int port);

};

