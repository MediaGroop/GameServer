#include "Client.h"
#include "easylogging++.h"

void Client::startNetworkTrd(Client* clnt, std::string h, int port)
{
	RakNet::Packet *packet;

	RakNet::SocketDescriptor sd;
	clnt->getPeer()->Startup(1, &sd, 1);
	clnt->getPeer()->Connect(h.c_str(), port, 0, 0);
	clnt->setRunning(true);
	while (clnt->getRunning())
	{
		Sleep(1);
		for (packet = clnt->getPeer()->Receive(); packet; clnt->getPeer()->DeallocatePacket(packet), packet = clnt->getPeer()->Receive())
		{
			clnt->getListener()->handle(packet);
		}
	}
	clnt->getPeer()->CloseConnection(*clnt->getServerAddr(), true);
	clnt->getPeer()->Shutdown(10.0);
	RakNet::RakPeerInterface::DestroyInstance(clnt->getPeer());
}

void Client::connect(std::string host, int port)
{
	this->setThread(new std::thread(startNetworkTrd, this, host, port));
}
