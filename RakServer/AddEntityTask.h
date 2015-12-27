#pragma once
#include "GameTask.h"
#include "World.h"

class AddEntityTask :
	public GameTask
{
private:
	int toAdd, dest;
	World* world;
public:
	AddEntityTask(World*,int, int);
	~AddEntityTask();
	virtual void process() override;
};

