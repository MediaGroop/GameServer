#include "SyncWorker.h"
#include "SyncWorkerConnectHandler.h"
#include "AddEntityTask.h"
#include "RemoveEntityTask.h"

void addNear(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int world_id, dest, target;
	bitStream->Read(world_id);
	bitStream->Read(dest);
	bitStream->Read(target);
	World* w = &(worlds.find(world_id)->second);
	if (w != nullptr)
	{
//		w->pushTask(new AddEntityTask(w, target, dest));
	}
};

void removeNear(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int world_id, dest, target;
	bitStream->Read(world_id);
	bitStream->Read(dest);
	bitStream->Read(target);
	World* w = &(worlds.find(world_id)->second);
	if (w != nullptr)
	{
//		w->pushTask(new RemoveEntityTask(w, target, dest));
	}
};

SyncWorker::SyncWorker(RakNet::RPC4* rpc) : Worker(rpc)
{

	registerFunction("an", addNear);
	registerFunction("rn", removeNear);
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, sWorkerConnected);
	//addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailPhyConnect);
}


SyncWorker::~SyncWorker()
{
}
