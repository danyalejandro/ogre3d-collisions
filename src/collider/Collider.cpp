#include <iomanip>
#include "Collider.h"
#include "../config.h"


Collider::Collider() {
	std::cout << "Collider() constructor" << std::endl;
	X = Vector3(0.0);
	V = Vector3(0.0);
	A = Vector3(0.0);
	F = Vector3(0.0);
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
	//std::cout << "A = " << std::setw(10) <<  A << "; V = " << std::setw(10) <<  V << "; X = " << std::setw(10) <<  X << "; m = " << m << std::endl;
	

	if (!fixed) {
		F = CONFIG_GRAVITY + Fimp;
		Fimp = 0; // reset after applying the first time
		A = 0.98*(F / m); // @TODO: separate into real physical dampings
		V += 0.9*A;
		X += 0.85*V;

		Fa = FimpA;
		Aa = Fa / 15.0; // @TODO: Configurable moment of inertia
		FimpA = 0;
		Va += Aa;
		rot = node->getOrientation() + node->getOrientation().FromAxes(Va);
		
		// update vertices
		for (Vector3 &p : vertices) {
			p += V;
		}
		
		// update node
		node->setPosition(X);
		node->rotate(rot);
	}
}

// creates an edge from references to the vertices at indexes specified
void Collider::addEdge(unsigned int index0, unsigned int index1) {
	edges.push_back(Edge(&vertices.at(index0), &vertices.at(index1)));
}

// adds a new vertice
void Collider::addVertice(Vector3 &v) {
	vertices.push_back(v);
}

// Performs Separate Axis Theorem (3D version) for OBBs, as explained in the white paper https://www.geometrictools.com/Documentation/DynamicCollisionDetection.pdf
// Returns the number of the collision origin if collision is detected with the other collider
// the number returned (from 1 to 15) follows the order of the equations in the white paper collision tests table
char Collider::collidedWith(Collider &other) {
	// Set up variables to match the variables in the paper
	Vector3 C0 = X;
	Vector3 C1 = other.X;
	Vector3 A0 = faces[0].normal;
	Vector3 A1 = faces[1].normal;
	Vector3 A2 = faces[2].normal;
	double a0 =  (*faces[1].edges.at(0)->v1 - *faces[1].edges.at(0)->v2).length();
	double a1 =  (*faces[2].edges.at(0)->v1 - *faces[2].edges.at(0)->v2).length();
	double a2 =  (*faces[3].edges.at(1)->v1 - *faces[3].edges.at(1)->v2).length();
	Vector3 B0 = other.faces[0].normal;
	Vector3 B1 = other.faces[1].normal;
	Vector3 B2 = other.faces[2].normal;
	double b0 =  (*other.faces[1].edges.at(0)->v1 - *other.faces[1].edges.at(0)->v2).length();
	double b1 =  (*other.faces[2].edges.at(0)->v1 - *other.faces[2].edges.at(0)->v2).length();
	double b2 =  (*other.faces[3].edges.at(1)->v1 - *other.faces[3].edges.at(1)->v2).length();
	Vector3 D = C1 - C0;
	double c00 = abs(A0.dotProduct(B0));
	double c01 = abs(A0.dotProduct(B1));
	double c02 = abs(A0.dotProduct(B2));
	double c10 = abs(A1.dotProduct(B0));
	double c11 = abs(A1.dotProduct(B1));
	double c12 = abs(A1.dotProduct(B2));
	double c20 = abs(A2.dotProduct(B0));
	double c21 = abs(A2.dotProduct(B1));
	double c22 = abs(A2.dotProduct(B2));

	// We return the first case triggered as the collision case for an initial approximation, though it might not be the first case that actually happened
	// @TODO: track the time for each collision case, trigger the collision case which fired first
	if (abs(A0.dotProduct(D)) > b0*c00+b1*c01+b2*c02 + a0) return 1;
	if (abs(A1.dotProduct(D)) > b0*c10+b1*c11+b2*c12 + a1) return 2;
	if (abs(A2.dotProduct(D)) > b0*c20+b1*c21+b2*c22 + a2) return 3;

	if (abs(B0.dotProduct(D)) > a0*c00+a1*c10+a2*c20 + b0) return 4;
	if (abs(B1.dotProduct(D)) > a0*c01+a1*c11+a2*c21 + b1) return 5;
	if (abs(B2.dotProduct(D)) > a0*c02+a1*c12+a2*c22 + b2) return 6;

	if (abs(A2.dotProduct(D)) - A1.dotProduct(D) > a1*c20+a2*c10+b1*c02+b2*c01) return 7;
	if (abs(A2.dotProduct(D)) - A1.dotProduct(D) > a1*c21+a2*c11+b0*c02+b2*c00) return 8;
	if (abs(A2.dotProduct(D)) - A1.dotProduct(D) > a1*c22+a2*c12+b0*c01+b1*c00) return 9;
	if (abs(A0.dotProduct(D)) - A2.dotProduct(D) > a0*c20+a2*c00+b1*c12+b2*c11) return 10;
	if (abs(A0.dotProduct(D)) - A2.dotProduct(D) > a0*c21+a2*c01+b0*c12+b2*c10) return 11;
	if (abs(A0.dotProduct(D)) - A2.dotProduct(D) > a0*c22+a2*c02+b0*c11+b1*c10) return 12;
	if (abs(A1.dotProduct(D)) - A0.dotProduct(D) > a0*c10+a1*c00+b1*c22+b2*c21) return 13;
	if (abs(A1.dotProduct(D)) - A0.dotProduct(D) > a0*c11+a1*c01+b0*c22+b2*c20) return 14;
	if (abs(A1.dotProduct(D)) - A0.dotProduct(D) > a0*c12+a1*c02+b0*c21+b1*c20) return 15;
	
	return 0; // no collision
}

// adds a face from references to the edges at indexes specified (counter-clockwise following the right hand rule)
void Collider::addFace(unsigned int index0, unsigned int index1, unsigned int index2, unsigned int index3) {
	faces.push_back(Quad(&edges.at(index0), &edges.at(index1), &edges.at(index2), &edges.at(index3)));
}


// adds impulse to the Fimp variable; Fimp will be applied in next collider step and then discarded
void Collider::applyImpulse(Vector3 v, Vector3 pos) {
	Fimp += 0.92*v; // @TODO: Figure out how to damp this with the body's inertia
	FimpA += 0.7*v.crossProduct(pos - X);
}
