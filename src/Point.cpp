/*
 * Point.cpp
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */
#include <iostream>
#include "Point.h"

using namespace std;

Point::Point() {}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Point::getX(){
	return this->x;
}

float Point::getY(){
	return this->y;
}

float Point::getZ(){
	return this->z;
}

Point::~Point() {}

void Point::print() {
	cout << "________Printing Point__________" << endl;
	cout << "X: " << this->x << endl;
	cout << "Y: " << this->y << endl;
	cout << "Z: " << this->z << endl;
}