#pragma once
#include "Packet.h"
class VerifyResponsePacket :
	public Packet
{
private:
	unsigned char result;
public:
	VerifyResponsePacket(unsigned char r) : result(r){};
	~VerifyResponsePacket(){};
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};

