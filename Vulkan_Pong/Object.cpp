#include "Object.h"

Object::Object()
{
}

std::vector<uint32_t> Object::getShiftedIndices(uint32_t shiftBy)
{
	std::vector<uint32_t> shiftedIndices;

	for (auto& element : indices) {
		shiftedIndices.push_back(element + shiftBy);
	}

	return shiftedIndices;
}
