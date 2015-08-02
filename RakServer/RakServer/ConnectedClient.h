#pragma once
#include "stdafx.h"

class ConnectedClient
{
public:
	RakNet::AddressOrGUID addr;
	//pass-session hash store for chaining
	RakNet::RakString hash; 
	
	ConnectedClient(RakNet::AddressOrGUID a){
		this->addr = a;
	}
	~ConnectedClient();
	virtual void onDisconnect(){};
};

