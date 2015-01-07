#include "AABB.h"
#include "visuals.h"

#include <iostream>

using namespace std;

AABB::AABB(float x_max, float y_max, float z_max, float x_min, float y_min, float z_min) {
	this->x_max = x_max;
	this->y_max = y_max;
	this->z_max = z_max;
	this->x_min = x_min;
	this->y_min = y_min;
	this->z_min = z_min;
}

AABB::~AABB() {}

void AABB::draw() {
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex3f(x_max, y_max, z_max);
	glVertex3f(x_max, y_min, z_max);
	glVertex3f(x_max, y_max, z_max);
	glVertex3f(x_max, y_max, z_min);
	glVertex3f(x_max, y_max, z_max);
	glVertex3f(x_min, y_max, z_max);

	glVertex3f(x_max, y_min, z_min);
	glVertex3f(x_max, y_min, z_max);
	glVertex3f(x_max, y_min, z_min);
	glVertex3f(x_max, y_max, z_min);
	glVertex3f(x_max, y_min, z_min);
	glVertex3f(x_min, y_min, z_min);

	glVertex3f(x_min, y_max, z_min);
	glVertex3f(x_min, y_min, z_min);
	glVertex3f(x_min, y_max, z_min);
	glVertex3f(x_min, y_max, z_max);
	glVertex3f(x_min, y_max, z_min);
	glVertex3f(x_max, y_max, z_min);

	glVertex3f(x_min, y_min, z_max);
	glVertex3f(x_min, y_max, z_max);
	glVertex3f(x_min, y_min, z_max);
	glVertex3f(x_min, y_min, z_min);
	glVertex3f(x_min, y_min, z_max);
	glVertex3f(x_max, y_min, z_max);

	glEnd();
	glPopMatrix();
}

bool AABB::intersects(AABB *box) {
	if ((box->z_max > this->z_min && box->z_min < this->z_max)
		&& (box->y_max > this->y_min && box->y_min < this->y_max)
		&& (box->x_max > this->x_min && box->x_min < this->x_max))
		return true;
	return false;
}

void AABB::print() {
	cout << "Printing Bounding Box" << endl;
	cout << " X: (" << x_min << ", " << x_max << ")" << endl;
	cout << " Y: (" << y_min << ", " << y_max << ")" << endl;
	cout << " Z: (" << z_min << ", " << z_max << ")" << endl;
}