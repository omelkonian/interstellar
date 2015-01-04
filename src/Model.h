/*
 * Model.h
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Point.h"
#include "Face.h"
#include <vector>
#include "../gl/glut.h"

class Model {
	//std::vector<Point> obj_points;
	//std::vector<Face> obj_faces;
	GLfloat* _vertices;
	GLfloat* _normals;
	GLint* _faces;
	GLfloat* _texels;
	GLint * _indices;
	int vertices;
	int faces;
	int normals;
	int texels;
	Point position;
	float rotation[3]; // XYZ rotation angles

	//helping functions
	int preproccessFile(const char * filename);
	int load_obj(const char * filename);
public:
	Model(int, int);
	Model(const char * file);
	virtual ~Model();
	//operations

	//sets the rotation 
	int setRotate(float x, float y, float z);
	//increments the rotation
	int rotate(float x, float y, float z);
	//moves the object
	int move(Point where);
	//sets the object position
	int place(Point where);
	//draws the object
	void draw();
	//getters setters
	int getVertices();
	void setVertices(int);

	int getFaces();
	void setFaces(int);

	Point* getObjPoints();
	Face* getObjFaces();

	void print();
};

#endif /* MODEL_H_ */
