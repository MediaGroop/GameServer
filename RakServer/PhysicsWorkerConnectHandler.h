#pragma once
#include "stdafx.h"
#include "ServVars.h"

void pWorkerConnected(RakNet::Packet* p)
{
	LOG(INFO) << "Physics worker is ready!";
	physicsWorker->getClient()->setServerAddr(p->systemAddress);
};