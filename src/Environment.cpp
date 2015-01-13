#include "Environment.h"


Environment::Environment() : ObjectModel("resources/environment.obj")
{
	this->position = { 5, 5, -10 };
	this->scale = { 500, 500, 500 };
	this->rposition = { 0, 180, 0 };
	image = SOIL_load_image("resources/universe.jpg", &width, &height, &channels, SOIL_LOAD_RGB);
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
}


Environment::~Environment()
{
	glDeleteTextures(1, &texture);
}

void Environment::draw() {
	glDisable(GL_LIGHTING);
	glEnable(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	//glColor3f(1.0, 1.0, 1.0);
	ObjectModel::draw();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}
