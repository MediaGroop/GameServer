#include "ConnectedClient.h"
#include "Signal.h"

void ConnectedClient::set_controlled_unit(Entity* s)
{
	this->_controlled_unit = s;
	s->set_controller(this);
};

Entity* ConnectedClient::get_controlled_unit(){
	return _controlled_unit;
};

RakNet::RakString ConnectedClient::getChar(){
	return _char;
};

void ConnectedClient::setChar(RakNet::RakString i)
{
	_char = i;
};

void ConnectedClient::setAccId(RakNet::RakString i)
{
	_account = i;
};

RakNet::RakString ConnectedClient::getAccId(){
	return _account;
};

void ConnectedClient::setHash(unsigned char* h)
{
	for (int i = 0; i < 20; ++i)
		hash[i] = h[i];
};

unsigned char* ConnectedClient::getHash()
{
	return hash;
};

RakNet::AddressOrGUID ConnectedClient::getAddrOrGUID()
{
	return addr;
};

ConnectedClient::ConnectedClient(RakNet::AddressOrGUID a){
	this->addr = a;
};

ConnectedClient::~ConnectedClient(){};

void ConnectedClient::signal(Signal* s) {
	s->incapsulate(this);
};

void ConnectedClient::onDisconnect(){};