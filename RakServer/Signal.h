#pragma once
#include "Avatar.h"
#include "AI.h"
#include "ConnectedClient.h"

class Signal
{
public:
	Signal();
	~Signal();
	virtual void incapsulate(ConnectedClient* a){};
	virtual void incapsulate(AI* a){};
};

