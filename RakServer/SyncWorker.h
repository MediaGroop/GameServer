#pragma once
#include "Worker.h"
class SyncWorker :
	public Worker
{
public:
	SyncWorker();
	~SyncWorker();
	virtual void init() override;
};

