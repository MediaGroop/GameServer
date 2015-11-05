#pragma once
#include "stdafx.h"
#include "VerifyResponsePacket.h"
#include "Utils.h"
#include "easylogging++.h"
#include "ServVars.h"

void verifyResultHandler(RakNet::Packet *packet){
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	unsigned char hash[20];
	unsigned char response;
	RakNet::RakString accId;
	bsIn.Read(response);
	for (int i = 0; i < 20; ++i){
		bsIn.Read(hash[i]);
	}
	bsIn.Read(accId);
	
	for (std::map<RakNet::RakNetGUID, ConnectedClient>::iterator ii = mainServer->getConnections()->begin(); ii != mainServer->getConnections()->end(); ++ii)
	{
		if (compareHashes((*ii).second.getHash(), hash))
		{
			(*ii).second.setAccId(accId);
			VerifyResponsePacket p(response);
			//dynamic hash equals
			switch (response)
			{
			case 0:
				LOG(INFO) << "Verification success!";
				p.send(mainServer->getPeer(), (*ii).second.getAddrOrGUID());
				break;
			case 1:
				LOG(INFO) << "Verification failed!";
				p.send(mainServer->getPeer(), (*ii).second.getAddrOrGUID());
				mainServer->getPeer()->CloseConnection((*ii).second.getAddrOrGUID(), true);//disconnect client
				(*ii).second.onDisconnect();
				mainServer->removeClient(mainServer->getPeer()->GetGuidFromSystemAddress((*ii).second.getAddrOrGUID().systemAddress));
				(*ii).second.onDisconnect();
				break;
			}
			break;
		}
	}
};
