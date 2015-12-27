#pragma once
#include "Signal.h"
#include "PacketTypes.h"

class OnAddNearSignal :
	public Signal
{
private:
	Entity* _ent;

public:
	
	OnAddNearSignal(Entity* ent);
	
	~OnAddNearSignal();

	virtual void incapsulate(ConnectedClient* a)override{
		_ent->sendDataTo(a);
	};

	virtual void incapsulate(AI* a)override{};

};

