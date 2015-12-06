#pragma once
#include "Worker.h"

class DatabaseWorker : public  Worker
{
public:
	DatabaseWorker(RakNet::RPC4* r);
	~DatabaseWorker();
};

