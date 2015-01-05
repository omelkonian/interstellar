/*
 * Model.h
 *
 *  Created on: 30 ��� 2014
 *      Author: Orestis Melkonian
 */

#pragma once

#include "../gl/glm/glm.hpp"
#include "../gl/glut.h"
#include "../gl/SOIL.h"

class Model {
private:
	long timeOld;

public:
	//linear variables
	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 acceleration;
	//rotational variables
	glm::vec3 rposition;
	glm::vec3 rspeed;
	glm::vec3 racceleration;

	//############## methods #####################
	//default constructor
	Model();
	//constructor with initial linear values
	Model(glm::vec3 pos, glm::vec3 speed);
	virtual ~Model();
	void doPhysics();
	//abstract methods
	//method draw has implementation and should be called first in derived implementation.
	virtual void draw() = 0;
	virtual void print() = 0;
};

