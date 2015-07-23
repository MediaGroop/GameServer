#pragma once
#include "stdafx.h"
#include <map>
#include <functional>

using namespace std;
class NetworkListener
{
public:
	NetworkListener(){};
	~NetworkListener(){};
	map<short, std::function<void(RakNet::Packet*)>> _handlers;
	void handle(RakNet::Packet*);
	void add(short, std::function<void(RakNet::Packet*)>);
};

