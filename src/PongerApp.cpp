/*
* File name: PongerApp.cpp
*
* This file is part of Ponger project.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
* option) any later version. This program is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Ponger project. If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2016 Sergio Torró.
*/

#include "PongerApp.hpp"

PongerApp::PongerApp() : mRoot(new Ogre::Root()), mPause(false), mExit(false),
						mInputManager(nullptr), mKeyboard(nullptr), mCamera(nullptr),
						mSceneManager(nullptr), mWindow(nullptr), mViewport(nullptr),
						mMainLight(nullptr), mLeftPaddle(nullptr), mRightPaddle(nullptr),
						mBall(nullptr) {
	// 
}

PongerApp::~PongerApp() {
	mRoot->saveConfig();

	// Release input manager
	if (mInputManager) {
		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);
	}

	delete mRoot;
	mRoot = nullptr;
	// Ogre handles the other pointers
	
	// Game objects
	if (mBall) {
		delete mBall;
		mBall = nullptr;
	}

	if (mLeftPaddle) {
		delete mLeftPaddle;
		mLeftPaddle = nullptr;
	}

	if (mRightPaddle) {
		delete mRightPaddle;
		mRightPaddle = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////
// Public
void PongerApp::start() {
	if (setup()) {
		mWindow = mRoot->initialise(true, "Ponger");
		mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);

		createCamera();
		createLights();
		createContext(); // TODO create better context
		prepareInput();
		loadResources();

		mRoot->addFrameListener(this); // TODO create single frame listener

		loadResources();
		createScene();

		mRoot->startRendering();
	} else {
		// show error ?
	}
}

// KeyListener
bool PongerApp::keyPressed(const OIS::KeyEvent& keyEventRef) {
	if (!mPause) {
		switch (keyEventRef.key) {
			case OIS::KC_ESCAPE:
				mExit = true;
				break;

			case OIS::KC_UP:
				mRightPaddle->move(UP);
				break;

			case OIS::KC_DOWN:
				mRightPaddle->move(DOWN);
				break;

			case OIS::KC_A:
				mLeftPaddle->move(UP);
				break;

			case OIS::KC_Z:
				mLeftPaddle->move(DOWN);
				break;

			case OIS::KC_P:
				mPause = true;
				break;
		}
	} else { // game paused
		if (keyEventRef.key == OIS::KC_P) mPause = false;
	}

	return true;
}

bool PongerApp::keyReleased(const OIS::KeyEvent& keyEventRef) {
	return true; // not needed
}

// FrameListener
bool PongerApp::frameStarted(const Ogre::FrameEvent& frameEventRef) {
	// main game loop
	mKeyboard->capture();
	if (!mPause) 
		mBall->move(frameEventRef.timeSinceLastFrame);

	return !mExit;
}

bool PongerApp::frameEnded(const Ogre::FrameEvent& frameEventRef) {
	return !mExit; // true if program may render next frame
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Private
void PongerApp::createScene() {
	mBall = new Ball(mSceneManager);
	mBall->addToScene();

	mRightPaddle = new Paddle(mSceneManager, RIGHT_PADDLE_NAME, 80);
	mRightPaddle->addToScene();
	mLeftPaddle = new Paddle(mSceneManager, LEFT_PADDLE_NAME, -80);
	mLeftPaddle->addToScene();

	//pared izquierda
	Ogre::Entity *entityPtr = mSceneManager->createEntity(LEFT_WALL_NAME, "cube.mesh");
	//entityPtr->setMaterialName("pared");
	Ogre::SceneNode *nodoPtr = mSceneManager->getRootSceneNode()->createChildSceneNode(LEFT_WALL_NAME);
	nodoPtr->attachObject(entityPtr);
	nodoPtr->setPosition(-95, 0, 0);
	nodoPtr->setScale(0.05, 1.45, 0.1);

	//pared derecha
	entityPtr = mSceneManager->createEntity(RIGHT_WALL_NAME, "cube.mesh");
	//entityPtr->setMaterialName("pared");
	nodoPtr = mSceneManager->getRootSceneNode()->createChildSceneNode(RIGHT_WALL_NAME);
	nodoPtr->attachObject(entityPtr);
	nodoPtr->setPosition(95, 0, 0);
	nodoPtr->setScale(0.05, 1.45, 0.1);

	//pared inferior
	entityPtr = mSceneManager->createEntity(LOWER_WALL_NAME, "cube.mesh");
	//entityPtr->setMaterialName("pared");
	nodoPtr = mSceneManager->getRootSceneNode()->createChildSceneNode(LOWER_WALL_NAME);
	nodoPtr->attachObject(entityPtr);
	nodoPtr->setPosition(0, -70, 0);
	nodoPtr->setScale(1.95, .05, .1);

	//pared superior
	entityPtr = mSceneManager->createEntity(UPPER_WALL_NAME, "cube.mesh");
	//entityPtr->setMaterialName("pared");
	nodoPtr = mSceneManager->getRootSceneNode()->createChildSceneNode(UPPER_WALL_NAME);
	nodoPtr->attachObject(entityPtr);
	nodoPtr->setPosition(0, 70, 0);
	nodoPtr->setScale(1.95, .05, .1);
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Inlined
void PongerApp::createCamera() {
	mCamera = mSceneManager->createCamera("MainCamera");
	mCamera->setPosition(Ogre::Vector3(0, 0, 200));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5);
	mCamera->setFarClipDistance(1000);

	// Viewport
	mViewport = mWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);

	auto aspectRatio(mViewport->getActualWidth() / mViewport->getActualHeight());
	mCamera->setAspectRatio(aspectRatio);
}

void PongerApp::createLights() {
	mSceneManager->setAmbientLight(Ogre::ColourValue(.75F, .75F, .75F));
	mMainLight = mSceneManager->createLight("MainLight");
	mMainLight->setPosition(.0F, .0F, .5F);
}

void PongerApp::createContext() {
	unsigned long hWnd;
	mWindow->getCustomAttribute("WINDOW", &hWnd);
	mParamList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
}

void PongerApp::prepareInput() {
	mInputManager = OIS::InputManager::createInputSystem(mParamList);
	mKeyboard = static_cast<OIS::Keyboard *>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mKeyboard->setEventCallback(this); // TODO create single input system
}

void PongerApp::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("..\\..\\dist\\media\\models",
		"FileSystem",
		"models");
}

bool PongerApp::setup() {
	return mRoot->restoreConfig() ? true : mRoot->showConfigDialog();
}
//////////////////////////////////////////////////////////////////////////////////
