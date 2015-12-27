#pragma once
#include "Signal.h"
class UpdateEntitySignal :
	public Signal
{
private:
	Entity* _ent;

public:
	UpdateEntitySignal(Entity* e);
	~UpdateEntitySignal();

	virtual void incapsulate(ConnectedClient* a)override{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)UPDATE_ENTITY);
		bsOut.Write(_ent->getId());
		bsOut.Write(_ent->getX());
		bsOut.Write(_ent->getY());
		bsOut.Write(_ent->getZ());
		mainServer->getPeer()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, a->getAddrOrGUID(), false);
	};

	virtual void incapsulate(AI* a)override{};
};

