#pragma once
#include "stdafx.h"
#include "ServVars.h"
#include "ClientState.h"
#include "LoadWorldPacket.h"

void handleCharSelect(RakNet::Packet* p)
{

	LOG(DEBUG) << "Character selection packet!";
	ConnectedClient* cc = mainServer->getClient(p->guid);
	if (cc != nullptr)
	{
		if (cc->getState() == VERIFIED){
			LOG(DEBUG) << "Account are verified, proceed...";
			RakNet::BitStream bsIn(p->data, p->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			RakNet::RakString charName;
			bsIn.Read(charName);

			LOG(INFO) << "Character select:";
			LOG(INFO) << charName.C_String();

			cc->setChar(charName);

			RakNet::BitStream bs;
			bs.Write(cc->getAccId());
			bs.Write(charName);

			//Loading da entity...
			databaseWorker->callRPC("lpe", &bs); // Database worker will return loaded entity and invoke load world func through RPC
		}
	}
};