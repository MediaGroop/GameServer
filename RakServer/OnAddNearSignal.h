#pragma once
#include "Signal.h"
#include "Entity.h"

class OnAddNearSignal :
	public Signal
{
private:
	Entity* _ent;

public:
	
	OnAddNearSignal(Entity* ent);
	
	~OnAddNearSignal();

	virtual void incapsulate(ConnectedClient* a)override;

	virtual void incapsulate(AI* a)override;
};

