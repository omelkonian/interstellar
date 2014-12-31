/*
 * Face.cpp
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#include "Face.h"

Face::Face(int v1, int v2, int v3) {
	this->vtx[0] = v1;
	this->vtx[1] = v2;
	this->vtx[2] = v3;
}

int Face::getV1() {
	return this->vtx[0];
}

int Face::getV2() {
	return this->vtx[1];
}

int Face::getV3() {
	return this->vtx[1];
}

Face::~Face() {
}

