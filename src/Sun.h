#pragma once

#include "Model.h"
#include "ObjectModel.h"

class Sun : public Model {
public:
	// Inner Sphere
	ObjectModel *innerSphere;

	// Outer Sphere
	GLdouble outerRadius;
	GLdouble outerRadiusMin;
	GLdouble outerRadiusMax;

	bool addition;

	Sun();
	virtual ~Sun();

	void draw();
	void animate();

	void print();
};