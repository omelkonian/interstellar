#include "Level.h"
#include "Defines.h"
#include "visuals.h"

#include <iostream>
using namespace std;

Level::Level() : Text(NumberToString(1).insert(0, "Level: ").c_str(), TEXT_SIZE, { -SPACESHIP_X, SPACESHIP_Y, TEXT_Z }) {
	this->level = 1;
}

Level::~Level() {}

void Level::draw() {
	strcpy(this->text, NumberToString(this->level).insert(0, "Level: ").c_str());
	Text::draw();
}