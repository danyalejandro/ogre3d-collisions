#ifndef OGRE3D_COLLISIONS_COLLIDER_H
#define OGRE3D_COLLISIONS_COLLIDER_H

#include <Ogre.h>
#include <vector>
#include "Collider.h"

using Ogre::Vector3;
using Ogre::SceneNode;

class Collider {
public:
	Vector3 F; // total force
	Vector3 A; // acceleration
	Vector3 V; // speed
	Vector3 X; // position of center (same as SceneNode)
	
	float m; // body total mass
	
	std::vector<Vector3> vertices;
	std::vector< std::pair<Vector3*, Vector3*> > edges; // edges, made from pointers to vertices
	
	SceneNode* node;
	
	Collider();

	void setCenterFromVertices();
	void addEdge(unsigned int index0, unsigned int index1);
	void addVertice(Vector3 &v);
	
	void step();

	
};


#endif //OGRE3D_COLLISIONS_COLLIDER_H
