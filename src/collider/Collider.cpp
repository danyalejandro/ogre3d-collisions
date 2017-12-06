//
// Created by danyalejandro on 05/12/17.
//

#include "Collider.h"

void Collider::averageCenter() {
	if (vertices.size() > 0) {
		for (const Vector3 &v : vertices) {
			X += v;
		}
		X /= double(vertices.size());
	}
	else {
		X = 0;
	}
}

void Collider::step() {
	Vector3 d(0.1, 0.0, 0.0);
	X += d;

	for (Vector3 &p : vertices) {
		p += d;
	}
}

// creates an edge from references to the vertices at indexes specified
void Collider::addEdge(unsigned int index0, unsigned int index1) {
	edges.push_back(std::pair<Vector3*, Vector3*>(&vertices.at(index0), &vertices.at(index1)));
}

// adds a new vertice
void Collider::addVertice(Vector3 &v) {
	vertices.push_back(v);
}
