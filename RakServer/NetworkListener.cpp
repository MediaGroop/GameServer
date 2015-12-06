#include "NetworkListener.h"
#include "easylogging++.h"
#include "Server.h"

//map<short, std::function<void(RakNet::Packet*)>> NetworkListener::_handlers;


void NetworkListener::handle(RakNet::Packet *packet){
	short s = packet->data[0];
	LOG(INFO) << "A message with ID: " << s <<" has been arrived!";
	for (map<short, std::function<void(RakNet::Packet*)>>::iterator ii = this->_handlers.begin(); ii != this->_handlers.end(); ++ii)
	{
	//	LOG(INFO) < (*ii).first << s;
		if ((*ii).first == packet->data[0])
		{
			//LOG(INFO) << "executing: " <<(*ii).first << s;

			(*ii).second(packet);
			break;
		}
	}
}

void NetworkListener::add(short id, std::function<void(RakNet::Packet*)> exec){
	this->_handlers.insert(pair<short, std::function<void(RakNet::Packet*)>>(id, exec));
}