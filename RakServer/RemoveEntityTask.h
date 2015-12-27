#pragma once
#include "GameTask.h"
#include "World.h"

class RemoveEntityTask :
	public GameTask
{
private:
	World* world;
	int from, whom;
public:
	RemoveEntityTask(World*, int, int);
	~RemoveEntityTask();
	virtual void process() override;
};

