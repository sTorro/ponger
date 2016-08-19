/*
* File name: PongerApp.hpp
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

#pragma once
#ifndef _PONGER_APP_HPP_
#define _PONGER_APP_HPP_

#include <Ogre.h>
#include <OIS.h>

#include "Definitions.hpp"

#include "Paddle.hpp"
#include "Ball.hpp"

class PongerApp : public Ogre::FrameListener, public OIS::KeyListener {
 public:
	 PongerApp();
	virtual ~PongerApp();

	void start();

	// KeyListener
	bool keyPressed(const OIS::KeyEvent& keyEventRef);
	bool keyReleased(const OIS::KeyEvent& keyEventRef);

	// FrameListener
	bool frameStarted(const Ogre::FrameEvent& frameEventRef);
	bool frameEnded(const Ogre::FrameEvent& frameEventRef);

 private:
	inline void createScene();
	inline void createCamera();
	inline void createLights();
	inline void createContext();
	inline void prepareInput();
	inline void loadResources();
	inline bool setup();

 private:
	OIS::ParamList mParamList;

	Ogre::Root* mRoot;
	Ogre::SceneManager* mSceneManager;
	Ogre::RenderWindow* mWindow;
	Ogre::Viewport* mViewport;
	Ogre::Camera* mCamera;
	OIS::InputManager* mInputManager;
	OIS::Keyboard* mKeyboard;

	Ogre::Light* mMainLight;

	Paddle* mLeftPaddle;
	Paddle* mRightPaddle;
	Ball* mBall;

	bool mPause;
	bool mExit;
};

#endif // !_PONGER_APP_HPP_
