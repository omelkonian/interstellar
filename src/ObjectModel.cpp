#include "ObjectModel.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

ObjectModel::ObjectModel(const char * file) : Model()
{
		this->faces = this->normals = this->texels = this->vertices = 0;
		this->preproccessFile(file);
		this->_vertices = (GLfloat*)malloc(this->vertices * sizeof(GLfloat) * 3);
		this->_texels = (GLfloat*)malloc(this->texels* sizeof(GLfloat) * 2);
		this->_normals = (GLfloat*)malloc(this->normals * sizeof(GLfloat) * 3);
		this->_faces = (GLuint*)malloc(this->faces * sizeof(GLuint) * 9);
		this->_indices = (GLuint*)malloc(this->faces * sizeof(GLuint) * 3);
		this->load_obj(file);
		//this->print();
}


ObjectModel::~ObjectModel()
{
}

int ObjectModel::preproccessFile(const char * filename) {
	string line;
	ifstream obj_file(filename, ifstream::in);
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
	GLfloat * $vertice = this->_vertices;
	GLfloat * $normal = this->_normals;
	GLfloat * $texel = this->_texels;
	GLuint * $face = this->_faces;
	GLuint * $index = this->_indices;

	ifstream obj_file(filename, ifstream::in);
	while (getline(obj_file, line)) {
		if (line.substr(0, 2) == "v ") { //vertices
			GLfloat x, y, z;
			sscanf_s(line.substr(2).c_str(), "%f %f %f", &x, &y, &z);
			$vertice[0] = x;
			$vertice[1] = y;
			$vertice[2] = z;
			$vertice += 3;
		}
		else if (line.substr(0, 2) == "vn") { //normals
			GLfloat x, y, z;
			sscanf_s(line.substr(2).c_str(), "%f %f %f", &x, &y, &z);
			$normal[0] = x;
			$normal[1] = y;
			$normal[2] = z;
			$normal += 3;
		}
		else if (line.substr(0, 2) == "vt") { //texels
			GLfloat u, v;
			sscanf_s(line.substr(2).c_str(), "%f %f", &u, &v);
			$texel[0] = u;
			$texel[1] = v;
			$texel += 2;
		}
		else if (line.substr(0, 2) == "f ") { //faces
			GLint v[3], vt[3], vn[3];
			sscanf_s(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &(v[0]), &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2]);
			$face[0] = v[0] - 1;
			$face[1] = vt[0];
			$face[2] = vn[0];
			$face[3] = v[1] - 1;
			$face[4] = vt[1];
			$face[5] = vn[1];
			$face[6] = v[2] - 1;
			$face[7] = vt[2];
			$face[8] = vn[2];
			$face += 9;
			$index[0] = v[0] - 1;
			$index[1] = v[1] - 1;
			$index[2] = v[2] - 1;
			$index += 3;
		}
	}
	obj_file.close();
	return 0;
}

void ObjectModel::draw() {
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, this->_normals);
	//glIndexPointer(GL_INT, 3, this->_faces);
	//glColorPointer(3, GL_FLOAT, 0, colors1);
	glVertexPointer(3, GL_FLOAT, 0, this->_vertices);

	Model::draw();
	glDrawElements(GL_TRIANGLES, this->faces * 3, GL_UNSIGNED_INT, this->_indices);

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
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
		printf("f %d/%d/%d", this->_faces[9 * i], this->_faces[9 * i + 1], this->_faces[9 * i + 2]);
		printf(" %d/%d/%d", this->_faces[9 * i + 3], this->_faces[9 * i + 4], this->_faces[9 * i + 5]);
		printf(" %d/%d/%d\n", this->_faces[9 * i + 6], this->_faces[9 * i + 7], this->_faces[9 * i + 8]);
	}
	for (int i = 0; i < this->faces; i++) {
		//printf("i %d %d %d\n", this->_indices[3 * i], this->_indices[3 * i + 1], this->_indices[3 * i + 2]);
	}
}