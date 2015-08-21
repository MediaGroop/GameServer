#pragma once
#include <string>
#include <thread>
#include "WorldAttrs.h"
#include "Chunk.h"
#include "Entity.h"
#include <list>
#include <map>

using namespace std;

class World
{
public:
	World(int, std::string, float x, float y, float z);
	~World();
	void update(int);
private:
	std::map<int, Entity> _entities;
	int _id;
	std::string _name;
	std::list<Chunk> _chunks;
	WorldAttrs* _attrs;
	std::thread* _updateTrd;
};