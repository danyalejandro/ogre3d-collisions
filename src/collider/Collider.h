#ifndef OGRE3D_COLLISIONS_COLLIDER_H
#define OGRE3D_COLLISIONS_COLLIDER_H

#include <Ogre.h>
#include <vector>
#include "Collider.h"

using Ogre::Vector3;


class Collider {
public:
	Vector3 X; // position of center (same as SceneNode)
	std::vector<Vector3> vertices;
	std::vector< std::pair<Vector3*, Vector3*> > edges; // edges, made from pointers to vertices

	void averageCenter();
	void step();

	void addEdge(unsigned int index0, unsigned int index1);
	void addVertice(Vector3 &v);
};


#endif //OGRE3D_COLLISIONS_COLLIDER_H