#include "DatabaseWorker.h"
#include "ConfigLoader.h"
#include "easylogging++.h"
#include "DatabaseWorkerHandler.h"
#include "DbWorkerConnFailHandler.h"
#include "World.h"

extern std::map<int, World> worlds;


void addEntity(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int id, wid, bid, uid, xg, yg;
	float x, y, z, height, mass, radius;
	char shapeId;
	bool hasMass, has_ph_data;

	bitStream->Read(id);
	bitStream->Read(bid);
	bitStream->Read(wid);
	bitStream->Read(uid);

	bitStream->Read(xg);
	bitStream->Read(yg);

	bitStream->Read(x);
	bitStream->Read(y);
	bitStream->Read(z);

	bitStream->Read(has_ph_data);
	
	if (has_ph_data)
	{
		bitStream->Read(shapeId);
		bitStream->Read(height);
		bitStream->Read(radius);
		bitStream->Read(hasMass);
		bitStream->Read(mass);

	}
	else{
		shapeId = 1;
		height = 1;
		radius = 1;
		hasMass = true;
		mass = 1;
	}
	Entity* e = new Entity(id, x, y, z, bid, wid, uid);
	e->sync((Shapes)shapeId, height, radius, hasMass, mass);
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
	this->registerFunction("ae", addEntity);
	addHandler((short)ID_CONNECTION_REQUEST_ACCEPTED, workerConnected);
	addHandler((short)ID_CONNECTION_ATTEMPT_FAILED, onFailConnect);
}

DatabaseWorker::~DatabaseWorker()
{
	LOG(INFO) << "dbWorker dctor";
}
