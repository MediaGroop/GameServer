#pragma once
#include "Signal.h"
#include "Entity.h"

class OnRemoveNearSignal :
	public Signal
{
private:
	Entity* _ent;

public:
	
	OnRemoveNearSignal(Entity*);
	
	~OnRemoveNearSignal();
	
	virtual void incapsulate(ConnectedClient* a)override;
	
	virtual void incapsulate(AI* a)override;
	
};

