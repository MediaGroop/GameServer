#pragma once
#include "stdafx.h"
#include "ClientState.h"
#include "Stateable.h"

class ConnectedClient: public Stateable
{
private:
	RakNet::AddressOrGUID addr;
	//pass-session hash store for chaining
	unsigned char hash[20];
	//account id
	RakNet::RakString _account;
public:	

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

