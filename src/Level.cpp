#include "Level.h"
#include "Defines.h"
#include "visuals.h"

#include <iostream>
using namespace std;

Level::Level() : Text(NumberToString(1).insert(0, "Level: ").c_str(), 0.01, { -SPACESHIP_X - 5, SPACESHIP_Y + 10, -20 }) {
	this->level = 1;
}

Level::~Level() {}

void Level::draw() {
	strcpy(this->text, NumberToString(this->level).insert(0, "Level: ").c_str());
	Text::draw();
}