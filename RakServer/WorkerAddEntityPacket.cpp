#include "WorkerAddEntityPacket.h"
#include "PhysicsWorkerPackets.h"
/*																				____________________
																				   \__________/    |
"Add entity" packet structure:														|  C++    |    |
- World id: id of a world that entity mst be spawned in(Integer)                /------------------|\
- Entity id: entity unique id(Integer)                                         /                   |\\
- X: x pos(Float)                                                             /   /===+      /===+ O \\
- Y: y pos(Float)                                                             |  /00  |     /00  |   ||
- Z: z pos(Float)                                                             |  \0---/     \0---/   ||
- Shape definition: what type of physics shape must be used(Short)            |                      ||
- Has mass: true if we must read mass, false if dont(Bool)                    |   \---------------|  ||
- Mass(Opt): mass of an entity(Float)                                         |    \=========     /  ||
																			   \     \-----------/   /
if shape definition is BOX:													    \___________________/
- Height: height of a box(Float)

if shape definition is CONE, CAPSULE or CYLLINDER:
- Height: height of a figure(Float)
- Radius: radius of a figure(Float)

if shape definition is SPHERE
- Radius: radius of a sphere(Float)

*/
void WorkerAddEntityPacket::send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to){
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ADD_ENTITY_P);
	bsOut.Write(_worldId);
	bsOut.Write(_entityId);
	bsOut.Write(_x);
	bsOut.Write(_y);
	bsOut.Write(_z);
	bsOut.Write(_shape);
	bsOut.Write(_hasMass);

	if (_hasMass)
		bsOut.Write(_mass);

	switch (_shape)
	{
	case BOX:
		bsOut.Write(_height);
		break;
	case CYLLINDER:
		bsOut.Write(_height);
		bsOut.Write(_radius);
		break;
	case SPHERE:
		bsOut.Write(_radius);
		break;
	case CAPSULE:
		bsOut.Write(_height);
		bsOut.Write(_radius);
		break;
	case CONE:
		bsOut.Write(_height);
		bsOut.Write(_radius);
		break;
	default:
		break;
	}

		by->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, to, false);

};

WorkerAddEntityPacket::WorkerAddEntityPacket(int wId, int eId, float x, float y, float z, bool hm, float mass, float hei, float rad, Shapes sh) : _worldId(wId), _entityId(eId), _x(x), _y(y), _z(z), _hasMass(hm), _mass(mass), _height(hei), _radius(rad), _shape(sh)
{
}


WorkerAddEntityPacket::~WorkerAddEntityPacket()
{
}
