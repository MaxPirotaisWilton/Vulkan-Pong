#include "Quad.h"
#include <iostream>

Quad::Quad(glm::vec3 pos, float width, float height, QuadGenerationMode genMode):
	Object(),
	pos(pos),
	genMode(genMode)
{
	dimensions = glm::vec2(width, height);

	vertexColors.assign(1, glm::vec3(1.0f,0.0f,0.0f));
	vertexColors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	vertexColors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	vertexColors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	updateVertices();
}

Quad::Quad(glm::vec3 pos, float width, float height, QuadGenerationMode genMode, glm::vec3 color):
	Object(),
	pos(pos),
	genMode(genMode)
{
	dimensions = glm::vec2(width, height);

	vertexColors.assign(4, color);

	updateVertices();
}

Quad::Quad(glm::vec3 pos, float width, float height, QuadGenerationMode genMode, std::vector<glm::vec3> vertexColors):
	Object(),
	pos(pos),
	genMode(genMode),
	vertexColors(vertexColors)
{
	dimensions = glm::vec2(width, height);

	updateVertices();
}

void Quad::initialize()
{
	updateVertices();
}

void Quad::render()
{
	updateVertices();
}

void Quad::behave(float deltaTime)
{

}


void Quad::updateVertices()
{
	float left = 0.0f;
	float right = 0.0f;
	float up = 0.0f;
	float down = 0.0f;

	switch (genMode) {

	case(CENTER):
		left = pos.x - getWidth() / 2.0f;
		right = pos.x + getWidth() / 2.0f;
		up = pos.y - getHeight() / 2.0f;
		down = pos.y + getHeight() / 2.0f;
		break;

	default:
		left = pos.x;
		right = pos.x + getWidth();
		up = pos.y;
		down = pos.y + getHeight();

	}

	//std::cout << "resizing quad dimensions X: " << right - left << " | Y: " << down - up << "\n";

	vertices = {
			{{left, up, pos.z}, vertexColors.at(0), {0.0f, 0.0f}},
			{{right, up, pos.z}, vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
			{{right, down, pos.z}, vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
			{{left, down, pos.z}, vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}}
	};
	indices = {0,1,2,0,2,3};
}

void Quad::resolveCollision(Quad other, void (*onCollisionPtr)(void* obj, Quad other, glm::vec3 dif))
{

	//	Get Center Pos of This Quad
	glm::vec3 thisPos;
	if (getQuadGenMode() == LOWERLEFTCORNER) {
		thisPos = getPos() + (glm::vec3(getWidth(), getHeight(), 0.0f))/2.0f;
	} else {
		thisPos = getPos();
	}

	//	Get Center Pos of Other Quad
	glm::vec3 otherPos;
	if (getQuadGenMode() == LOWERLEFTCORNER) {
		otherPos = other.getPos() + (glm::vec3(other.getWidth(), other.getHeight(), 0.0f)) / 2.0f;
	} else {
		otherPos = other.getPos();
	}

	glm::vec3 dif = thisPos - otherPos;
	//glm::vec3 processedDif = dif;

	/*if (dif.x < 0) { 
		processedDif = glm::vec3(dif.x * -1, dif.y, dif.z); 
	}

	if (dif.y < 0) { 
		processedDif = glm::vec3(dif.x, dif.y * -1, dif.z);
	}*/

	if (dif.x < (getWidth() + other.getWidth())/2.0f && 
		dif.x > -(getWidth() + other.getWidth()) / 2.0f &&
		dif.y < (getHeight() + other.getHeight()) / 2.0f &&
		dif.y > -(getHeight() + other.getHeight()) / 2.0f)
	{
 		onCollisionPtr(this, other, dif);
	}
}

