#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayElement.h>
#include "App.h"

App::App() : OgreBites::ApplicationContext("BasicApp") {
	camGuy = CamGuy();
}

// ##### EVENTS

bool App::keyPressed(const OgreBites::KeyboardEvent& evt)  {
	Keycode key = evt.keysym.sym;
	
	if (key == SDLK_ESCAPE) getRoot()->queueEndRendering();
	else camGuy.handleKeyPressed(key);
	
	return InputListener::keyPressed(evt);
}

bool App::keyReleased(const OgreBites::KeyboardEvent& evt)  {
	Keycode key = evt.keysym.sym;
	camGuy.handleKeyReleased(key);
	return InputListener::keyPressed(evt);
}

bool App::frameRenderingQueued(const FrameEvent &evt) {
	camGuy.processFrame(evt.timeSinceLastFrame);
	return ApplicationContext::frameRenderingQueued(evt);
}

bool App::mouseMoved(const MouseMotionEvent &evt) {
	if (!firstFrame) {
		camNode->yaw(Ogre::Degree(-evt.xrel * camMouseSpeed), Ogre::Node::TS_PARENT);
		camNode->pitch(Ogre::Degree(-evt.yrel * camMouseSpeed));
	} else {
		firstFrame = false;
	}
	return InputListener::mouseMoved(evt);
}


// ##### FUNCTIONS

void App::setup(void)  {
	
	// Initialize scene
	//ResourceGroupManager::getSingleton().addResourceLocation("/home/dany/CLionProjects/ogrecam/media", "FileSystem");
	OgreBites::ApplicationContext::setup();
	
	Root* root = getRoot();

	//root->showConfigDialog();
	scnMgr = root->createSceneManager();
	addInputListener(this);
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);
	scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	createCamera();
	createLights();
	createObjects();
}

void App::createLights() {
	scnMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

	Light* pointLight = scnMgr->createLight("PointLight1");
	pointLight->setType(Light::LT_POINT);
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 5000, 5000);
	lightNode->attachObject(pointLight);
}


void App::createObjects() {
	//ninja
	Entity* ninjaEntity = scnMgr->createEntity("ninja.mesh");
	SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ninjaEntity);
	
	// create ManualObject
	//Line3D(scnMgr, Vector3(0,0,0), Vector3(100,100,100));
	//Point3D(scnMgr, Vector3(100,100,100));
	
	// spring
	//springs.push_back(LinearSpring(&physNodes[0], &physNodes[1], 10));
	std::vector<Vector3> points = { Vector3(0,0,0),Vector3(80,0,0),Vector3(100,100,0),Vector3(0,100,0),
							   Vector3(0,0,-100),Vector3(90,0,-100),Vector3(100,50,-100),Vector3(0,100,-100)};
	Cuboid cub(*scnMgr, points, "Simple/Red");
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(cub.manual);
	
	// ground
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
			"ground",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane,
			1500, 1500,
			20, 20,
			true,
			1, 5, 5,
			Vector3::UNIT_Z);
	Entity* groundEntity = scnMgr->createEntity("ground");
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
}

void App::createCamera() {
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5);
	cam->setAutoAspectRatio(true);
	getRenderWindow()->addViewport(cam);
	
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camGuy.setCamNode(camNode);
	camNode->setPosition(180, 50, 180);
	camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_PARENT);
	camNode->attachObject(cam);

}
