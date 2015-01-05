/*
 * Face.cpp
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#include "Face.h"
#include <iostream>

using namespace std;

Face::Face(int vertices[3], int texels[3], int normals[3]) {
	memcpy(this->vertices, vertices, 3 * sizeof(int));
	memcpy(this->texels, texels, 3 * sizeof(int));
	memcpy(this->normals, normals, 3 * sizeof(int));
}

Face::~Face() {
}

/*void Face::print() {
	cout << "_________Printing Face_________" << endl;
	cout << "V1: " << this->vtx[0] << endl;
	cout << "V2: " << this->vtx[1] << endl;
	cout << "V3: " << this->vtx[2] << endl;
} */