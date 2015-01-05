#pragma once

#include "Model.h"

class Sun : public Model {
public:
	// Inner Sphere
	GLdouble innerRadius;

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