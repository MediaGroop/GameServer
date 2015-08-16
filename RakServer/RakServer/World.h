#pragma once
#include <string>
#include <thread>
#include "WorldAttrs.h"
#include "Chunk.h"
#include <list>

using namespace std;
#include <btBulletDynamicsCommon.h>
#include "Entity.h"

class World
{
public:
	World(int, std::string, btVector3&);
	~World();
	void update(int);
private:
	std::list<Entity> entities;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btCollisionDispatcher* dispatcher;
	int id;
	std::string alias;
	std::list<Chunk> chunks;
	WorldAttrs* attrs;
	std::thread* physicsTrd;
};