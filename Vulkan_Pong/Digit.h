#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class Digit : public Object
{
private:
	short value;

	glm::vec3 pos;
	glm::vec2 scale;
	std::vector<glm::vec3> vertexColors;

	void updateVertices() override;

public:

	//Constructors
	Digit(short val);
	Digit(short val, glm::vec3 pos, glm::vec2 size);

	//Getters

	short GetValue() const { return value; }

	glm::vec3 getPos() const { return pos; }
	std::vector<glm::vec3> GetVertexColors() const { return vertexColors; }

	//Setters

	void setValue(short val) { value = val; }
	void setPos(glm::vec3 newPos) { pos = newPos; }
	void setVertexColors(std::vector<glm::vec3> newVertexColors)
	{
		vertexColors.clear();
		vertexColors = newVertexColors;
	}
	void setVertexColors(glm::vec3 newVertexColor) {
		vertexColors.clear();
		vertexColors.push_back(newVertexColor);
	}

	//Other Methods 

	void initialize() override;
	void render() override;
	void behave(float deltaTime) override;

	void updateDigit();
	void updateDigit(short value);
};

