#include "Entity.h"
#include "WorkerAddEntityPacket.h"
#include "ServVars.h"

factory g_factory;

Entity::Entity(){
};

Entity::Entity(int i) :Entity(i, 0, 0, 0, 0){};

Entity::Entity(int i, float x, float y, float z) : Entity(i, x, y, z, 0){};

Entity::Entity(int i, float x, float y, float z, int world) : Entity(i, x, y, z, 0, world){};

Entity::Entity(int i, float x, float y, float z, int body, int world) : Entity(i, x, y, z, body, world, 0){};

Entity::Entity(int i, float x, float y, float z, int body, int world, int upId) : _id(i), _x(x), _y(y), _z(z), _world_id(world), _body_id(body), _upcast_id(upId){

};

// I dunno why it must return bool...
bool Entity::sync(Shapes shapes, float height, float radius, bool hasMass, float mass){
	
	//Registering it to physics worker
	WorkerAddEntityPacket packet(_world_id, _id, _x, _y, _z, hasMass, mass, height, radius, shapes);
	packet.send(physicsWorker->getClient()->getPeer(), *physicsWorker->getClient()->getServerAddr());

	//Registering it to sync worker
	RakNet::BitStream bs;
	bs.Write(this->_world_id);//World id is the same as room id, y e s...
	bs.Write(this->_id);

	bs.Write(this->_x);
	bs.Write(this->_y);
	bs.Write(this->_z);

	bs.Write(this->_updateRadius);

	syncWorker->callRPC("ae", &bs);
	return true;
};

Entity::~Entity(){};