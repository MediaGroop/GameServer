#include "Worker.h"


Worker::Worker()
{
	this->_client = new Client();
}

void Worker::start(const char* h, int port){
	this->_client->connect(h, port);
	while(!this->_client->getRunning()){}
	init();
};

Worker::~Worker()
{
	LOG(INFO) << "Worker dctor";
}


void Worker::addHandler(short k, std::function<void(RakNet::Packet* p)> h){
	_client->getListener()->add(k, h);
};

Client* Worker::getClient()
{
	return _client;
};

void Worker::setClient(Client* c)
{
	_client = c;
};

void Worker::callRPC(const char* funcName, RakNet::BitStream* bs){
    this->_client->getRPC()->Call(funcName, bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), false);
};

bool Worker::callRPCAndWait(const char* funcName, RakNet::BitStream* bs, RakNet::BitStream* out){
    return this->_client->getRPC()->CallBlocking(funcName, bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), out);
};

void Worker::registerFunction(const char* c, void(*functionPointer) (RakNet::BitStream *userData, RakNet::Packet *packet)){
  this->_client->getRPC()->RegisterFunction(c, functionPointer);
};

void Worker::init()
{

};
