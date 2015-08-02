#pragma once
#include "stdafx.h"
#include "ServVars.h"
#include "easylogging++.h"

void handledisconn(RakNet::Packet *packet){
	ConnectedClient* cc = mainServer->getClient(packet->guid);
	if (cc != nullptr)
	{
		mainServer->removeClient(packet->guid);
		cc->onDisconnect();
	}
	LOG(INFO) << "Client disconnected...";
};