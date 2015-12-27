#pragma once
#include "stdafx.h"
#include "Shapes.h"
#include "Avatar.h"
#include <list>
#include "Signal.h"
#include <map>
#include <algorithm>
#include <vector>
#include "OnAddNearSignal.h"
#include "OnRemoveNearSignal.h"
#include "UpdateEntityTask.h"
#include "ServVars.h"

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

	void updateToSync(){
		RakNet::BitStream bs;
		bs.Write(_id);
		bs.Write(_world_id);
		bs.Write(_x);
		bs.Write(_y);
		bs.Write(_z);
		syncWorker->callRPC("ue", &bs);
	};

	virtual void updateTo(Entity* e){
		e->SignalController(new UpdateEntitySignal(this));
	};

	std::vector<Entity*>* getNear(){
		return &_near;
	}

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

	void SignalController(Signal* s)
	{
		if (_controller != nullptr)
			_controller->signal(s);
	}

	void WriteData(RakNet::BitStream* stream)
	{
		stream->Write(_id);
		stream->Write(_body_id);
		stream->Write(_x);
		stream->Write(_y);
		stream->Write(_z);
	}

	void removeNear(Entity* ent)
	{
		if (hasNear(ent))
		{
			std::remove(_near.begin(), _near.end(), ent);
			SignalController(new OnRemoveNearSignal(ent));
		}
	}

	void addNear(Entity* ent){
		if (!hasNear(ent))
		{
			_near.insert(_near.end(), ent);
			SignalController(new OnAddNearSignal(ent));
		}
	};

	bool hasNear(Entity* from)
	{
		if (std::find(_near.begin(), _near.end(), from) != _near.end())
			return true;
		return false;
	};

	void setXYZ(float x, float y, float z)
	{
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_x_grid = x / CHUNK_WIDTH;
		this->_y_grid = z / CHUNK_HEIGHT;
		World* w = &worlds.find(this->_world_id)->second;
		if (w != nullptr)
		{
			w->pushTask(new UpdateEntityTask(this));
		}
	};

	float getX(){
		return _x;
	};

	float getY(){
		return _y;
	};

	float getZ(){
		return _z;
	};

	void sendDataTo(ConnectedClient* to){
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ADD_ENTITY);
		WriteData(&bsOut);
		mainServer->getPeer()->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to->getAddrOrGUID(), false);
		sendAddData(to);
	};

	virtual void sendAddData(ConnectedClient* to){};
	virtual ~Entity();
};
