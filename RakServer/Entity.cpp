#include "Entity.h"
#include "WorkerAddEntityPacket.h"
#include "ServVars.h"
#include "UpdateEntitySignal.h"
#include "PacketTypes.h"
#include "OnAddNearSignal.h"
#include "OnRemoveNearSignal.h"

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

void Entity::loadData(RakNet::BitStream* bitStream){

	float height, mass, radius;
	char shapeId;
	bool hasMass, has_ph_data;
	bitStream->Read(_id);

	bitStream->Read(_world_id);
	bitStream->Read(_body_id);
	//bitStream->Read(_upcast_id);


	bitStream->Read(_x);
	bitStream->Read(_y);
	bitStream->Read(_z);

	bitStream->Read(_x_grid);
	bitStream->Read(_y_grid);

	bitStream->Read(has_ph_data);
	if (has_ph_data)
	{
		bitStream->Read(shapeId);
		bitStream->Read(height);
		bitStream->Read(radius);
		bitStream->Read(hasMass);
		if (hasMass)
			bitStream->Read(mass);
	}
	else
	{
		shapeId = 1;
		height = 1;
		radius = 1;
		hasMass = true;
		mass = 1;
	}

	sync((Shapes)shapeId, height, radius, hasMass, mass);
};

void Entity::setXYZ(float x, float y, float z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_x_grid = x / CHUNK_WIDTH;
	this->_y_grid = z / CHUNK_HEIGHT;
};

void Entity::updateTo(Entity* e){
	e->SignalController(new UpdateEntitySignal(this));
};

std::vector<Entity*>* Entity::getNear(){
	return &_near;
}

void Entity::registerClasses()
{
	REGISTER_CLASS(-1, Entity);
}

void Entity::set_controller(Avatar* a){
	_controller = a;
}

Avatar* Entity::get_controller(){
	return _controller;
}

int Entity::getId(){
	return _id;
};

void Entity::setWorldId(int i)
{
	_world_id = i;
}

void Entity::setId(int i){
	_id = i;
}

int Entity::getBodyId()
{
	return _body_id;
};

void Entity::SignalController(Signal* s)
{
	if (_controller != nullptr)
		_controller->signal(s);
}

float Entity::getX(){
	return _x;
};

float Entity::getY(){
	return _y;
};

float Entity::getZ(){
	return _z;
};

bool Entity::hasNear(Entity* from)
{
	if (std::find(_near.begin(), _near.end(), from) != _near.end())
		return true;
	return false;
};

void Entity::addNear(Entity* ent){
	if (!hasNear(ent))
	{
		_near.insert(_near.end(), ent);
			SignalController(new OnAddNearSignal(ent));
	}
};

void Entity::removeNear(Entity* ent)
{
	if (hasNear(ent))
	{
		std::remove(_near.begin(), _near.end(), ent);
			SignalController(new OnRemoveNearSignal(ent));
	}
}

void Entity::WriteData(RakNet::BitStream* stream)
{
	stream->Write(_id);
	stream->Write(_body_id);
	stream->Write(_x);
	stream->Write(_y);
	stream->Write(_z);
}

void Entity::saveData(RakNet::BitStream* bitStream){
	bitStream->Write(_id);
	bitStream->Write(_body_id);
	bitStream->Write(_world_id);
	bitStream->Write(_upcast_id);

	bitStream->Write(_x_grid);
	bitStream->Write(_y_grid);

	bitStream->Write(_x);
	bitStream->Write(_y);
	bitStream->Write(_z);
	//TODO: save physics data
};

Entity::~Entity(){};