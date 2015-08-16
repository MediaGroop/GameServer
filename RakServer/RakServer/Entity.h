#pragma once
#include "World.h"

class Entity{
private:
	int id;
	btRigidBody rigid;
	World* world_ptr;
public:
	Entity(int);
	Entity(int, btVector3);
	Entity(int, btVector3, World*);
	virtual ~Entity();
};