#pragma once

#include "Model.h"
#include "ObjectModel.h"
#include "AABB.h"
#include "Defines.h"

class Spaceship :
	public Model
{
public:
	Spaceship(GLdouble look = 0.0f);
	~Spaceship();

	//methods
	void draw();
	void animate();
	void doPhysics();

	AABB* getAABB();

	void printPosition();
private:
	GLdouble look;
	ObjectModel *ship;
	ObjectModel *torus;
	ObjectModel *torus2;
};

