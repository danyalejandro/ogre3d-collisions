#ifndef COLLISIONS_CUBOID_H
#define COLLISIONS_CUBOID_H

#include <Ogre.h>

using namespace Ogre;
using std::vector;

// Describes a cuboid (6-faced 3D box with uneven faces) with a manual object
class Cuboid {
public:
	ManualObject* manual;
	std::vector<Vector3> vertice;

	Cuboid(SceneManager &scnMgr, std::vector<Vector3> &points, std::string materialName);
	void addQuadVertices(Vector3 &p0, Vector3 &p1, Vector3 &p2, Vector3 &p3);
};


#endif //COLLISIONS_CUBOID_H
