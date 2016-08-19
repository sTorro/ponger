/*
* File name: Paddle.cpp
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

#include "Paddle.hpp"

Paddle::Paddle(Ogre::SceneManager* const sceneMan, const Ogre::String& name, const Ogre::int8 posX) :
	mSceneManPtr(sceneMan),
	mNode(nullptr),
	mName(name),
	mPosX(posX) {
	//
}

Paddle::~Paddle(void) {
	// TODO dtor
}

void Paddle::addToScene() {
	Ogre::Entity* entityPtr = mSceneManPtr->createEntity(mName, "cube.mesh");
	//entityPtr->setMaterialName(material);
	mNode = mSceneManPtr->getRootSceneNode()->createChildSceneNode(mName);
	mNode->attachObject(entityPtr);
	mNode->setScale(0.02, 0.3, 0.1);
	mNode->setPosition(mPosX, 0, 0);
}

void Paddle::move(const Ogre::Vector3& dir) {
	mNode->translate(dir);
	if (mNode->getPosition().y > 52.5) mNode->setPosition(mPosX, 52.5, 0);
	else if (mNode->getPosition().y < -52.5) mNode->setPosition(mPosX, -52.5, 0);
}
