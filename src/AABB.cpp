#include "AABB.h"
#include "visuals.h"

#include <iostream>

using namespace std;
using namespace glm;

AABB::AABB(float max_x, float max_y, float max_z, float min_x, float min_y, float min_z) {
	this->max.x = max_x;
	this->max.y = max_y;
	this->max.z = max_z;
	this->min.x = min_x;
	this->min.y = min_y;
	this->min.z = min_z;
	this->positionBound = NULL;
}

AABB::AABB(vec3 min, vec3 max, vec3 *position) : minInit(min), maxInit(max), positionBound(position){
	min = minInit + *position;
	max = maxInit + *position;
}

//AABB::AABB(ObjectModel const &model) {
//	this->model = &model;
//}

AABB::~AABB() {}

void AABB::drawBounds() {
	this->updateBounds();
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(max.x, max.y, max.z);
	glVertex3f(max.x, min.y, max.z);
	glVertex3f(max.x, max.y, max.z);
	glVertex3f(max.x, max.y, min.z);
	glVertex3f(max.x, max.y, max.z);
	glVertex3f(min.x, max.y, max.z);

	glVertex3f(max.x, min.y, min.z);
	glVertex3f(max.x, min.y, max.z);
	glVertex3f(max.x, min.y, min.z);
	glVertex3f(max.x, max.y, min.z);
	glVertex3f(max.x, min.y, min.z);
	glVertex3f(min.x, min.y, min.z);

	glVertex3f(min.x, max.y, min.z);
	glVertex3f(min.x, min.y, min.z);
	glVertex3f(min.x, max.y, min.z);
	glVertex3f(min.x, max.y, max.z);
	glVertex3f(min.x, max.y, min.z);
	glVertex3f(max.x, max.y, min.z);

	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, max.y, max.z);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, min.y, min.z);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(max.x, min.y, max.z);

	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

bool AABB::intersects(AABB *box) {
	this->updateBounds();
	box->updateBounds();
	if ((box->max.z > this->min.z && box->min.z < this->max.z)
		&& (box->max.y > this->min.y && box->min.y < this->max.y)
		&& (box->max.x > this->min.x && box->min.x < this->max.x))
		return true;
	return false;
}

bool AABB::withinBounds(glm::vec3 pos) {
	if ((pos.x > max.x) || (pos.x < min.x))
		return false;
	if ((pos.y > max.y) || (pos.y < min.y))
		return false;
	if ((pos.z > max.z) || (pos.z < min.z))
		return false;
	return true;
}

void AABB::updateBounds() {
	max = maxInit + *positionBound;
	min = minInit + *positionBound;
}
void AABB::printBounds() {
	cout << "Printing Bounding Box" << endl;
	cout << " X: (" << min.x << ", " << max.x << ")" << endl;
	cout << " Y: (" << min.y << ", " << max.y << ")" << endl;
	cout << " Z: (" << min.z << ", " << max.z << ")" << endl;
}