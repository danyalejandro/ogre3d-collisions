#ifndef OGRE3D_COLLISIONS_MANAGER_H
#define OGRE3D_COLLISIONS_MANAGER_H


#include "Collider.h"

class Manager {
public:
	std::vector<Collider*> colliders;

	void nextFrame(); // runs steps for the frame on all registered colliders
	void addCollider(Collider* c); // register a collider
};


#endif //OGRE3D_COLLISIONS_MANAGER_H
