#include "Cuboid.h"

/* Builds a cuboid out of 8 points
 * First 4 points should be one of the faces, the next 4 points should be the opposite face
 * Both faces' points should be entered in counter-clockwise order
 */
Cuboid::Cuboid(SceneManager &scnMgr, std::vector<Vector3> &points, std::string materialName) {
	this->vertice = points;
	manual = scnMgr.createManualObject("manual");
	manual->begin(materialName, RenderOperation::OT_TRIANGLE_LIST);

	// add points in the order received
	addQuadVertices(points.at(0), points.at(1), points.at(2), points.at(3));
	addQuadVertices(points.at(4), points.at(7), points.at(6), points.at(5));
	addQuadVertices(points.at(1), points.at(5), points.at(6), points.at(2));
	addQuadVertices(points.at(0), points.at(3), points.at(7), points.at(4));
	addQuadVertices(points.at(3), points.at(2), points.at(6), points.at(7));
	addQuadVertices(points.at(0), points.at(4), points.at(5), points.at(1));

	manual->setCastShadows(true);
	manual->end();
	((Ogre::VertexData*)(manual->getEdgeList()->edgeGroups.at(0).vertexData))->prepareForShadowVolume();
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