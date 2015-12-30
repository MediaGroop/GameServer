#include "OnRemoveNearSignal.h"
#include "PacketTypes.h"
#include "ServVars.h"

OnRemoveNearSignal::OnRemoveNearSignal(Entity* e) : _ent(e)
{
}


OnRemoveNearSignal::~OnRemoveNearSignal()
{
}

void OnRemoveNearSignal::incapsulate(ConnectedClient* a){
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)REMOVE_ENTITY);
	bsOut.Write(_ent->getId());
	mainServer->getPeer()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, a->getAddrOrGUID(), false);
};

void OnRemoveNearSignal::incapsulate(AI* a){};
