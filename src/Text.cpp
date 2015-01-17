#include "Text.h"
#include "visuals.h"

using namespace std;

Text::Text(const char *text, float size, glm::vec3 position) {
	this->text = (char*)malloc(MAX_TEXT_LENGTH);
	strcpy(this->text, (char*)text);
	this->size = size;
	this->position = { position.x, position.y, position.z };
	this->color = { 1, 1, 1 };
}

Text::~Text() {
	//free(this->text);
}

void Text::draw() {
	glPushMatrix();

	glDisable(GL_LIGHTING);
	
	glColor3f(this->color.x, this->color.y, this->color.z);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glScalef(size, size, size);

	for (int i = 0; i < strlen(this->text); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, this->text[i]);

	glEnable(GL_LIGHTING);

	glPopMatrix();
}