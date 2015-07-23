#include "World.h"
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include "easylogging++.h"

void updateWorld(int tick, btDynamicsWorld* world){
	world->stepSimulation(1 / tick, 10);
}

World::World(int i, std::string name, btVector3 & gravity){
	this->id = i;
	this->alias = name;
	this->broadphase = new btDbvtBroadphase();

	this->collisionConfiguration = new btDefaultCollisionConfiguration();
	this->dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	this->solver = new btSequentialImpulseConstraintSolver;
	this->dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	this->dynamicsWorld->setGravity(gravity);
	LOG(INFO) << "World " + name + " has been created!";
	thread trd(updateWorld, 60, this->dynamicsWorld);
	this->physicsTrd = &trd;
}

World::~World(){
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}