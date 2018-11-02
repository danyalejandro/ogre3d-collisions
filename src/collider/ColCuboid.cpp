#include "ColCuboid.h"

// returns 1 or -1 depending on the sign
double sign(double x) {
	if (x > 0.0) return 1.0;
	if (x < 0.0) return -1.0;
	return x;
}

ColCuboid::ColCuboid() : Collider() {
	std::cout << "ColCuboid() constructor" << std::endl;
}


ColCuboid::ColCuboid(SceneNode* node, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p5, Vector3 p6, Vector3 p7) : Collider() {
	this->node = node;
	
	std::cout << "ColCuboid(things) constructor" << std::endl;
	// store vertices
	addVertice(p0);
	addVertice(p1);
	addVertice(p2);
	addVertice(p3);
	addVertice(p4);
	addVertice(p5);
	addVertice(p6);
	addVertice(p7);

	// compute center position and initialize center position coords from vertices
	setCenterFromVertices();

	// store edges (try to follow counter-clockwise order)
	addEdge(0,1);
	addEdge(1,2);
	addEdge(2,3);
	addEdge(3,0);
	addEdge(5,4);
	addEdge(4,7);
	addEdge(7,6);
	addEdge(6,5);
	addEdge(3,7);
	addEdge(4,0);
	addEdge(1,5);
	addEdge(6,2);
	
	// store faces (again follow counter-clockwise order)
	addFace(0,1,2,3);
	addFace(7,6,5,4);
	addFace(1,9,5,10);
	addFace(7,8,3,11);
	addFace(8,6,0,2);
	addFace(10,3,11,0);
}

// Responds to a collision by creating an impulse force to the opposite direction in the contact point
// Obtains the intersection point using the unique point coefficients for OBB-OBB intersection described in https://www.geometrictools.com/Documentation/DynamicCollisionDetection.pdf
void ColCuboid::collisionResponse(char index, ColCuboid other) {
	// Set up variable names to match the equations in the paper
	// @TODO: Maybe we can move some of these calculations out?
	Vector3 C0 = X;
	Vector3 C1 = other.X;
	Vector3 A0 = faces[0].normal; // right handed orthonormal axes
	Vector3 A1 = faces[1].normal;
	Vector3 A2 = faces[2].normal;
	double a0 =  (*faces[1].edges.at(0)->v1 - *faces[1].edges.at(0)->v2).length(); // extents
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

	double x0,x1,x2,y0,y1,y2;
	
	Vector3 p; // contact point

	// For an initial approximation, we only solve for this collider's side and suppose the same contact point for both colliders
	// @TODO: Figure out what to do with the other collider's contact point... perhaps increase precision?
	switch (index) {
		// Cases for Ai
		case 1: p = Vector3(-sign(c00)*b0,-sign(c01)*b1,-sign(c02)*b2); break;
		case 2: p = Vector3(-sign(c10)*b0,-sign(c11)*b1,-sign(c12)*b2); break;
		case 3: p = Vector3(-sign(c20)*b0,-sign(c21)*b1,-sign(c22)*b2); break;
		// Cases for Bj
		case 4: p = Vector3(sign(c00)*b0,sign(c10)*b1,sign(c20)*b2); break;
		case 5: p = Vector3(sign(c01)*b0,sign(c11)*b1,sign(c21)*b2); break;
		case 6: p = Vector3(sign(c02)*b0,sign(c12)*b1,sign(c22)*b2); break;
		// Edge-to-Edge tests
		case 7:
			x1 = -sign(c20)*a1;
			x2 = sign(c10)*a2;
			y1 = -sign(c02)*b1;
			y2 = sign(c01)*b2;
			x0 = (1/(1-c00*c00))*A0.dotProduct(D)+c00*(-B0.dotProduct(D)+c10*x1+c20*x2+c01*y1+c02*y2);
			p = Vector3(x0,x1,x2); // initial approximation, same for other cases
			break;
		case 8:
			x1 = -sign(c21)*a1;
			x2 = sign(c11)*a2;
			y1 = -sign(c02)*b0;
			y2 = sign(c00)*b2;
			x0 = (1/(1-c01*c01))*A0.dotProduct(D)+c01*(-B1.dotProduct(D)+c11*x1+c21*x2+c00*y0+c02*y2);
			p = Vector3(x0,x1,x2);
			break;
		case 9:
			x1 = -sign(c22)*a1;
			x2 = sign(c12)*a2;
			y0 = -sign(c01)*b0;
			y1 = sign(c00)*b1;
			x0 = (1/(1-c02*c02))*A0.dotProduct(D)+c02*(-B2.dotProduct(D)+c12*x1+c22*x2+c00*y0+c01*y1);
			p = Vector3(x0,x1,x2);
			break;
		case 10:
			x0 = sign(c20)*a0;
			x2 = -sign(c00)*a2;
			y1 = -sign(c12)*b1;
			y2 = sign(c11)*b2;
			x1 = (1/(1-c10*c10))*A1.dotProduct(D)+c10*(-B0.dotProduct(D)+c00*x0+c20*x2+c11*y1+c12*y2);
			p = Vector3(x0,x1,x2);
			break;
		case 11:
			x0 = sign(c21)*a0;
			x2 = -sign(c01)*a2;
			y0 = sign(c12)*b0;
			y2 = -sign(c10)*b2;
			x1 = (1/(1-c11*c11))*A1.dotProduct(D)+c11*(-B1.dotProduct(D)+c01*x0+c21*x2+c10*y0+c12*y2);
			p = Vector3(x0,x1,x2);
			break;
		case 12:
			x0 = sign(c22)*a0;
			x2 = -sign(c02)*a2;
			y0 = -sign(c11)*b0;
			y1 = sign(c10)*b1;
			x1 = (1/(1-c12*c12))*A1.dotProduct(D)+c12*(-B2.dotProduct(D)+c02*x0+c22*x2+c10*y0+c11*y1);
			p = Vector3(x0,x1,x2);
			break;
		case 13:
			x0 = -sign(c10)*a0;
			x1 = sign(c00)*a1;
			y1 = -sign(c22)*b1;
			y2 = sign(c21)*b2;
			x2 = (1/(1-c20*c20))*A2.dotProduct(D)+c20*(-B0.dotProduct(D)+c00*x0+c10*x1+c21*y1+c22*y2);
			p = Vector3(x0,x1,x2);
			break;
		case 14:
			x0 = -sign(c11)*a0;
			x1 = sign(c01)*a1;
			y0 = sign(c22)*b0;
			y2 = -sign(c20)*b2;
			x2 = (1/(1-c21*c21))*A2.dotProduct(D)+c21*(-B1.dotProduct(D)+c01*x0+c11*x1+c20*y0+c22*y2);
			p = Vector3(x0,x1,x2);
			break;
		case 15:
			x0 = -sign(c12)*a0;
			x1 = sign(c02)*a1;
			y0 = -sign(c21)*b0;
			y1 = sign(c20)*b1;
			x2 = (1/(1-c22*c22))*A2.dotProduct(D)+c22*(-B2.dotProduct(D)+c02*x0+c12*x1+c20*y0+c21*y1);
			p = Vector3(x0,x1,x2);
			break;
		// @TODO: add the other tests
	}

	Vector3 Fresp = 0.00055 * V; // for now we just do a factor of the velocity of this collider as a quick-and-dirty "approximation"
	applyImpulse(-Fresp, p);
	other.applyImpulse(Fresp, p);
}