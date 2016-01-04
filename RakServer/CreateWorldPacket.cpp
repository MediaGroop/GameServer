#include "CreateWorldPacket.h"
#include "PhysicsWorkerPackets.h"

CreateWorldPacket::CreateWorldPacket(int i, float x, float y, float z) : _id(i), _x(x), _y(y), _z(z)
{
}


CreateWorldPacket::~CreateWorldPacket()
{
}

void CreateWorldPacket::send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to){
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)CREATE_WORLD_P);
	bsOut.Write(_id);
	bsOut.Write(_x);
	bsOut.Write(_y);
	bsOut.Write(_z);
	by->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to, false);

};
