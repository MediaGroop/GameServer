#include "RemoveEntityTask.h"


RemoveEntityTask::RemoveEntityTask(World* w, int f, int wh) : world(w), from(f), whom(wh)
{
}


RemoveEntityTask::~RemoveEntityTask()
{
}

void RemoveEntityTask::process(){
	Entity* fromE = world->getEntity(from);
	Entity* whomE = world->getEntity(whom);
	if (fromE != nullptr && whomE != nullptr)
	{
		fromE->removeNear(whomE);
	}
};