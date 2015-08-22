#pragma once
#include "stdafx.h"
#include "ServVars.h"

void workerConnected(RakNet::Packet* p){
	LOG(INFO) << "Database worker is ready!";
	databaseWorker->getClient()->setServerAddr(p->systemAddress);
	RakNet::BitStream s;
	databaseWorker->callRPC("lw", &s);
};