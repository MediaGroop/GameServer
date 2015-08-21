#include "Worker.h"


Worker::Worker(char* c, std::string addr, int port)
{
	this->_name = *new RakNet::RakString(c);
	this->_client = new Client(new NetworkListener());
	this->_client->connect(addr, port);
	_rpc = new RakNet::RPC4();
	this->_client->getPeer()->AttachPlugin(_rpc);
}


Worker::~Worker()
{
	delete _client;
	delete _rpc;
}
