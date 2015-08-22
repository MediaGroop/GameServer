#include "DatabaseWorker.h"
#include "ConfigLoader.h"
#include "easylogging++.h"
#include "DatabaseWorkerHandler.h"
#include "DbWorkerConnFailHandler.h"
#include "World.h"

extern std::map<int, World> worlds;

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
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, workerConnected);
	addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailConnect);
}

DatabaseWorker::~DatabaseWorker()
{
	LOG(INFO) << "dbWorker dctor";
}
