#pragma once
#include "Packet.h"

class VerifyPacket : public Packet
{
public:
	RakNet::RakString login;
	unsigned char hash[20];
	VerifyPacket(RakNet::RakString l, unsigned char h[20]) : login(l){
		for (int i = 0; i < 20; ++i)
		{
			hash[i] = h[i];
		}
	};
	~VerifyPacket(){};
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};