#include "PhysicsWorker.h"
#include "ConfigLoader.h"
#include "PhysicsWorkerConnectHandler.h"
#include "PhyWorkConnFailHanler.h"


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
		}
	}
};

PhysicsWorker::PhysicsWorker(RakNet::RPC4* r) : Worker(r)
{
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, pWorkerConnected);
	addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailPhyConnect);
	addHandler((short)UPDATE_ENTITY, onUpdateEnt);

};

PhysicsWorker::~PhysicsWorker()
{
	LOG(INFO) << "PWorker dctor";
};
