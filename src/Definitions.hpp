/*
* File name: Definitions.hpp
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
#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_

const Ogre::String RIGHT_PADDLE_NAME("RightPaddle");
const Ogre::String LEFT_PADDLE_NAME("LeftPaddle");

const Ogre::String UPPER_WALL_NAME("UpperWall");
const Ogre::String LOWER_WALL_NAME("LowerWall");
const Ogre::String LEFT_WALL_NAME("LeftWall");
const Ogre::String RIGHT_WALL_NAME("RightWall");

const Ogre::Vector3 DOWN(0, -25, 0);
const Ogre::Vector3 UP(0, 25, 0);

const Ogre::int8 BALL_RADIUS = 5;
const Ogre::int8 PADDLE_WIDTH = 2;
const Ogre::int8 PADDLE_HEIGHT = 30;
const Ogre::int8 WALL_WIDTH = 5;

#endif // !_DEFINITIONS_HPP_
