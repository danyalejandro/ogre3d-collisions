#include "Cuboid.h"

/* Builds a cuboid out of 8 points
 * First 4 points should be one of the faces, the next 4 points should be the opposite face
 * Both faces' points should be entered in counter-clockwise order
 */
Cuboid::Cuboid(SceneManager &scnMgr, std::string materialName) {
	node = scnMgr.getRootSceneNode()->createChildSceneNode();
	manual = scnMgr.createManualObject();
	this->materialName = materialName;
}

// p1, p2, p3 and p4 describe a quad face in counter-clockwise order
void Cuboid::addQuadVertices(Vector3 &p0, Vector3 &p1, Vector3 &p2, Vector3 &p3) {
	int i0 = manual->getCurrentIndexCount();

	manual->position(p0.x, p0.y, p0.z);
	manual->textureCoord(0, 0);
	manual->position(p2.x, p2.y, p2.z);
	manual->textureCoord(1, 1);
	manual->position(p3.x, p3.y, p3.z);
	manual->textureCoord(0, 1);

	manual->position(p0.x, p0.y, p0.z);
	manual->textureCoord(0, 0);
	manual->position(p1.x, p1.y, p1.z);
	manual->textureCoord(1, 0);
	manual->position(p2.x, p2.y, p2.z);
	manual->textureCoord(1, 1);

	manual->triangle(i0, i0 + 1, i0 + 2);
	manual->triangle(i0 + 3, i0 + 4, i0 + 5);
}

// stores vertices and sets up the manual object
void Cuboid::setVertices(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 p5, Vector3 p6, Vector3 p7) {
	// set up collider
	collider = ColCuboid(node, p0, p1, p2, p3, p4, p5, p6, p7);

	// add points to manual object in the order received
	manual->begin(materialName, RenderOperation::OT_TRIANGLE_LIST);

	addQuadVertices(p0, p1, p2, p3);
	addQuadVertices(p4, p7, p6, p5);
	addQuadVertices(p1, p5, p6, p2);
	addQuadVertices(p0, p3, p7, p4);
	addQuadVertices(p3, p2, p6, p7);
	addQuadVertices(p0, p4, p5, p1);

	manual->setCastShadows(true);
	manual->end();
	((Ogre::VertexData*)(manual->getEdgeList()->edgeGroups.at(0).vertexData))->prepareForShadowVolume();
	node->attachObject(manual);
}
