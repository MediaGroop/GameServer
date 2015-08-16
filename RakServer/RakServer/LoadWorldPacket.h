#pragma once
#include "stdafx.h"
#include "Packet.h"

class LoadWorldPacket: public Packet{
public:
	LoadWorldPacket(){};
	~LoadWorldPacket(){};
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};
