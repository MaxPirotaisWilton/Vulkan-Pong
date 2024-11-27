#pragma once
#include "Object.h"
#include <glm/glm.hpp>

enum QuadGenerationMode {
	LOWERLEFTCORNER,
	CENTER
};

class Quad : public Object
{
private: 
	glm::vec3 pos;
	glm::vec2 dimensions;

	std::vector<glm::vec3> vertexColors;

	QuadGenerationMode genMode;

	void updateVertices() override;

public:
	//Constructors

	Quad(glm::vec3 pos, float width, float height, QuadGenerationMode genMode);
	Quad(glm::vec3 pos, float width, float height, QuadGenerationMode genMode, glm::vec3 color);
	Quad(glm::vec3 pos, float width, float height, QuadGenerationMode genMode, std::vector<glm::vec3> vertexColors);

	// Getter

	glm::vec3 getPos() const { return pos; }

	glm::vec2 getDimensions() const { return dimensions; }

	float getWidth()	const { return dimensions.x; }
	float getHeight()	const { return dimensions.y; }

	std::vector<glm::vec3> GetVertexColors() const { return vertexColors; }

	QuadGenerationMode getQuadGenMode() const { return genMode; }

	// Setters

	void setPos(glm::vec3 newPos) { pos = newPos; }
	
	void setDimensions(glm::vec2 newDimensions) { dimensions = newDimensions; }

	void setWidth(float newWidth) { dimensions.x = newWidth; }
	void setHeight(float newHeight) { dimensions.y = newHeight; }

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

	void setQuadGenMode(QuadGenerationMode newGenMode) { genMode = newGenMode; }

	// Other Methods

	void initialize() override;
	void render() override;
	void behave(float deltaTime) override;

	void resolveCollision(Quad other, void (*onCollisionPtr)(void* obj, Quad other, glm::vec3 dif));
};

