#pragma once
#include "stdafx.h"
#include <string>
#include <thread>
#include "WorldAttrs.h"
#include "Chunk.h"
#include "Entity.h"
#include <list>
#include <map>
#include "GameTask.h"
#include <vector>

using namespace std;

class World
{
public:
	
	World(int, std::string, float x, float y, float z);
	
	~World();
	
	void update();
	
	bool getRunning()
	{
		return _running;
	};
	
	void addEntity(Entity* e)
	{
		_entities[e->getId()] = *e;
		//TODO: add to chunk?
	}

	int getTPU()
	{
		return _tPU;
	};
	
	Entity* getEntity(int id)
	{
		return &_entities.find(id)->second;
	};

	RakNet::RakString getName(){
		return *new RakNet::RakString(_name.c_str());
	}

private:
	vector<GameTask> _tasks;
	std::map<int, Entity> _entities;
	bool _running;
	int _id;
	std::string _name;
	std::list<Chunk> _chunks;
	WorldAttrs* _attrs;
	int _tPU = 100;
	std::thread* _updateTrd;
};