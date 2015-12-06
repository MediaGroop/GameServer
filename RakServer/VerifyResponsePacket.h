#pragma once
#include "Packet.h"
class VerifyResponsePacket :
	public Packet
{
public:
	unsigned char result;
	VerifyResponsePacket(unsigned char r) : result(r){};
	~VerifyResponsePacket(){};
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};

