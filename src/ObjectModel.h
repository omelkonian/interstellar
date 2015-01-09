#pragma once
#include "Model.h"
#include "AABB.h"
#include "../gl/glm/glm.hpp"

class ObjectModel :
	public Model
{
public:
	ObjectModel(const char * file);
	~ObjectModel();

	void draw();
	void print();

	AABB* getAABB();

protected:
	GLfloat* _vertices;
	GLfloat* _normals;
	GLuint* _faces;
	GLfloat* _texels;
	GLuint * _indices;
	int vertices;
	int faces;
	int normals;
	int texels;
	

	//helping functions
	int preproccessFile(const char * filename);
	int load_obj(const char * filename);
};

