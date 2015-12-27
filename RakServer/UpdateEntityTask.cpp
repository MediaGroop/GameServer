#include "UpdateEntityTask.h"
#include "UpdateEntitySignal.h"

UpdateEntityTask::UpdateEntityTask(Entity* e) : _ent(e)
{
}


UpdateEntityTask::~UpdateEntityTask()
{
}

//UPDATING ONLY FROM PHYSICS WORKER
void UpdateEntityTask::process(){
	//Updating us to avatar
	_ent->SignalController(new UpdateEntitySignal(this));
	//Updating us to the near clients
	std::vector<Entity*>* es = _ent->getNear();
	for (std::vector<Entity*>::iterator it = es->begin(); it != es->end(); ++it){
		_ent->updateTo(*it);
		_ent->updateToSync();
	}
};
