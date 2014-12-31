/*
 * Point.h
 *
 *  Created on: 30 Δεκ 2014
 *      Author: Orestis Melkonian
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
	float x;
	float y;
	float z;
public:
	Point();
	Point(float, float, float);
	virtual ~Point();

	float getX();
	float getY();
	float getZ();

};

#endif /* POINT_H_ */
