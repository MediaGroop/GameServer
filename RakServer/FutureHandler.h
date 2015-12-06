#pragma once
#include "ConnectedClient.h"

class FutureHandler
{
private:
	ConnectedClient* _clnt;
	char _packetID;
public:
	
	//Checks if this future handler prepared for specified client and packet
	bool verify(ConnectedClient* cln, char id)
	{
		if ((cln == this->_clnt) && (id == this->_packetID)){
			return true;
		}
		return false;
	};

	FutureHandler(ConnectedClient* c, char packt);
	~FutureHandler();
};

