#include "World.h"
#include "CreateWorldPacket.h"
#include "ServVars.h"
#define sleep Sleep(10)

void World::update()
{
	//LOG(INFO) << "update!";
	for (int i = 0; i < this->_tasks.size(); ++i)
	{
		if (i > getTPU())
		{
			break;
		}
		_tasks[i]->process();
		_tasks.erase(_tasks.begin() + i);
	}
}

static void process(World* w)
{
	while (w->getRunning())
	{
		sleep;
		w->update();
	}
}

World::World(int i, std::string name, float x, float y, float z): _id(i), _name(name){
	CreateWorldPacket packet(i, x, y, z);
	packet.send(physicsWorker->getClient()->getPeer(), *physicsWorker->getClient()->getServerAddr());
	LOG(INFO) << "World initialized: ";
	LOG(INFO) << name;
	this->_running = true;
	this->_updateTrd = new std::thread(process, this);
}

World::~World(){

}