#include "VerifyPacket.h"
#include "PacketTypes.h"

void VerifyPacket::send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to)
{
	RakNet::BitStream bsOut;

	bsOut.Write((RakNet::MessageID)VERIFY_ACCOUNT);
	
	//Very simple packet structure
	bsOut.Write(login);
	bsOut.Write(hash);
	//****************************

	by->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to, false);
};