#include "Quad.h"

// Stores the edge references in order (right hand) and computes the normal
Quad::Quad(Edge *e0, Edge *e1, Edge *e2, Edge *e3) {
	edges.at(0) = e0;
	edges.at(1) = e1;
	edges.at(2) = e2;
	edges.at(3) = e3;
	
	// use 3 non-collinear face points to get the face normal
	Vector3 v1Plane = *e0->v1 - *e0->v2;
	Vector3 v2Plane = *e0->v1 - *e1->v1;
	normal = v1Plane.crossProduct(v2Plane).normalise();
}
