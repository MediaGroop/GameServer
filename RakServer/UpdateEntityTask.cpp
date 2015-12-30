#include "UpdateEntityTask.h"
#include "UpdateEntitySignal.h"
#include "ServVars.h"
#include "Entity.h"

UpdateEntityTask::UpdateEntityTask(Entity* e) : _ent(e)
{
}


UpdateEntityTask::~UpdateEntityTask()
{
}

//UPDATING ONLY FROM PHYSICS WORKER
void UpdateEntityTask::process(){
	//Updating us to avatar
	_ent->SignalController(new UpdateEntitySignal(_ent));
	//Updating us to the near clients
	std::vector<Entity*>* es = _ent->getNear();
	for (std::vector<Entity*>::iterator it = es->begin(); it != es->end(); ++it){
		_ent->updateTo(*it);
		RakNet::BitStream bs;
		bs.Write(_ent->getId());
		bs.Write(_ent->getBodyId());
		bs.Write(_ent->getX());
		bs.Write(_ent->getY());
		bs.Write(_ent->getZ());
		syncWorker->callRPC("ue", &bs);
	}
};
