#pragma once
#include "Worker.h"
class PhysicsWorker :
	public Worker
{
public:
	PhysicsWorker(RakNet::RPC4*);
	~PhysicsWorker();
};

