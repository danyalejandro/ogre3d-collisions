//
// Created by danyalejandro on 05/12/17.
//

#include <iomanip>
#include "Collider.h"


Collider::Collider() {
	std::cout << "Collider() constructor" << std::endl;
	X = 0.0;
	V = 0.0;
	A = 0.0;
	F = 0.0;
	m = 1.0; // never 0!
}

// set the center average position from the vertices
void Collider::setCenterFromVertices() {
	if (vertices.size() > 0) {
		for (const Vector3 &v : vertices) {
			X += v;
		}
		X /= double(vertices.size());
	}
	else {
		X = 0.0;
	}
	
	node->setPosition(X); // update node
}

void Collider::step() {
	// integrate
	std::cout << "A = " << std::setw(10) <<  A << "; V = " << std::setw(10) <<  V << "; X = " << std::setw(10) <<  X << "; m = " << m << std::endl;
	
	A = F / m;
	V += A;
	X += V;
	
	
	
	// update vertices
	for (Vector3 &p : vertices) {
		p += V;
	}
	
	// update node
	node->setPosition(X);
}

// creates an edge from references to the vertices at indexes specified
void Collider::addEdge(unsigned int index0, unsigned int index1) {
	edges.push_back(std::pair<Vector3*, Vector3*>(&vertices.at(index0), &vertices.at(index1)));
}

// adds a new vertice
void Collider::addVertice(Vector3 &v) {
	vertices.push_back(v);
}
