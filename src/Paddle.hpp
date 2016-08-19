/*
* File name: Paddle.hpp
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
#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <Ogre.h>

class Paddle {
public:
	Paddle(Ogre::SceneManager* const, const Ogre::String&, const Ogre::int8);
	~Paddle();

	void addToScene();
	void move(const Ogre::Vector3&);

private:
	Ogre::SceneManager* mSceneManPtr;
	Ogre::SceneNode* mNode;
	Ogre::String mName;
	Ogre::int8 mPosX;
};


#endif // !_PADDLE_H_