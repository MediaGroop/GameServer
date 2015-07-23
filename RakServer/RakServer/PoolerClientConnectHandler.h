#pragma once
#include "stdafx.h"
#include "easylogging++.h"
#include "AuthPoolerPacket.h"
#include "ServVars.h"

void registerServer(RakNet::Packet *packet){
	LOG(INFO) << "Pooler accepted our connection!";
	AuthPoolerPacket p;
	p.send(poolerClient->peer, packet->systemAddress);
	LOG(INFO) << "Sending auth packet";
}
