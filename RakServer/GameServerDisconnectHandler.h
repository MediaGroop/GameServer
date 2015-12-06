#pragma once
#include "stdafx.h"
#include "easylogging++.h"
#include "ServVars.h"


void handledisconn(RakNet::Packet *packet){
	ConnectedClient* cc = mainServer->getClient(packet->guid);
	if (cc != nullptr)
	{
		cc->onDisconnect();
		mainServer->removeClient(packet->guid);
	}
	LOG(INFO) << "Client disconnected...";
};