#pragma once
#include "stdafx.h"
#include "easylogging++.h"
#include "AuthPoolerPacket.h"
#include "ServVars.h"

void registerServer(RakNet::Packet *packet){
	LOG(INFO) << "Pooler accepted our connection!";
	poolerClient->setServerAddr(packet->systemAddress);
	AuthPoolerPacket p;
	p.send(poolerClient->getPeer(), packet->systemAddress);
	LOG(INFO) << "Sending auth packet";
}
