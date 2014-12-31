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
	int vtx[3];
public:
	Face(int, int, int);
	virtual ~Face();

	int getV1();
	int getV2();
	int getV3();
};

#endif /* FACE_H_ */
