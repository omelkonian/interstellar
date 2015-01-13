#include "Score.h"
#include "Defines.h"
#include "visuals.h"
#include <iostream>
using namespace std;

Score::Score() : Text(NumberToString(0).insert(0, "Score: ").c_str(), TEXT_SIZE, { -SPACESHIP_X, SPACESHIP_Y-3, TEXT_Z }) {
	this->score = 0;
}

Score::~Score() {}

void Score::draw() {
	strcpy(this->text, NumberToString(this->score).insert(0, "Score: ").c_str());
	Text::draw();
}