#pragma once

// Axis-aligned bounding box.
class AABB {
public:
	float x_max;
	float y_max;
	float z_max;
	float x_min;
	float y_min;
	float z_min;

	AABB(float, float, float, float, float, float);
	virtual ~AABB();

	void draw();
	void print();

	bool intersects(AABB*);
};