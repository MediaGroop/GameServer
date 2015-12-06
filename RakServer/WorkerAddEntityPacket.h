#pragma once
#include "Packet.h"
#include "Shapes.h"
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
class WorkerAddEntityPacket :
	public Packet
{
private:
	int _entityId, _worldId;
	float _x, _y, _z, _mass, _radius, _height;
	bool _hasMass;
	Shapes _shape;
public:
	WorkerAddEntityPacket(int, int, float, float, float, bool, float, float, float, Shapes); // worldId, entityId, x, y, z, hasMass, mass, height, radius, shape
	~WorkerAddEntityPacket();
	void virtual send(RakNet::RakPeerInterface * by, RakNet::AddressOrGUID to) override;
};

