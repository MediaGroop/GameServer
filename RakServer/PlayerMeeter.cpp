#include "PlayerMeeter.h"
#include "ClientState.h"
#include "LoadWorldPacket.h"

bool PlayerMeeter::process(Stateable* s)
{
	if (s->getState() == READY_TO_ENTER){
		return process((ConnectedClient*)s);
	}
	return false;
};

bool PlayerMeeter::process(ConnectedClient* c)
{
	//LoadWorldPacket* pckt = new LoadWorldPacket();
	c->setState(LOADING_WORLD);
	return true;
};

PlayerMeeter::PlayerMeeter()
{
}


PlayerMeeter::~PlayerMeeter()
{
}
