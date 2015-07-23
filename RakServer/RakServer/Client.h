#pragma once
#include "stdafx.h"
#include "NetworkListener.h"
#include <thread>

class Client
{
private:
	static void startNetworkTrd(Client*, std::string, int);
public:
	Client(NetworkListener * l){
		this->listener = l;
	};
	~Client(){};
	NetworkListener* listener;
	
	//RakNet::TCPInterface* sslClient;
	RakNet::SystemAddress serverAddress;

	RakNet::RakPeerInterface *peer;
	std::thread* networkTrd;
	bool running = false;
	void connect(std::string host, int port);

};

