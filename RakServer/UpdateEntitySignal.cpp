#include "UpdateEntitySignal.h"
#include "Entity.h"
#include "ServVars.h"
#include "PacketTypes.h"

UpdateEntitySignal::UpdateEntitySignal(Entity* e) : _ent(e)
{
}


UpdateEntitySignal::~UpdateEntitySignal()
{
}

void UpdateEntitySignal::incapsulate(ConnectedClient* a){
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)UPDATE_ENTITY);
	bsOut.Write(_ent->getId());
	bsOut.Write(_ent->getX());
	bsOut.Write(_ent->getY());
	bsOut.Write(_ent->getZ());
	mainServer->getPeer()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, a->getAddrOrGUID(), false);
};

void UpdateEntitySignal::incapsulate(AI* a){};