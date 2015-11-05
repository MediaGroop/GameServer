#pragma once
#include "stdafx.h"
#include "ServVars.h"
#include "ClientState.h"

void handleCharSelect(RakNet::Packet* p)
{

	ConnectedClient* cc = mainServer->getClient(p->guid);
	if (cc != nullptr)
	{
		if (cc->getState() == VERIFIED){
			RakNet::BitStream bsIn(p->data, p->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			
			RakNet::RakString charName;
			bsIn.Read(charName);

			LOG(INFO) << "Character select:";
			LOG(INFO) << charName.C_String();

			RakNet::BitStream bs;
			bs.Write(cc->getAccId());
			bs.Write(charName);

			databaseWorker->callRPC("lpe", &bs);
		}
	}
};