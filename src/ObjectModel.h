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
	glm::vec3* _vertices;
	glm::vec3* _normals;
	glm::vec2* _texels;
	
	int faces;

	//helping functions
	int preproccessFile(const char * filename);
	int load_obj(const char * filename);
private:
	int vertices;
	int normals;
	int texels;
	glm::vec3 *verticesFile;
	glm::vec2 *texCoordsFile;
	glm::vec3 *normalsFile;
};

