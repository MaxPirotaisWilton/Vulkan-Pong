#include "TranslateSawWave.h"

TranslateSawWave::TranslateSawWave(glm::vec3 position, glm::vec2 scale):
	pos(position),
	dimensions(scale),
	vertexColors(
		{
			glm::vec3(1.0f)
		}
	)
{
}

void TranslateSawWave::initialize()
{
	updateVertices();
}

void TranslateSawWave::render()
{
	updateVertices();
}

void TranslateSawWave::behave(float deltaTime)
{

	

}

void TranslateSawWave::updateVertices()
{

	float left = pos.x - getWidth() / 2.0f;
	float right = pos.x + getWidth() / 2.0f;

	float tip0 = pos.x + (getWidth() * centreRot / 2) + (getWidth() / 4);
	float tip1 = pos.x + (getWidth() * centreRot / 2) - (getWidth() / 4);
	float tip2 = pos.x + (getWidth() * centreRot / 2) - (3 * getWidth() / 4);

	float trough0 = pos.x + (getWidth() * centreRot / 2);
	float trough1 = pos.x + (getWidth() * centreRot / 2) - (getWidth() / 2);

	float up = pos.y + getHeight() / 2.0f;
	float down = pos.y - getHeight() / 2.0f;
	
	float yCentre = pos.y;

	float endHeightMagn = centreRot * 2.0f - 1.0f;

	if (endHeightMagn > 0) {
		endHeightMagn = -endHeightMagn;
	}

	vertices = {

		// Crown Base

		{{left, yCentre, pos.z}, vertexColors.at(0), {0.0f, 0.0f}},
		{{right, yCentre, pos.z}, vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
		{{right, down, pos.z}, vertexColors.at(2 % vertexColors.size()), {0.0f, 0.0f}},
		{{left, down, pos.z}, vertexColors.at(3 % vertexColors.size()), {0.0f, 0.0f}},

		//Crown Pointy Bits (?)
		{ { tip0, up, pos.z }, vertexColors.at(0), {0.0f, 0.0f} },
		{ { tip1, up, pos.z }, vertexColors.at(0), {0.0f, 0.0f} },
		{ { tip2, up, pos.z }, vertexColors.at(0), {0.0f, 0.0f} },

		{ { trough0, yCentre, pos.z }, vertexColors.at(0), {0.0f, 0.0f} },
		{ { trough1, yCentre, pos.z }, vertexColors.at(0), {0.0f, 0.0f} },


		{{right, up + (getHeight()/2) * endHeightMagn , pos.z}, vertexColors.at(1 % vertexColors.size()), {0.0f, 0.0f}},
		{{left, up + (getHeight()/2) * endHeightMagn , pos.z}, vertexColors.at(0), {0.0f, 0.0f}}

	};
	indices = { 
		//Crown Base
		0,2,1, 0,3,2,
	
		//Crown Pointy Bits (?)

		//Middle Point
		5, 8, 7,

		//Right Point, panning out as rot >> 1
		4, 7 , 9, 1, 9, 7,

		//Left Point, panning in as rot >> 1
		6, 10 ,8, 10, 0, 8
	};


}