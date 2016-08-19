/*
* File name: Ball.cpp
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

#include "Ball.hpp"
#include "Paddle.hpp"
#include "Definitions.hpp"

Ball::Ball(Ogre::SceneManager* const sceneMan) :
	mSceneManPtr(sceneMan),
	mNode(nullptr), 
	mSpeed(100), 
	mDirection(Ogre::Vector3(1, -1, 0)) {
	//
}

Ball::~Ball() {
	// TODO dtor
}

void Ball::addToScene() {
	Ogre::Entity *entityPtr = mSceneManPtr->createEntity("ball", "sphere.mesh");
	//entityPtr->setMaterialName("ball");
	mNode = mSceneManPtr->getRootSceneNode()->createChildSceneNode("ball");
	mNode->attachObject(entityPtr);
	mNode->setScale(Ogre::Vector3(.05F, .05F, .05F));
}

void Ball::move(const Ogre::Real time) {
	mNode->translate(mDirection * mSpeed * time);

	Ogre::Vector3 ballPos = mNode->getPosition();
	Ogre::Vector3 upperPos = mSceneManPtr->getSceneNode(UPPER_WALL_NAME)->getPosition();
	Ogre::Vector3 lowerPos = mSceneManPtr->getSceneNode(LOWER_WALL_NAME)->getPosition();
	Ogre::Vector3 leftPos = mSceneManPtr->getSceneNode(LEFT_WALL_NAME)->getPosition();
	Ogre::Vector3 rightPos = mSceneManPtr->getSceneNode(RIGHT_WALL_NAME)->getPosition();

	if ((ballPos.x - BALL_RADIUS) <= leftPos.x + (WALL_WIDTH / 2)) {
		// collides with left "wall", so left player +1
		mNode->setPosition(0, 0, 0);
		mSpeed = 100;
	} else if ((ballPos.x + BALL_RADIUS) >= rightPos.x - (WALL_WIDTH / 2)) {
		// collides with right "wall", so right player +1
		mNode->setPosition(0, 0, 0);
		mSpeed = 100;
	} else if ((ballPos.y - BALL_RADIUS) <= lowerPos.y + (WALL_WIDTH / 2) && mDirection.y < 0) {
		// ball collides with lower wall
		mDirection *= Ogre::Vector3(1, -1, 1); // invert direction
		mNode->setPosition(ballPos.x, (lowerPos.y + (WALL_WIDTH / 2) + BALL_RADIUS), ballPos.z);
	} else if ((ballPos.y + BALL_RADIUS) >= upperPos.y - (WALL_WIDTH / 2) && mDirection.y > 0) {
		// ball collides with upper wall
		mDirection *= Ogre::Vector3(1, -1, 1);
		mNode->setPosition(ballPos.x, (upperPos.y - (WALL_WIDTH / 2) - BALL_RADIUS), ballPos.z);
	}

	collide();
}

void Ball::collide() {
	Ogre::Vector3 leftPaddlePos = mSceneManPtr->getSceneNode(LEFT_PADDLE_NAME)->getPosition();
	Ogre::Vector3 rightPaddlePos = mSceneManPtr->getSceneNode(RIGHT_PADDLE_NAME)->getPosition();
	Ogre::Vector3 ballPos = mNode->getPosition();

	if ((ballPos.x - BALL_RADIUS) < (leftPaddlePos.x + (PADDLE_WIDTH / 2)))
	{
		if ((ballPos.y - BALL_RADIUS) < leftPaddlePos.y + (PADDLE_HEIGHT / 2) &&
			(ballPos.y + BALL_RADIUS) > (leftPaddlePos.y - (PADDLE_HEIGHT / 2)))
		{
			// collision detected!
			mDirection *= Ogre::Vector3(-1, 1, 1);
			mNode->setPosition(leftPaddlePos.x + (PADDLE_WIDTH / 2) + BALL_RADIUS, ballPos.y, ballPos.z);
			mSpeed += 10;
		}
	}
	else if ((ballPos.x + BALL_RADIUS) > (rightPaddlePos.x - (PADDLE_WIDTH / 2)))
	{
		if ((ballPos.y - BALL_RADIUS) < rightPaddlePos.y + (PADDLE_HEIGHT / 2)
			&& (ballPos.y + BALL_RADIUS) > (rightPaddlePos.y - (PADDLE_HEIGHT / 2)))
		{
			// collision detected!
			mDirection *= Ogre::Vector3(-1, 1, 1);
			mNode->setPosition(rightPaddlePos.x - (PADDLE_WIDTH / 2) - BALL_RADIUS, ballPos.y, ballPos.z);
			mSpeed += 10;
		}
	}
}