#include "Text.h"
#include "visuals.h"

Text::Text(char *text, float size, glm::vec3 position) {
	this->text = (char*)malloc(strlen(text));
	strcpy(this->text, text);
	this->size = size;
	this->position = { position.x - 5, position.y, position.z + 25 };
	this->color = { 1, 0, 0 };
}

Text::~Text() {}

void Text::draw() {
	glPushMatrix();
	glColor3f(this->color.x, this->color.y, this->color.z);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glScalef(size, size, size);

	for (int i = 0; i < strlen(this->text); i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, this->text[i]);

	glPopMatrix();
}