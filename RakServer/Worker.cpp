#include "Worker.h"


Worker::Worker(RakNet::RPC4* rp)
{
	_rpc = rp;
	this->_client = new Client();
	this->_client->getPeer()->AttachPlugin(rp);
}

void Worker::start(std::string h, int port){
	this->_client->connect(h, port);
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
	_rpc->Call(funcName, bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), false);
};

bool Worker::callRPCAndWait(const char* funcName, RakNet::BitStream* bs, RakNet::BitStream* out){
	return _rpc->CallBlocking(funcName, bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), out);
};

void Worker::registerFunction(const char* c, void(*functionPointer) (RakNet::BitStream *userData, RakNet::Packet *packet)){
	_rpc->RegisterFunction(c, functionPointer);
};