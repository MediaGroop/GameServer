#pragma once
#include "stdafx.h"
#include "Client.h"
#include <functional>
#include "RPC4Plugin.h"
#include "easylogging++.h"
#include <functional>

class Worker
{
private:
	Client* _client;

public:

	void addHandler(short k, std::function<void(RakNet::Packet* p)> h);

	Client* getClient();

	void setClient(Client* c);

	void callRPC(const char* funcName, RakNet::BitStream* bs);

	bool callRPCAndWait(const char* funcName, RakNet::BitStream* bs, RakNet::BitStream* out);

	void registerFunction(const char* c, void(*functionPointer) (RakNet::BitStream *userData, RakNet::Packet *packet));

	Worker();

	void start(const char* h, int port);

	virtual ~Worker();
	
	virtual void init();
};