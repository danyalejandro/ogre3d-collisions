#ifndef COLLISIONS_COLCUBOID_H
#define COLLISIONS_COLCUBOID_H

#include <Ogre.h>
#include <vector>
#include "Collider.h"

using Ogre::Vector3;
using Ogre::Plane;

// Collider shaped as a cuboid (6 faces)
class ColCuboid : public Collider {
public:
	//std::array<std::vector<Vector3*>, 6> faces;

	ColCuboid() = default;
	ColCuboid(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p5, Vector3 p6, Vector3 p7);
};


#endif //COLLISIONS_COLCUBOID_H
