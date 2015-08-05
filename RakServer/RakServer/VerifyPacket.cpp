#include "VerifyPacket.h"
#include "PacketTypes.h"

void VerifyPacket::send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to)
{
	RakNet::BitStream bsOut;

	bsOut.Write((RakNet::MessageID)VERIFY_ACCOUNT);

	//Very simple packet structure
	bsOut.Write(login);
	for (int i = 0; i < 20; ++i)
		bsOut.Write(hash[i]);
	//****************************

	by->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to, false);
};