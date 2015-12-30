#pragma once
#include "stdafx.h"
#include "Avatar.h"
#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include "Shapes.h"

class Signal;
class ConnectedClient;

#define REGISTER_CLASS(t, n) g_factory.register_class<n>(t)
#define CREATE_CLASS(t) g_factory.construct(t);

#define CHUNK_WIDTH 512
#define CHUNK_HEIGHT 512

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
	std::vector<Entity*> _near;
	Avatar* _controller;
public:

	virtual void updateTo(Entity* e);

	std::vector<Entity*>* getNear();

	static void registerClasses();

	void set_controller(Avatar* a);

	Avatar* get_controller();

	int getId();

	void setWorldId(int i);

	void setId(int i);

	int getBodyId();

	bool sync(Shapes, float, float, bool, float);

	Entity();
	Entity(int); // entity id
	Entity(int, float, float, float);  // entity id, x, y, z
	Entity(int, float, float, float, int); // entity id, x, y, z, worldId
	Entity(int, float, float, float, int, int); // entity id, x, y, z, body id, worldId
	Entity(int, float, float, float, int, int, int); // entity id, x, y, z, body id, worldId, upcastId

	virtual void loadData(RakNet::BitStream* bitStream);

	virtual void saveData(RakNet::BitStream* bitStream);

	void SignalController(Signal* s);
	
	void WriteData(RakNet::BitStream* stream);

	void removeNear(Entity* ent);

	void addNear(Entity* ent);

	bool hasNear(Entity* from);

	void setXYZ(float x, float y, float z);

	float getX();

	float getY();

	float getZ();

	virtual void sendAddData(ConnectedClient* to){};
	
	virtual ~Entity();
};
