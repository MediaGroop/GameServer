#pragma once
#include "stdafx.h"
#include "ConnectedClient.h"
#include "ServVars.h"
void onLoadWorld(RakNet::Packet* p)
{
	ConnectedClient* cc = mainServer->getClient(p->guid);
	if (cc != nullptr)
	{
		if (cc->getState() == VERIFIED){

		}
	}
}