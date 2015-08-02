#pragma once
#include "stdafx.h"
#include "Packet.h"

class VerifyPacket : public Packet
{
public:
	RakNet::RakString login;
	RakNet::RakString hash;
	VerifyPacket(RakNet::RakString l, RakNet::RakString h) : login(l), hash(h){};
	~VerifyPacket(){};
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};