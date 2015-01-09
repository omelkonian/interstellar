#pragma once

#include "Model.h"
#include "ObjectModel.h"
#include "AABB.h"

class Spaceship :
	public Model
{
public:
	Spaceship();
	~Spaceship();

	//methods
	void draw();
	void animate();

	AABB* getAABB();

	void printPosition();
private:
	ObjectModel *ship;
	ObjectModel *torus;
};

