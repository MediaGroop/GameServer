#pragma once
#include "stdafx.h"
#include "Client.h"
#include <functional>
#include "RPC4Plugin.h"

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
class Worker
{
private:
	Client* _client;
	RakNet::RakString _name; // must be unique!
	RakNet::RPC4* _rpc;
public:
	Client* getClient()
	{
		return _client;
	};

	void setClient(Client* c)
	{
		_client = c;
	};

	void callRPC(char* funcName, RakNet::BitStream* bs){
		_rpc->Signal(_name + RakNet::RakString(funcName), bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), false, true);
	};

	bool callRPCAndWait(char* funcName, RakNet::BitStream* bs, RakNet::BitStream* out){
		return _rpc->CallBlocking(_name + RakNet::RakString(funcName), bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, *_client->getServerAddr(), out);
	};

	void registerFunction(char* c, void(*functionPointer) (RakNet::BitStream *userData, RakNet::Packet *packet)){
		_rpc->RegisterSlot(c, functionPointer, 0);
	};

	Worker(char* c, std::string, int);
	
	virtual ~Worker();
};