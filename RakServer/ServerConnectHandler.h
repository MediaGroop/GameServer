#pragma once
#include "stdafx.h"
#include "ConnectedClient.h"
#include "easylogging++.h"
#include "ServVars.h"

void handleconn(RakNet::Packet *packet){
	LOG(INFO) << "Incoming connection!";
	if (!mainServer->hasClient(packet->guid)) // Won't it always be true?
	{
		mainServer->addClient(packet->guid, *new ConnectedClient(packet->systemAddress));
	}
}