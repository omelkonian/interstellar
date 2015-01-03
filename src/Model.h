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

class Model {
	Point** obj_points;
	Face** obj_faces;
	int vertices;
	int faces;
public:
	Model(int, int);
	virtual ~Model();

	int getVertices();
	void setVertices(int);

	int getFaces();
	void setFaces(int);

	Point** getObjPoints();
	Face** getObjFaces();

	void print();
};

#endif /* MODEL_H_ */
