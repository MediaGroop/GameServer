#include "PhysicsWorker.h"
#include "ConfigLoader.h"
#include "PhysicsWorkerConnectHandler.h"
#include "PhyWorkConnFailHanler.h"

PhysicsWorker::PhysicsWorker(RakNet::RPC4* r) : Worker(r)
{
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, pWorkerConnected);
	addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailPhyConnect);
};

PhysicsWorker::~PhysicsWorker()
{
	LOG(INFO) << "PWorker dctor";
};
