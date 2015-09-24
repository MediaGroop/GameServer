#pragma once
#include "Shapes.h"

class Entity{
private:
	int _id;
	int _body_id;
	float _x, _y, _z;
	int _world_id;
	std::list<Entity> _near;
public:
	int getId(){
		return _id;
	};
	
	int getBodyId()
	{
		return _body_id;
	};

	bool sync(Shapes, float, float, bool, float);

	Entity(int); // entity id
	Entity(int, float, float, float);  // entity id, x, y, z
	Entity(int, float, float, float, int); // entity id, x, y, z, worldId
	Entity(int, float, float, float, int, int); // entity id, x, y, z, body id, worldId

	virtual ~Entity();
};