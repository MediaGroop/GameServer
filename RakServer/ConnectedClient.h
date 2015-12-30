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

	void set_controlled_unit(Entity* s);

	Entity* get_controlled_unit();

	RakNet::RakString getChar();

	void setChar(RakNet::RakString i);

	void setAccId(RakNet::RakString i);

	RakNet::RakString getAccId();

	void setHash(unsigned char* h);

	unsigned char* getHash();

	RakNet::AddressOrGUID getAddrOrGUID();

	ConnectedClient(RakNet::AddressOrGUID a);

	virtual ~ConnectedClient();

	virtual void signal(Signal* s) override;

	virtual void onDisconnect();
};

