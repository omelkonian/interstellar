#include "ObjectModel.h"
#include "Asteroid.h"
#include "Defines.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <sstream>


using namespace std;
using namespace glm;

ObjectModel::ObjectModel(ObjectModel *cpy) : Model()
{
	this->position = cpy->position;
	this->speed = cpy->speed;
	this->acceleration = cpy->acceleration;
	this->rposition = cpy->rposition;
	this->rspeed = cpy->rspeed;
	this->racceleration = cpy->racceleration;
	this->_vertices = cpy->_vertices;
	this->_normals = cpy->_normals;
	this->_texels = cpy->_texels;
	this->faces = cpy->faces;
	this->vertices = cpy->vertices;
	this->normals = cpy->normals;
	this->texels = cpy->texels;
	this->verticesFile = cpy->verticesFile;
	this->texCoordsFile = cpy->texCoordsFile;
	this->normalsFile = cpy->normalsFile;
}

ObjectModel::ObjectModel(const char * file, const char * texture) : Model()
{
	//printf("Constructing object from [%s] with texture [%s]\n", file, (texture != NULL) ? texture : "");
	this->faces = this->normals = this->texels = this->vertices = 0;
	this->preproccessFile(file);
	this->faces *= 3;
	this->verticesFile = (vec3 *)malloc(this->vertices * sizeof(vec3));
	this->texCoordsFile = (vec2 *)malloc(this->texels * sizeof(vec2));
	this->normalsFile = (vec3 *)malloc(this->normals * sizeof(vec3));
	this->_vertices = (vec3*)malloc(this->faces * sizeof(vec3));
	this->_texels = (vec2*)malloc(this->faces* sizeof(vec2));
	this->_normals = (vec3*)malloc(this->faces * sizeof(vec3));
	this->load_obj(file);
	constructBounds();
	this->texture = (texture != NULL) ? (loadTexture(texture)) : 0;
}

void ObjectModel::freeResources() {
	free(this->_vertices);
	free(this->_texels);
	free(this->_normals);
}

ObjectModel::~ObjectModel() {
	return;
	if (texture != 0) {
		glDeleteTextures(1, &texture);
	}
	free(this->verticesFile);
	free(this->texCoordsFile);
	free(this->normalsFile);
}

int ObjectModel::preproccessFile(const char * filename) {
	string line;
	ifstream obj_file(filename, ifstream::in);

	if (obj_file.fail())
		cout << "ERROR: Unable to open " << filename << endl;

	while (getline(obj_file, line)) {
		if (line.substr(0, 2) == "v ") {
			this->vertices++;
		}
		else if (line.substr(0, 2) == "vn") {
			this->normals++;
		}
		else if (line.substr(0, 2) == "vt") {
			this->texels++;
		}
		else if (line.substr(0, 2) == "f ") {
			this->faces++;
		}
	}
	obj_file.close();
	return 0;
}

int ObjectModel::load_obj(const char * filename) {
	string line;
	vec3 *$vertice = verticesFile;
	vec3 *$normal = normalsFile;
	vec2 *$texel = texCoordsFile;
	int face = 0;

	ifstream obj_file(filename, ifstream::in);
	while (getline(obj_file, line)) {
		if (line.substr(0, 2) == "v ") { //vertices
			GLfloat x, y, z;
			sscanf_s(line.substr(2).c_str(), "%f %f %f", &x, &y, &z);
			$vertice->x = x;
			$vertice->y = y;
			$vertice->z = z;
			$vertice++;
		}
		else if (line.substr(0, 2) == "vn") { //normals
			GLfloat x, y, z;
			sscanf_s(line.substr(2).c_str(), "%f %f %f", &x, &y, &z);
			$normal->x = x;
			$normal->y = y;
			$normal->z = z;
			$normal++;
		}
		else if (line.substr(0, 2) == "vt") { //texels
			GLfloat u, v;
			sscanf_s(line.substr(2).c_str(), "%f %f", &u, &v);
			$texel->x = u;
			$texel->y = v;
			$texel++;
		}
		else if (line.substr(0, 2) == "f ") { //faces
			GLint v[3], vt[3], vn[3];
			sscanf_s(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &(v[0]), &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2]);
			//faces are last, so the arrays are already populated
			this->_vertices[face] = verticesFile[v[0] - 1];
			this->_vertices[face + 1] = verticesFile[v[1] - 1];
			this->_vertices[face + 2] = verticesFile[v[2] - 1];
			this->_texels[face] = texCoordsFile[vt[0] - 1];
			this->_texels[face + 1] = texCoordsFile[vt[1] - 1];
			this->_texels[face + 2] = texCoordsFile[vt[2] - 1];
			this->_normals[face] = normalsFile[vn[0] - 1];
			this->_normals[face + 1] = normalsFile[vn[1] - 1];
			this->_normals[face + 2] = normalsFile[vn[2] - 1];
			face += 3;

		}
	}
	obj_file.close();
	return 0;
}

void ObjectModel::draw() {
	if (texture != 0) {
		glEnable(GL_SMOOTH);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glPushMatrix();
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, this->_vertices);
	glNormalPointer(GL_FLOAT, 0, this->_normals);
	glTexCoordPointer(2, GL_FLOAT, 0, this->_texels);

	Model::draw();
	glDrawArrays(GL_TRIANGLES, 0, this->faces);

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glPopMatrix();
	if (texture != 0) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_SMOOTH);
	}
}

void ObjectModel::constructBounds() {
	this->minInit = { +FLT_MAX, +FLT_MAX, +FLT_MAX };
	this->maxInit = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
	
	for (int i = 0; i < this->vertices; i++) {
		glm::vec3 vertex = this->_vertices[i];

		float x = vertex.x + this->position.x;
		float y = vertex.y + this->position.y;
		float z = vertex.z + this->position.z;

		if (x > max.x) maxInit.x = x;
		if (x < min.x) minInit.x = x;
		if (y > max.y) maxInit.y = y;
		if (y < min.y) minInit.y = y;
		if (z > max.z) maxInit.z = z;
		if (z < min.z) minInit.z = z;
	}
	maxInit *= this->scale;
	minInit *= this->scale;
}

void ObjectModel::print() {
	cout << "________Printing Model____________ " << endl;
	for (int i = 0; i < this->vertices; i++) {
		printf("v %f %f %f\n", this->_vertices[3 * i], this->_vertices[3 * i + 1], this->_vertices[3 * i + 2]);
	}
	for (int i = 0; i < this->normals; i++) {
		printf("vn %f %f %f\n", this->_normals[3 * i], this->_normals[3 * i + 1], this->_normals[3 * i + 2]);
	}
	for (int i = 0; i < this->texels; i++) {
		printf("vt %f %f %f\n", this->_texels[2 * i], this->_texels[2 * i + 1]);
	}
	for (int i = 0; i < this->faces; i++) {
		//printf("f %d/%d/%d", this->_faces[9 * i], this->_faces[9 * i + 1], this->_faces[9 * i + 2]);
		//printf(" %d/%d/%d", this->_faces[9 * i + 3], this->_faces[9 * i + 4], this->_faces[9 * i + 5]);
		//printf(" %d/%d/%d\n", this->_faces[9 * i + 6], this->_faces[9 * i + 7], this->_faces[9 * i + 8]);
	}
	for (int i = 0; i < this->faces; i++) {
		//printf("i %d %d %d\n", this->_indices[3 * i], this->_indices[3 * i + 1], this->_indices[3 * i + 2]);
	}
}

GLuint ObjectModel::loadTexture(const char * textureName) {
	unsigned char * image;
	unsigned int texture;
	printf("Loading texture [%s]\n", textureName);
	image = SOIL_load_image(textureName, &width, &height, &channels, SOIL_LOAD_RGB);
	assert(image != NULL);
	glGenTextures(1, &texture);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// when texture area is small, bilinear filter the closest MIP map
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first MIP map
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// if wrap is true, the texture wraps over at the edges (repeat)
	//       ... false, the texture ends at the edges (clamp)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// build our texture MIP maps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width,
		height, GL_RGB, GL_UNSIGNED_BYTE, image);

	// free buffer
	SOIL_free_image_data(image);
	return texture;
}