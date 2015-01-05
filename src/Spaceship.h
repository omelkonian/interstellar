#pragma once
#include "Model.h"
#include "ObjectModel.h"
class Spaceship :
	public Model
{
public:
	Spaceship();
	~Spaceship();
	
	//methods
	void draw();
	void animate();

private:
	ObjectModel *ship;
	ObjectModel *torus;
};

