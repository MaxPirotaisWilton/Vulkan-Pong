#pragma once
#include "Object.h"

class TranslateSawWave :
    public Object
{
private:
    glm::vec3 pos;
    glm::vec2 dimensions;

	float centreRot = 0.5f;

    std::vector<glm::vec3> vertexColors;

    void updateVertices() override;

public:
	TranslateSawWave(glm::vec3 pos, glm::vec2 scale);

    //Getters

    glm::vec3 getPos() const { return pos; }

    glm::vec2 getDimensions() const { return dimensions; }

    float getWidth()	const { return dimensions.x; }
    float getHeight()	const { return dimensions.y; }

    std::vector<glm::vec3> GetVertexColors() const { return vertexColors; }

	float getCentreRot() const { return centreRot;  }

    //Setters

	void setPos(glm::vec3 newPos) { pos = newPos; }

	void setDimensions(glm::vec2 newDimensions) { dimensions = newDimensions; }

	void setWidth(float newWidth) { dimensions.x = newWidth; }
	void setHeight(float newHeight) { dimensions.y = newHeight; }

	void setCentreRot(float rot) { centreRot = rot; }

	void setVertexColors(std::vector<glm::vec3> newVertexColors)
	{
		vertexColors.clear();
		vertexColors = newVertexColors;
	}

	void setVertexColors(glm::vec3 newVertexColor)
	{
		vertexColors.clear();
		vertexColors.push_back(newVertexColor);
	}

	void initialize() override;
	void render() override;
	void behave(float deltaTime) override;
};

