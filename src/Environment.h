#pragma once
#include "ObjectModel.h"
class Environment :
	public ObjectModel
{
private:
	int width;
	int height;
	int channels;
	GLuint texture;
	unsigned char * image;
public:
	Environment();
	~Environment();
	void draw();
};

