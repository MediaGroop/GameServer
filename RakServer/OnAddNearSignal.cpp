#include "OnAddNearSignal.h"
#include "PacketTypes.h"
#include "Entity.h"
#include "ServVars.h"

OnAddNearSignal::OnAddNearSignal(Entity* e) : _ent(e)
{
}


OnAddNearSignal::~OnAddNearSignal()
{
}

void OnAddNearSignal::incapsulate(ConnectedClient* a){
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ADD_ENTITY);
	_ent->WriteData(&bsOut);
	mainServer->getPeer()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, a->getAddrOrGUID(), false);
	_ent->sendAddData(a);
};

void OnAddNearSignal::incapsulate(AI* a){};