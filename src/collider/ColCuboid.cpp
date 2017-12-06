#include "ColCuboid.h"


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
}
