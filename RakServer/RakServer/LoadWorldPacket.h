#pragma once
#include "Packet.h"
#include "PacketTypes.h"
#include <map>

class LoadWorldPacket: public Packet{
private:
	RakNet::RakString _name;

public:
	
	LoadWorldPacket(RakNet::RakString name): _name(name){};
	
	~LoadWorldPacket(){};
	
	virtual void send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override {
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)LOAD_WORLD);
		bsOut.Write(_name);
		by->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to, false);
	};
};
