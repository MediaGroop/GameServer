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

	bool getRunning()
	{
		return _running;
	};

	void setRunning(bool r)
	{
		this->_running = r;
	};

	void setPeer(RakNet::RakPeerInterface* i)
	{
		this->_peer = i;
	};

	void setServerAddr(RakNet::SystemAddress a)
	{
		this->_serverAddress = a;
	};

	void setThread(std::thread* trd)
	{
		this->_networkTrd = trd;
	};

	RakNet::SystemAddress* getServerAddr()
	{
		return &_serverAddress;
	};

	std::thread* getThread()
	{
		return _networkTrd;
	};

	RakNet::RakPeerInterface* getPeer(){
		return _peer;
	};

	NetworkListener* getListener(){
		return _listener;
	};

	Client(NetworkListener * l){
		this->_listener = l;
		setPeer(RakNet::RakPeerInterface::GetInstance());
	};

	~Client(){};
	
	void connect(std::string host, int port);

};

