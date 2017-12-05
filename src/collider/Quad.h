#ifndef COLLISIONS_QUAD_H
#define COLLISIONS_QUAD_H

#include <Ogre.h>

using Ogre::Vector3;

// Abstraction of a face between 4 vertices
class Quad {
public:
	std::array<Vector3*, 4> vertices; // vertices, in counter-clockwise order with the normal obeying the right hand rule
	Vector3 normal; // normal unitary vector
};


#endif //COLLISIONS_QUAD_H
