#include "AddEntityTask.h"


AddEntityTask::AddEntityTask(World* w, int t, int s) : toAdd(t), dest(s), world(w)
{
}


AddEntityTask::~AddEntityTask()
{
}


void AddEntityTask::process(){
	Entity* destEnt = world->getEntity(dest);
	Entity* toAddEnt = world->getEntity(toAdd);
	if (destEnt != nullptr && toAddEnt != nullptr)
	{
		destEnt->addNear(toAddEnt);
	}
};