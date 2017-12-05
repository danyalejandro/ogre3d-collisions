#ifndef COLLISIONS_COLCUBOID_H
#define COLLISIONS_COLCUBOID_H

#include <Ogre.h>
#include <vector>

using Ogre::Vector3;
using Ogre::Plane;

// Collider shaped as a cuboid (6 faces)
class ColCuboid {
	std::array<Vector3, 8> vertices; // 8 vertices in order: 4 front face, 4 back face counter-clockwise (same as Cuboid mesh)
	std::array<std::pair<Vector3*, Vector3*>, 12> edges; // 12 edges, made from pointers to vertices
	std::array<std::vector<Vector3*>, 6> faces;
};


#endif //COLLISIONS_COLCUBOID_H
