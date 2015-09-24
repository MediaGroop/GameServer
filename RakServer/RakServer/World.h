#pragma once
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
	int getTPU()
	{
		return _tPU;
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