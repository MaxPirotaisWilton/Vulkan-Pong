#include "Letter.h"
#include <array>

Letter::Letter(TitleLetterEnum titleLetter):
	Object(),
	titleLetterEnum(titleLetter),
	pos(glm::vec3(0.0f)),
	scale(glm::vec2(1.0f))
{
	setVertexColors(glm::vec3(1.0f));
}

Letter::Letter(TitleLetterEnum titleLetter, glm::vec3 pos): 
	Object(),
	titleLetterEnum(titleLetter),
	pos(pos),
	scale(glm::vec2(1.0f))
{
	setVertexColors(glm::vec3(1.0f));
}

Letter::Letter(TitleLetterEnum titleLetter, glm::vec3 pos, glm::vec2 scale) :
	Object(),
	titleLetterEnum(titleLetter),
	pos(pos),
	scale(scale)
{
	setVertexColors(glm::vec3(1.0f));
}

void Letter::updateVertices()
{

	switch (titleLetterEnum) {
	case P:
	{
		float horiPos[6] = { 0.0f, 0.15f, 0.15f, 0.85f, 0.9f, 1.0f };
		float vertPos[7] = { 0.0f, 0.4f, 0.5f, 0.6f, 0.8f, 0.9f, 1.0f };

		vertices = {
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[6] + pos.y, pos.z},	vertexColors.at(0), {0.0f, 0.0f}},
			{{scale.x * horiPos[4] + pos.x, scale.y * vertPos[6] + pos.y, pos.z},	vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[4] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(4 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(5 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(6 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(7 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(8 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(9 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(10 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(11 % vertexColors.size()), {0.0f, 0.0f}}
		};


		indices = {
			0, 8,1, 		1, 8, 9,	 	2, 1,9,  		2, 9, 10,
			3, 2,10, 		4, 3,10,		10,5, 4, 		11,  5, 10,
			11,6,5,			7, 6,11,		7, 11,0,  		0, 11, 8
		};
	}
	break;

	case O:
	{
		float horiPos[6] = { 0.0f, 0.1f, 0.2f, 0.8f, 0.9f, 1.0f };
		float vertPos[6] = { 0.0f, 0.1f, 0.2f, 0.8f, 0.9f, 1.0f };

		vertices = {
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(0), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[4] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(4 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[4] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(5 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(6 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(7 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(8 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(9 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(10 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(11 % vertexColors.size()), {0.0f, 0.0f}}
		};

		indices = {
			0, 8,1, 		1, 8, 2,	 	2, 8,9,  		2, 9, 3,
			3, 9,4, 		4, 9,10,		10,5, 4, 		6,  5, 10,
			11,6,10,		7, 6,11,		7, 11,0,  		0, 11, 8
		};
	}
	break;

	case N:
	{
		float horiPos[4] = { 0.0f, 0.2f, 0.8f, 1.0f };
		float vertPos[4] = { 0.0f, 0.3f, 0.7f, 1.0f };

		vertices = {
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(0), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(4 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(5 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(6 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(7 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(8 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(9 % vertexColors.size()), {0.0f, 0.0f}}
		};

		indices = {
			0, 7,1, 		1, 7, 2,	 	2, 7,6,  		2, 6, 5,
			2, 5,4, 		4, 3, 2,		0,9, 7, 		7,  9, 8
		};
	}
	break;

	case G:
	{
		float horiPos[6] = { 0.0f, 0.1f, 0.2f, 0.4f, 0.8f, 1.0f };
		float vertPos[8] = { 0.0f, 0.1f, 0.2f, .4f, 0.6f, 0.8f, 0.9f, 1.0f };

		vertices = {
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[6] + pos.y, pos.z},	vertexColors.at(0), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[7] + pos.y, pos.z},	vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[7] + pos.y, pos.z},	vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(4 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(5 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[4] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(6 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[4] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(7 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(8 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(9 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(10 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[5] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(11 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(12 % vertexColors.size()), {0.0f, 0.0f}},
			{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(13 % vertexColors.size()), {0.0f, 0.0f}}
		};

		indices = {
			1, 3,2, 		1, 4, 3,	 	0, 4,1,  		0, 5, 4,
			13, 5,0, 		13, 12,5,		11,6, 5, 		6,  11, 7,
			7,11,10,		5, 12,11,		7, 10,9,  		9, 8, 7
		};
	}
	break;
	}

}

void Letter::setVertexColors(glm::vec3 newVertexColor)
{
	int verticesNum = 0;
	vertexColors.clear();
	switch (titleLetterEnum) {
	case P:
		verticesNum = 12;
		break;

	case N:
		verticesNum = 10;
		break;

	case G:
		verticesNum = 14;
		break;

	default:
		verticesNum = 12;
	}
	vertexColors.assign(verticesNum, newVertexColor);

	int mockNum = 0;
}

void Letter::initialize()
{
	updateVertices();
}

void Letter::render()
{
	updateVertices();
}

void Letter::behave(float deltaTime)
{
}
