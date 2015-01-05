/*
 * Face.h
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#ifndef FACE_H_
#define FACE_H_

// Faces are triangles only.
class Face {
public:
	int vertices[3];
	int texels[3];
	int normals[3];
	Face(int[3], int[3], int[3]);
	virtual ~Face();

	int getV1();
	int getV2();
	int getV3();

	void print();
};

#endif /* FACE_H_ */
