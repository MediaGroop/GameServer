#pragma once
#include "stdafx.h"
#include "ConnectedClient.h"
#include "ServVars.h"

void onLoadWorld(RakNet::Packet* p)
{
	ConnectedClient* cc = mainServer->getClient(p->guid);
	if (cc != nullptr)
	{
		//First login
		if (cc->getState() == VERIFIED){
			cc->get_controlled_unit()->addNear(cc->get_controlled_unit()); // Adding itself
		}
		//World changing
		if (cc->getState() == PLAYING)
		{
			//TODO: ????
		}
	}
}