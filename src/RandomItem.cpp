#include "RandomItem.h"
#include "visuals.h"

RandomItem::RandomItem() : Model() {}

void RandomItem::randomize() {
	this->position = { this->position.x + randFloat(-4, 4), this->position.y + randFloat(-4, 4), this->position.z + randFloat(-4, 4) };
	this->speed = { randFloat(-0.1,0.1), randFloat(-0.1,0.1), randFloat(-0.1,0.1) };
	this->rspeed = { randFloat(-0.1,0.1), randFloat(-0.1,0.1), randFloat(-0.1,0.1) };
	this->color = { randFloat(0, 1), randFloat(0, 1), randFloat(0, 1) };
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
		glScalef(randFloat(1, 4), randFloat(1, 4), randFloat(1, 4));
		glutSolidCone(1, 1, 50, 50);
		break;
	case 1: // cube
		glScalef(randFloat(1, 4), randFloat(1, 4), randFloat(1, 4));
		glutSolidCube(1);
		break;
	case 2: // octahedron
		glScalef(randFloat(1, 4), randFloat(1, 4), randFloat(1, 4));
		glutSolidOctahedron();
		break;
	case 3: // dodecahedron
		glScalef(randFloat(1, 4), randFloat(1, 4), randFloat(1, 4));
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