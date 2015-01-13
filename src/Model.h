/*
 * Model.h
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#pragma comment(lib, "gl/libSOIL.lib")
#include "../gl/glm/glm.hpp"
#include "../gl/glut.h"
#include "../gl/SOIL.h"
#include "AABB.h"

class Model : public AABB{
public:
	//linear variables
	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 acceleration;
	//rotational variables
	glm::vec3 rposition;
	glm::vec3 rspeed;
	glm::vec3 racceleration;
	//scale
	glm::vec3 scale;
	//time
	long timeOld;
	//############## methods #####################
	//default constructor
	Model();
	//constructor with initial linear values
	Model(glm::vec3 pos, glm::vec3 speed);
	virtual ~Model();
	virtual void doPhysics();
	//abstract methods
	//method draw has implementation and should be called first in derived implementation.
	virtual void draw() = 0;
	virtual void print();
	virtual void animate() {};
};

