/*
 * Point.h
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#ifndef POINT_H_
#define POINT_H_
#include <cstdio>
#include <cstdlib>
#include "../gl/glut.h"

class Point {
	GLfloat x;
	GLfloat y;
	GLfloat z;
public:
	Point();
	Point(float, float, float);
	virtual ~Point();

	float getX();
	float getY();
	float getZ();

	void print();
};

#endif /* POINT_H_ */
