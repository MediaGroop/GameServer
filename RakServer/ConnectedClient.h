#pragma once
#include "stdafx.h"
#include "ClientState.h"
#include "Avatar.h"
#include "Entity.h"

class ConnectedClient: public Avatar
{
private:
	RakNet::AddressOrGUID addr;
	
	//pass-session hash store for chaining
	unsigned char hash[20];
	
	//account id
	RakNet::RakString _account;
	RakNet::RakString _char;
	
	//Instance of controlled unit, we can control everything....
	Entity* _controlled_unit;
public:	

	void set_controlled_unit(Entity* s)
	{
		this->_controlled_unit = s;
		s->set_controller(this);
	};

	Entity* get_controlled_unit(){
		return _controlled_unit;
	};

	RakNet::RakString getChar(){
		return _char;
	};

	void setChar(RakNet::RakString i)
	{
		_char = i;
	};

	void setAccId(RakNet::RakString i)
	{
		_account = i;
	};

	RakNet::RakString getAccId(){
		return _account;
	};

	void setHash(unsigned char* h)
	{
		for (int i = 0; i < 20; ++i)
			hash[i] = h[i];
	};

	unsigned char* getHash()
	{
		return hash;
	};

	RakNet::AddressOrGUID getAddrOrGUID()
	{
		return addr;
	};

	ConnectedClient(RakNet::AddressOrGUID a){
		this->addr = a;
	};

	virtual ~ConnectedClient(){};

	virtual void onDisconnect(){};
};

