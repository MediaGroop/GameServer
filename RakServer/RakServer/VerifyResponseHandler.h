#pragma once
#include "stdafx.h"
#include "VerifyResponsePacket.h"

void verifyResultHandler(RakNet::Packet *packet){
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	RakNet::RakString hash;
	unsigned char response;

	bsIn.Read(response);
	bsIn.Read(hash);

	for (map<RakNet::RakNetGUID, ConnectedClient>::iterator ii = mainServer->_connections.begin(); ii != mainServer->_connections.end(); ++ii)
	{
		if ((*ii).second.hash == hash)
		{
			VerifyResponsePacket p(response);

			//dynamic hash equals
			switch(response)
			{
				case 0:
					p.send(mainServer->peer, (*ii).second.addr);
					break;
				case 1:
					p.send(mainServer->peer, (*ii).second.addr);
					mainServer->peer->CloseConnection((*ii).second.addr, true);//disconnect client
					mainServer->removeClient((*ii).second.addr.rakNetGuid);
					(*ii).second.onDisconnect();
					break;
			}
		}
	}
};
