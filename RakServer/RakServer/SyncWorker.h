#pragma once
#include "Worker.h"
class SyncWorker :
	public Worker
{
public:
	SyncWorker(RakNet::RPC4* rpc);
	~SyncWorker();
};

