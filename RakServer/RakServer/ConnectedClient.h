#pragma once
#include "stdafx.h"

class ConnectedClient
{
public:
	RakNet::AddressOrGUID addr;
	ConnectedClient(RakNet::AddressOrGUID a){
		this->addr = a;
	}
	~ConnectedClient();
};

