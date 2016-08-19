/*
* File name: Ball.hpp
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
#ifndef _BALL_H_
#define _BALL_H_

#include <Ogre.h>

class Ball {
public:
	Ball(Ogre::SceneManager* const);
	~Ball();

	void addToScene();
	void move(const Ogre::Real);

private:
	Ogre::SceneManager* mSceneManPtr;
	Ogre::SceneNode* mNode;
	Ogre::int16 mSpeed;
	Ogre::Vector3 mDirection;

	void collide();
};

#endif // !_BALL_H_