#pragma once
//#include "ConnectedClient.h"
//#include "AI.h"
class ConnectedClient;
class AI;
class Signal
{
public:
	Signal();
	~Signal();
	virtual void incapsulate(ConnectedClient* a){};
	virtual void incapsulate(AI* a){};
};

