#pragma once
#include "Worker.h"

class PhysicsWorker :
	public Worker
{
public:
	PhysicsWorker();

	~PhysicsWorker();
	
	virtual void init() override;
};

