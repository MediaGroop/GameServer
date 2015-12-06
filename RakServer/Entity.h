#pragma once
#include "stdafx.h"
#include "Shapes.h"
#include "Avatar.h"
#include <list>
#include <map>

#define REGISTER_CLASS(t, n) g_factory.register_class<n>(t)
#define CREATE_CLASS(t) g_factory.construct(t);

template <class T> void* constructor() { return (void*)new T(); }

struct factory
{
	typedef void*(*constructor_t)();
	typedef std::map<int, constructor_t> map_type;
	map_type m_classes;

	template <class T>
	void register_class(int id)
	{
		m_classes.insert(std::make_pair(id, &constructor<T>));
	}

	void* construct(int n)
	{
		map_type::iterator i = m_classes.find(n);
		if (i == m_classes.end()) return 0; // or throw or whatever you want
		return i->second();
	}
};

extern factory g_factory;

class Entity{

private:
	int _id;
	int _body_id;
	float _x, _y, _z;
	int _world_id;
	int _x_grid, _y_grid;
	int _upcast_id;
	int _updateRadius = 50;
	std::list<Entity> _near;
	Avatar* _controller;
public:

	static void registerClasses()
	{
		REGISTER_CLASS(-1, Entity);
	}

	void set_controller(Avatar* a){
		_controller = a;
	}

	Avatar* get_controller(){
		return _controller;
	}

	int getId(){
		return _id;
	};

	void setWorldId(int i)
	{
		_world_id = i;
	}

	void setId(int i){
		_id = i;
	}

	int getBodyId()
	{
		return _body_id;
	};

	bool sync(Shapes, float, float, bool, float);

	Entity();
	Entity(int); // entity id
	Entity(int, float, float, float);  // entity id, x, y, z
	Entity(int, float, float, float, int); // entity id, x, y, z, worldId
	Entity(int, float, float, float, int, int); // entity id, x, y, z, body id, worldId
	Entity(int, float, float, float, int, int, int); // entity id, x, y, z, body id, worldId, upcastId

	virtual void loadData(RakNet::BitStream* bitStream){

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

	virtual void saveData(RakNet::BitStream* bitStream){
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

	virtual ~Entity();
};
