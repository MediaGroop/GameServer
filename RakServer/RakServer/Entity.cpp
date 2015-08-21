#include "Entity.h"
#include "WorkerAddEntityPacket.h"
#include "ServVars.h"

Entity::Entity(int i) :Entity(i, 0,0,0,0){};

Entity::Entity(int i, float x, float y, float z) : Entity(i, x, y, z, 0){};

Entity::Entity(int i, float x, float y, float z, int world) : Entity(i, x, y, z, world, 0){};

Entity::Entity(int i, float x, float y, float z, int body, int world) : _id(i), _x(x), _y(y), _z(z), _world_id(world){};

// I dunno why it must return bool...
bool Entity::sync(Shapes shapes, float height, float radius, bool hasMass, float mass){
	WorkerAddEntityPacket packet(_world_id, _id, _x, _y, _z, hasMass, mass, height, radius, shapes);
	packet.send(physicsWorker->getClient()->getPeer(), *physicsWorker->getClient()->getServerAddr());
	return true;
};

Entity::~Entity(){};