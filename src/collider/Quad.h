#ifndef COLLISIONS_QUAD_H
#define COLLISIONS_QUAD_H

#include <Ogre.h>
#include "Edge.h"

using Ogre::Vector3;

// Abstraction of a face between 4 vertices
class Quad {
public:
	std::array<Edge*, 4> edges; // edges, in counter-clockwise order with the normal obeying the right hand rule
	Vector3 normal; // normal unitary vector
	
	Quad(Edge* e0, Edge* e1, Edge* e2, Edge* e3);
};


#endif //COLLISIONS_QUAD_H
