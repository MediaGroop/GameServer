#pragma once
#include "stdafx.h"
#include <string.h>

class Packet{
public:
	Packet(){};
	~Packet(){};
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to){};
};