#include "PhysicsWorker.h"
#include "ConfigLoader.h"
#include "PhysicsWorkerConnectHandler.h"
#include "PhyWorkConnFailHanler.h"
#include "PacketTypes.h"
#include "UpdateEntityTask.h"

void onUpdateEnt(RakNet::Packet* p)
{
	int wid, id;
	float x, y, z;
	RakNet::BitStream bsIn(p->data, p->length, false);
	bsIn.Read(wid);
	bsIn.Read(id);
	bsIn.Read(x);
	bsIn.Read(y);
	bsIn.Read(z);

	World* w = &worlds.find(wid)->second;
	if (w != nullptr)
	{
		Entity* ent = w->getEntity(id);
		if (ent != nullptr)
		{
			ent->setXYZ(x, y, z);
			if (w != nullptr)
			{
				w->pushTask(new UpdateEntityTask(ent));
			}
		}
	}
};

PhysicsWorker::PhysicsWorker() : Worker()
{
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, pWorkerConnected);
	addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailPhyConnect);
	addHandler((short)UPDATE_ENTITY, onUpdateEnt);

};

PhysicsWorker::~PhysicsWorker()
{
	LOG(INFO) << "PWorker dctor";
};

void PhysicsWorker::init()
{
Worker::init();
}

