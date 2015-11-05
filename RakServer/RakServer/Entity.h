#pragma once
#include "Shapes.h"
#include <list>

class Entity{
private:
	typedef Entity * (*crfnptr)(const std::string &);
	typedef std::map<std::string, crfnptr> CreatorMap;

	static CreatorMap creators;
	int _id;
	int _body_id;
	float _x, _y, _z;
	int _world_id;
	int _x_grid, _y_grid;
	int _upcast_id;
	int _updateRadius = 50;
	std::list<Entity> _near;
public:

	Entity * clone() const { return new Entity(*this); }
	
	/*
	static Entity * create_from_string(std::string name)
	{
		CreatorMap::const_iterator it = creators.find(name);
		return it == creators.end() ? NULL : it->first();
	}
	*/

	static void regClass(std::string name, crfnptr f)
	{
		creators[name] = f;
	}

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
	Entity(int, float, float, float, int, int, int); // entity id, x, y, z, body id, worldId, upcastId

	virtual ~Entity();
};