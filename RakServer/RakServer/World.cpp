#include "World.h"
#include "CreateWorldPacket.h"
#include "ServVars.h"

World::World(int i, std::string name, float x, float y, float z): _id(i), _name(name){
	CreateWorldPacket packet(i, x, y, z);
	packet.send(physicsWorker->getClient()->getPeer(), *physicsWorker->getClient()->getServerAddr());
	LOG(INFO) << "World initialized: ";
	LOG(INFO) << name;
}

World::~World(){

}