#include "Digit.h"
#include "Vertex.h"



Digit::Digit(short val) :
	Object(),
	value(val),
	pos(glm::vec3(0.0f)),
	scale(glm::vec2(1.0f))
{
	vertexColors.assign(24, glm::vec3(1.0f));
}

Digit::Digit(short val, glm::vec3 pos, glm::vec2 scale) :
	Object(),
	value(val),
	pos(pos),
	scale(scale)
{
	vertexColors.assign(24, glm::vec3(1.0f));
}

void Digit::initialize()
{
	updateVertices();
}

void Digit::render()
{
	updateVertices();
}

void Digit::behave(float deltaTime)
{
}

void Digit::updateDigit()
{
	updateVertices();
}

void Digit::updateDigit(short value)
{
	setValue(value);
	updateVertices();
}

void Digit::updateVertices()
{

	float horiPos[4] = { 0.0f, 0.25f, 0.75f, 1.0f };
	float vertPos[6] = { 0.0f, 0.125f, 0.5f, 0.625, 0.875f, 1.0f };

	vertices = {
		{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(0), {0.0f, 0.0f}},
		{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[0] + pos.y, pos.z},	vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(4 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(5 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(6 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[1] + pos.y, pos.z},	vertexColors.at(7 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(8 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(9 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(10 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[2] + pos.y, pos.z},	vertexColors.at(11 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(12 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(13 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(14 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[3] + pos.y, pos.z},	vertexColors.at(15 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(16 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(17 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(18 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[4] + pos.y, pos.z},	vertexColors.at(19 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[0] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(20 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[1] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(21 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[2] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(22 % vertexColors.size()), {0.0f, 0.0f}},
		{{scale.x * horiPos[3] + pos.x, scale.y * vertPos[5] + pos.y, pos.z},	vertexColors.at(23 % vertexColors.size()), {0.0f, 0.0f}}
	};

	std::vector<std::vector<uint32_t>> segments = {
		{
			1,2,6, 5,1,6
		},
		{
			4,5,9, 8,4,9
		},
		{
			10,6,11, 6,7,11
		},
		{
			13,9,14, 9,10,14
		},
		{
			16,12,17, 12,13,17
		},
		{
			18,14,19, 14,15,19
		},
		{
			21,17,22, 17,18,22
		}
	};

	std::vector<std::vector<uint32_t>> interSegments = {
		{
			0,1,5, 4,0,5
		},
		{
			6,2,7, 7,2,3
		},
		{
			12,8,13, 8,9,13
		},
		{
			10,15,14, 10,11,15
		},
		{
			16,17,21, 20,16,21
		},
		{
			22,18,23, 18,19,23
		}
	};

	indices.clear();

	switch (value%10) {
	case 1:
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());

		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());

		break;
	case 2:
		indices.insert(indices.end(), segments.at(0).begin(), segments.at(0).end());
		indices.insert(indices.end(), segments.at(1).begin(), segments.at(1).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(0).begin(), interSegments.at(0).end());
		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());

		break;
	case 3:
		indices.insert(indices.end(), segments.at(0).begin(), segments.at(0).end());
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(0).begin(), interSegments.at(0).end());
		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;
	case 4:
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(4).begin(), segments.at(4).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());

		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;
	case 5:
		indices.insert(indices.end(), segments.at(0).begin(), segments.at(0).end());
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(4).begin(), segments.at(4).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(0).begin(), interSegments.at(0).end());
		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;

	case 6:
		indices.insert(indices.end(), segments.at(0).begin(), segments.at(0).end());
		indices.insert(indices.end(), segments.at(1).begin(), segments.at(1).end());
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(4).begin(), segments.at(4).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(0).begin(), interSegments.at(0).end());
		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;

	case 7:
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;

	case 8:
		indices.insert(indices.end(), segments.at(0).begin(), segments.at(0).end());
		indices.insert(indices.end(), segments.at(1).begin(), segments.at(1).end());
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(4).begin(), segments.at(4).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(0).begin(), interSegments.at(0).end());
		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;
	
	case 9:
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(3).begin(), segments.at(3).end());
		indices.insert(indices.end(), segments.at(4).begin(), segments.at(4).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
		break;

	default:
		indices.insert(indices.end(), segments.at(0).begin(), segments.at(0).end());
		indices.insert(indices.end(), segments.at(1).begin(), segments.at(1).end());
		indices.insert(indices.end(), segments.at(2).begin(), segments.at(2).end());
		indices.insert(indices.end(), segments.at(4).begin(), segments.at(4).end());
		indices.insert(indices.end(), segments.at(5).begin(), segments.at(5).end());
		indices.insert(indices.end(), segments.at(6).begin(), segments.at(6).end());

		indices.insert(indices.end(), interSegments.at(0).begin(), interSegments.at(0).end());
		indices.insert(indices.end(), interSegments.at(1).begin(), interSegments.at(1).end());
		indices.insert(indices.end(), interSegments.at(2).begin(), interSegments.at(2).end());
		indices.insert(indices.end(), interSegments.at(3).begin(), interSegments.at(3).end());
		indices.insert(indices.end(), interSegments.at(4).begin(), interSegments.at(4).end());
		indices.insert(indices.end(), interSegments.at(5).begin(), interSegments.at(5).end());
	}

	indices.resize(78, indices.back());
}
