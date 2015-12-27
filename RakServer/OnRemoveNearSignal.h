#pragma once
#include "Signal.h"
#include "PacketTypes.h"

class OnRemoveNearSignal :
	public Signal
{
private:
	Entity* _ent;

public:
	
	OnRemoveNearSignal(Entity*);
	
	~OnRemoveNearSignal();
	
	virtual void incapsulate(ConnectedClient* a)override{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)REMOVE_ENTITY);
		bsOut.Write(_ent->getId());
		mainServer->getPeer()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, a->getAddrOrGUID(), false);
	};
	
	virtual void incapsulate(AI* a)override{};

};

