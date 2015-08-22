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
