#pragma once
#include "GameTask.h"
#include "Entity.h"

class UpdateEntityTask :
	public GameTask
{
private:
	Entity* _ent;
public:
	UpdateEntityTask(Entity*);
	~UpdateEntityTask();
	virtual void process() override;

};

