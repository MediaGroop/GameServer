#include <btBulletDynamicsCommon.h>
#include <string>
#include <thread>
#include "WorldAttrs.h"
#include "Chunk.h"
#include <list>

using namespace std;
#include <btBulletDynamicsCommon.h>

class World
{
public:
	World(int, std::string, btVector3&);
	~World();
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btCollisionDispatcher* dispatcher;
	int id;
	std::string alias;
	std::list<Chunk> chunks;
	WorldAttrs* attrs;
private:
	std::thread* physicsTrd;
	void update(int);
};