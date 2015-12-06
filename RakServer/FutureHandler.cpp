#include "FutureHandler.h"


FutureHandler::FutureHandler(ConnectedClient* c, char packt) : _clnt(c), _packetID(packt)
{
}


FutureHandler::~FutureHandler()
{
}
