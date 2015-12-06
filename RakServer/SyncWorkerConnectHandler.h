#pragma once
#include "stdafx.h"
#include "ServVars.h"

void sWorkerConnected(RakNet::Packet* p)
{
	LOG(INFO) << "Sync worker is ready!";
	syncWorker->getClient()->setServerAddr(p->systemAddress);
};