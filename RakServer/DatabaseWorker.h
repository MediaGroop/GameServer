#pragma once
#include "Worker.h"

class DatabaseWorker : public  Worker
{
public:
	DatabaseWorker();
	
	~DatabaseWorker();
	
	virtual void init() override;
};

