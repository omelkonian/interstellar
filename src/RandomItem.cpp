#include "RandomItem.h"
#include "visuals.h"

RandomItem::RandomItem() : Model() {}

void RandomItem::randomize() {
	this->position = { this->position.x + randFloat(-4, 4), this->position.y + randFloat(-4, 4), this->position.z + randFloat(-4, 4) };
	this->speed = { randFloat(RANDOM_ITEM_MIN_SPEED, RANDOM_ITEM_MAX_SPEED), randFloat(RANDOM_ITEM_MIN_SPEED, RANDOM_ITEM_MAX_SPEED), randFloat(RANDOM_ITEM_MIN_SPEED, RANDOM_ITEM_MAX_SPEED) };
	this->rspeed = { randFloat(RANDOM_ITEM_MIN_ROT_SPEED, RANDOM_ITEM_MAX_ROT_SPEED), randFloat(RANDOM_ITEM_MIN_ROT_SPEED, RANDOM_ITEM_MAX_ROT_SPEED), randFloat(RANDOM_ITEM_MIN_ROT_SPEED, RANDOM_ITEM_MAX_ROT_SPEED) };
	this->color = { randFloat(0.1, 1), randFloat(0.1, 1), randFloat(0.1, 1) };
	this->shape = rand() % 7;
}

RandomItem::~RandomItem(){}

void RandomItem::draw() {
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	Model::draw();
	
	glColor3f(this->color.x, this->color.y, this->color.z);

	switch (this->shape) {
	case 0: // cone
		glScalef(randFloat(2, 3), randFloat(2, 3), randFloat(2, 3));
		glutSolidCone(1, 1, 50, 50);
		break;
	case 1: // cube
		glScalef(randFloat(2, 3), randFloat(2, 3), randFloat(2, 3));
		glutSolidCube(1);
		break;
	case 2: // octahedron
		glScalef(randFloat(2, 3), randFloat(2, 3), randFloat(2, 3));
		glutSolidOctahedron();
		break;
	case 3: // dodecahedron
		glScalef(randFloat(2, 3), randFloat(2, 3), randFloat(2, 3));
		glutSolidDodecahedron();
		break;
	case 4: // sphere
		glutSolidSphere(randFloat(1, 3), 50, 50);
		break;
	case 5: // triangle
		glBegin(GL_TRIANGLES);
		glVertex3f(this->position.x, this->position.y, this->position.z);
		glVertex3f(this->position.x + randFloat(0.5, 3), this->position.y + randFloat(0.5, 3), this->position.z + randFloat(0.5, 3));
		glVertex3f(this->position.x + randFloat(-3, -0.5), this->position.y + randFloat(-3, -0.5), this->position.z + randFloat(-3, -0.5));
		glEnd();
		break;
	case 6: // square
		glBegin(GL_QUADS);
		glVertex3f(this->position.x, this->position.y, this->position.z);
		glVertex3f(this->position.x + randFloat(0.5, 3), this->position.y + randFloat(0.5, 3), this->position.z + randFloat(0.5, 3));
		glVertex3f(this->position.x + randFloat(-3, -0.5), this->position.y + randFloat(-3, -0.5), this->position.z + randFloat(-3, -0.5));
		glVertex3f(this->position.x + randFloat(-3, 3), this->position.y + randFloat(-3, 3), this->position.z + randFloat(-3, 3));
		glEnd();
		break;
	}
	
	glPopMatrix();
}