#include "Client.h"
#include "easylogging++.h"

void Client::startNetworkTrd(Client* clnt, std::string h, int port)
{
	clnt->peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet *packet;

	RakNet::SocketDescriptor sd;
	clnt->peer->Startup(1, &sd, 1);
	clnt->peer->Connect(h.c_str(), port, 0, 0);
	clnt->running = true;
	while (clnt->running)
	{
		Sleep(1);
		for (packet = clnt->peer->Receive(); packet; clnt->peer->DeallocatePacket(packet), packet = clnt->peer->Receive())
		{
			clnt->listener->handle(packet);
		}
	}
	clnt->peer->CloseConnection(clnt->serverAddress, true);
	clnt->peer->Shutdown(1);
	RakNet::RakPeerInterface::DestroyInstance(clnt->peer);
}

void Client::connect(std::string host, int port)
{
	static std::thread trs(startNetworkTrd, this,  host, port);
	this->networkTrd = &trs;
}
