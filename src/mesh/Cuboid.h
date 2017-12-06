#ifndef COLLISIONS_CUBOID_H
#define COLLISIONS_CUBOID_H

#include <Ogre.h>
#include "../collider/ColCuboid.h"

using namespace Ogre;
using std::vector;

// Describes a cuboid (6-faced 3D box with uneven faces) with a manual object
class Cuboid {
public:
	ColCuboid collider;
	SceneNode* node;
	ManualObject* manual;
	std::string materialName;

	Cuboid(SceneManager &scnMgr, std::string materialName);
	void setVertices(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p5, Vector3 p6, Vector3 p7);
	void addQuadVertices(Vector3 &p0, Vector3 &p1, Vector3 &p2, Vector3 &p3);
};


#endif //COLLISIONS_CUBOID_H
