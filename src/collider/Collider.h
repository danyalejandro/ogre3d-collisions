#ifndef OGRE3D_COLLISIONS_COLLIDER_H
#define OGRE3D_COLLISIONS_COLLIDER_H

#include <Ogre.h>
#include <vector>
#include <iostream>
#include "Collider.h"
#include "Quad.h"
#include "Edge.h"


using Ogre::Vector3;
using Ogre::SceneNode;

class Collider {
public:
	Vector3 F; // translational force
	Vector3 A; // acceleration
	Vector3 V; // speed
	Vector3 X; // position of center (same as SceneNode)

	Vector3 Fa; // rotational force
	Vector3 Aa; // angular acceleration
	Vector3 Va; // angular velocity
	Ogre::Quaternion rot; // orientation

	Vector3 Fimp; // holds impulse forces; gets reset after applied
	Vector3 FimpA; // same for angular component
	
	float m; // body total mass
	bool fixed = false; // true if this body doesn't budge (floats in space)
	
	std::vector<Quad> faces; // 4 edged faces
	std::vector<Vector3> vertices;
	std::vector<Edge> edges; // edges, made from pointers to vertices
	
	SceneNode* node;
	
	Collider();

	void setCenterFromVertices();
	void addEdge(unsigned int index0, unsigned int index1);
	void addVertice(Vector3 &v);
	void applyImpulse(Vector3 v, Vector3 pos);
	void addFace(unsigned int index0, unsigned int index1, unsigned int index2, unsigned int index3);
	virtual char collidedWith(Collider &other);
	
	void step();

	
};


#endif //OGRE3D_COLLISIONS_COLLIDER_H
