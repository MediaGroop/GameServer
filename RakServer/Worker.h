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

	void addHandler(short k, std::function<void(RakNet::Packet* p)> h);

	Client* getClient();

	void setClient(Client* c);

	void callRPC(const char* funcName, RakNet::BitStream* bs);

	bool callRPCAndWait(const char* funcName, RakNet::BitStream* bs, RakNet::BitStream* out);

	void registerFunction(const char* c, void(*functionPointer) (RakNet::BitStream *userData, RakNet::Packet *packet));

	Worker(RakNet::RPC4*);

	void start(std::string h, int port);

	virtual ~Worker();
};