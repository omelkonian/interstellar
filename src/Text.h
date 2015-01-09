#pragma once
#include "../gl/glm/glm.hpp"


class Text {
public:
	char *text;
	float size;
	glm::vec3 position;
	glm::vec3 color;

	Text(char *text, float size, glm::vec3 position);
	virtual ~Text();

	void draw();
};