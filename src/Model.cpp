/*
 * Model.cpp
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#include "Model.h"
#include <cstdlib>

Model::Model(int vertices, int faces) {
	this->vertices = vertices;
	this->faces = faces;

	this->obj_points = (Point**)malloc(vertices * sizeof(Point*));
	this->obj_faces = (Face**)malloc(faces * sizeof(Face*));
}

Model::~Model() {
}

int Model::getVertices() {
	return this->vertices;
}
void Model::setVertices(int vertices) {
	this->vertices = vertices;
}

int Model::getFaces() {
	return this->faces;
}
void Model::setFaces(int faces) {
	this->faces = faces;
}

Point** Model::getObjPoints() {
	return this->obj_points;
}
Face** Model::getObjFaces() {
	return this->obj_faces;
}
