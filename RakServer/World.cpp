#include "World.h"
#include "CreateWorldPacket.h"
#include "ServVars.h"
#define sleep Sleep(10)

void World::update()
{
	static GameTask* task = nullptr;
	//LOG(INFO) << "update!";
	for (int i = 0; i < this->_tasks.size(); ++i)
	{
		if (i > getTPU())
		{
			break;
		}
		task = _tasks[i];
		task->process();
		_tasks.erase(_tasks.begin() + i);
		delete task;
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

bool World::getRunning()
{
	return _running;
};

void World::addEntity(Entity* e)
{
	_entities[e->getId()] = *e;
	//TODO: add to chunk?
}

int World::getTPU()
{
	return _tPU;
};

Entity* World::getEntity(int id)
{
	return &_entities.find(id)->second;
};

RakNet::RakString World::getName(){
	return *new RakNet::RakString(_name.c_str());
}

void World::pushTask(GameTask* t)
{
	_tasks.insert(_tasks.end(), t);
}