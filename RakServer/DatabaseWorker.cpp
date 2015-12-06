#include "DatabaseWorker.h"
#include "ConfigLoader.h"
#include "easylogging++.h"
#include "DatabaseWorkerHandler.h"
#include "DbWorkerConnFailHandler.h"
#include "World.h"
#include "ServVars.h"
#include "LoadWorldPacket.h"

extern std::map<int, World> worlds;

//Set Entity data to instance
void setEntityData(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{

	LOG(INFO) << "Setting entity data...";
	int wid, id;
	bitStream->Read(id);
	bitStream->Read(wid);
	bitStream->ResetReadPointer();

	World* w = &worlds.find(wid)->second;
	if (&w != nullptr)
	{
		Entity* e = w->getEntity(id);
		if (e != nullptr)
		{
			e->loadData(bitStream);
		}
	}
	LOG(INFO) << "Done!";
}

//Linking ConnectedClient with Entity instance
void setEntity(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{

	LOG(INFO) << "Setting entity to avatar";
	RakNet::RakString acc;
	int id, wid;

	bitStream->Read(acc);
	bitStream->Read(id);
	bitStream->Read(wid);

	World w = worlds.find(wid)->second;
	Entity* e = w.getEntity(id);
	if (&w != nullptr) {
		for (std::map<RakNet::RakNetGUID, ConnectedClient>::iterator ii = mainServer->getConnections()->begin(); ii != mainServer->getConnections()->end(); ++ii)
		{
			if ((*ii).second.getAccId() == acc) {
				LOG(INFO) << "Sending Load World packet...";
				(*ii).second.set_controlled_unit(e); // entity can be null
				LoadWorldPacket* pckt = new LoadWorldPacket(w.getName());
				pckt->send(mainServer->getPeer(), (*ii).second.getAddrOrGUID());
				delete pckt;
				break;
			}
		}
	}
};

void addEnt(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{

	LOG(INFO) << "Add entity request...";
	//Reading data
	int id, uid, wid;
	bitStream->Read(id);
	bitStream->Read(uid);
	bitStream->Read(wid);

	//Adding new instance of entity
	Entity* e = (Entity*)CREATE_CLASS(uid);
	e->setId(id);
	e->setWorldId(wid);
	
	//Adding entity to world
	World* w = &worlds.find(wid)->second;
	if (w != nullptr)
	{
		w->addEntity(e);
	}

	//Requesting data load from worker
	RakNet::BitStream bs;
	bs.Write(id);
	bs.Write(uid);
	databaseWorker->callRPC("le", &bs);
};

void addWorld(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int id;
	std::string name;
	float x, y, z;
	bitStream->Read(id);
	bitStream->Read(name);
	bitStream->Read(x);
	bitStream->Read(y);
	bitStream->Read(z);

	worlds.insert(std::pair<int, World>(id, *new World(id, name, x, y, z)));
	LOG(INFO) << "Add world!";
};

DatabaseWorker::DatabaseWorker(RakNet::RPC4* r) : Worker(r)
{
	this->registerFunction("aw", addWorld);
	this->registerFunction("addEntity", addEnt);
	this->registerFunction("se", setEntity);
	this->registerFunction("sed", setEntityData);
	
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, workerConnected);
	addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailConnect);
}

DatabaseWorker::~DatabaseWorker()
{
	LOG(INFO) << "dbWorker dctor";
}
