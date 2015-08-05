#pragma once
#include "stdafx.h"
#include "VerifyResponsePacket.h"
#include "Utils.h"
#include "easylogging++.h"

void verifyResultHandler(RakNet::Packet *packet){
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	unsigned char hash[20];
	unsigned char response;

	bsIn.Read(response);

	for (int i = 0; i < 20; ++i){
		bsIn.Read(hash[i]);
	}

	for (map<RakNet::RakNetGUID, ConnectedClient>::iterator ii = mainServer->_connections.begin(); ii != mainServer->_connections.end(); ++ii)
	{
		if (compareHashes((*ii).second.getHash(), hash))
		{
			VerifyResponsePacket p(response);
			//dynamic hash equals
			switch (response)
			{
			case 0:
				LOG(INFO) << "Verification success!";
				p.send(mainServer->peer, (*ii).second.getAddrOrGUID());
				break;
			case 1:
				LOG(INFO) << "Verification failed!";
				p.send(mainServer->peer, (*ii).second.getAddrOrGUID());
				mainServer->peer->CloseConnection((*ii).second.getAddrOrGUID(), true);//disconnect client
				(*ii).second.onDisconnect();
				mainServer->removeClient(mainServer->peer->GetGuidFromSystemAddress((*ii).second.getAddrOrGUID().systemAddress));
				(*ii).second.onDisconnect();
				break;
			}
		}
	}
};
