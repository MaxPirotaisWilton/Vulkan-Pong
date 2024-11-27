#pragma once
#include "Vertex.h"
#include <vector>

class Object
{
protected:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	Object();
	virtual void updateVertices() = 0;

public:
	virtual void initialize() = 0;
	virtual void render() = 0;
	virtual void behave(float deltaTime) = 0;

	std::vector<Vertex> getVertices() const { return vertices; }
	std::vector<uint32_t> getIndices() const { return indices; }

	std::vector<uint32_t> getShiftedIndices(uint32_t shiftBy);

};