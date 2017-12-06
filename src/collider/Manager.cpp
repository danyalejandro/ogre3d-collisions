//
// Created by danyalejandro on 05/12/17.
//

#include "Manager.h"
#include "../config.h"

void Manager::addCollider(Collider* c) {
	colliders.push_back(c);
}

void Manager::nextFrame() {
	int n, steps = 1 / CONFIG_DT;

	for (n = 0 ; n < steps ; n++) {
		for (Collider* c : colliders) {
			c->step();
		}
	}
}
