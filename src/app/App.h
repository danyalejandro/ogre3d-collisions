#ifndef OGRECAM_APP_H
#define OGRECAM_APP_H

#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <OgreResourceGroupManager.h>
#include "Sample.h"
#include "CamGuy.h"
#include "../config.h"
#include "../mesh/Cuboid.h"
#include "../collider/Manager.h"


using namespace Ogre;
using namespace OgreBites;

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener {
	SceneNode* camNode;
	SceneManager* scnMgr;
	CamGuy camGuy;
	Manager man;
	std::vector<Cuboid> cuboids;

	float camMouseSpeed = 0.4f;
	bool firstFrame = true;

public:
	App();
	void setup();
	
	void createCamera();
	void createLights();
	void createObjects();
	
	bool keyPressed(const KeyboardEvent &evt);
	bool keyReleased(const KeyboardEvent &evt);
	bool mouseMoved(const MouseMotionEvent &evt);
	bool frameRenderingQueued(const FrameEvent &evt);
};


#endif //OGRECAM_APP_H
