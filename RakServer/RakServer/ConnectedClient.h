#pragma once
#include "stdafx.h"
#include "ClientState.h"

class ConnectedClient
{
private:
	RakNet::AddressOrGUID addr;
	//pass-session hash store for chaining
	unsigned char hash[20];
	ClientState state = CONNECTED;
public:	

	void setState(ClientState s){
		state = s;
	};

	ClientState getState()
	{
		return state;
	}

	void setHash(unsigned char* h)
	{
		for (int i = 0; i < 20; ++i)
			hash[i] = h[i];
	}

	unsigned char* getHash()
	{
		return hash;
	}

	RakNet::AddressOrGUID getAddrOrGUID()
	{
		return addr;
	}

	ConnectedClient(RakNet::AddressOrGUID a){
		this->addr = a;
	}
	virtual ~ConnectedClient(){};
	virtual void onDisconnect(){};


};

