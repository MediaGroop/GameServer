#pragma once
#include "stdafx.h"
#include "Client.h"
#include <functional>
#include "RPC4Plugin.h"
#include "easylogging++.h"
/*                                                                   ____________________________________
                                                                    |                __                  |
Representation of a network worker									|			  __/OO\__               |
Just ghost class for Client, using RPC calls for interaction        |	     ___//-- ||  --\\___         | 
																	|	    //--     ||      --\\        |
																	|			     ||                  |
																	|				 ||                  |
																	|				 ||                  |
																	|				 ||                  |
																	|			     ||                  |
																	|			    /||\                 |
																	|			   |0000|                |
																	|			    \--/                 |
																	|____________________________________|
																	          \\\\|WORKER|////
																	              \======/
*/
#include <functional>

class Worker
{
private:
	Client* _client;
	RakNet::RPC4* _rpc;
public:

	void addHandler(short k, std::function<void(RakNet::Packet* p)> h){
		_client->getListener()->add(k, h);
	};

	Client* getClient()
	{
		return _client;
	};

	void setClient(Client* c)
	{
		_client = c;
	};

	void callRPC(const char* funcName, RakNet::BitStream* bs){
		_rpc->Signal(funcName, bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), false, true);
	};

	bool callRPCAndWait(const char* funcName, RakNet::BitStream* bs, RakNet::BitStream* out){
		return _rpc->CallBlocking(funcName, bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), out);
	};

	void registerFunction(const char* c, void(*functionPointer) (RakNet::BitStream *userData, RakNet::Packet *packet)){
		_rpc->RegisterSlot(c, functionPointer, 0);
	};

	Worker(RakNet::RPC4*);

	void start(std::string h, int port);

	virtual ~Worker();
};