#include "DatabaseWorker.h"
#include "ConfigLoader.h"
#include "easylogging++.h"

void addWorld(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	LOG(INFO) << "Add world!";
};

DatabaseWorker::DatabaseWorker() : Worker("dat", ConfigLoader::getVal("DatabaseWorker-Address"), ConfigLoader::getIntVal("DatabaseWorker-Port"))
{
	this->registerFunction("b-aw", addWorld);
}

DatabaseWorker::~DatabaseWorker()
{
}
