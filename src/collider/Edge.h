#ifndef OGRE3D_COLLISIONS_EDGE_H
#define OGRE3D_COLLISIONS_EDGE_H

#include <Ogre.h>
#include <vector>

using Ogre::Vector3;

// Edge abstraction: 2 vertice references
class Edge {
public:
	Vector3* v1;
	Vector3* v2;
	
	Edge(Vector3* _v1, Vector3* _v2);
};


#endif //OGRE3D_COLLISIONS_EDGE_H
