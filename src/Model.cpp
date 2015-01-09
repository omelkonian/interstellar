/*
 * Model.cpp
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Model.h"
#include "Asteroid.h"
#include "Spaceship.h"


using namespace std;

Model::Model() {
	timeOld = glutGet(GLUT_ELAPSED_TIME);
	speed = { 0, 0, 0 };
	acceleration = { 0, 0, 0 };
	position = { 0, 0, 0 };
	rspeed = { 0, 0, 0 };
	racceleration = { 0, 0, 0 };
	rposition = { 0, 0, 0 };
}


Model::~Model() {

}

void Model::doPhysics() {
	long timeNew = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (timeNew - timeOld)/1000.0f;
	//linear
	this->speed = this->speed + this->acceleration*deltaTime;
	this->position = this->position + this->speed*deltaTime;
	//rotation
	this->rspeed = this->rspeed + this->racceleration*deltaTime;
	this->rposition = this->rposition + this->rspeed*deltaTime;
}

void Model::draw() {
	this->doPhysics();
	
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glRotatef(this->rposition.x, 1, 0, 0);
	glRotatef(this->rposition.y, 0, 1, 0);
	glRotatef(this->rposition.z, 0, 0, 1);
}

void Model::print() {
	cout << "I'm an object" << endl;
}