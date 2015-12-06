#include "SyncWorker.h"
#include "SyncWorkerConnectHandler.h"

void addNear(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int world_id, dest, target;
	bitStream->Read(world_id);
	bitStream->Read(dest);
	bitStream->Read(target);
	World* w = &(worlds.find(world_id)->second);
	if (w != nullptr)
	{
		Entity* e = w->getEntity(dest);
		Entity* e2 = w->getEntity(target);
		if (e2 != nullptr && e != nullptr){
			// Add entity code
		}
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
		Entity* e = w->getEntity(dest);
		Entity* e2 = w->getEntity(target);
		if (e2 != nullptr && e != nullptr){
			// Remove entity code
		}
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
