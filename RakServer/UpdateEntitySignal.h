#pragma once
#include "Signal.h"
#include "Entity.h"

class UpdateEntitySignal :
	public Signal
{
private:
	Entity* _ent;

public:
	UpdateEntitySignal(Entity* e);
	~UpdateEntitySignal();

	virtual void incapsulate(ConnectedClient* a)override;

	virtual void incapsulate(AI* a)override;
};

