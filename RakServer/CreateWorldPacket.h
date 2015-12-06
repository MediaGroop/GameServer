#pragma once
#include "Packet.h"
/*
 Packet to create a world on physics worker
*/
class CreateWorldPacket :
	public Packet
{
private:
	int _id;
	float _x, _y, _z;
public:
	CreateWorldPacket(int, float, float, float);
	~CreateWorldPacket();
	void virtual send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};

