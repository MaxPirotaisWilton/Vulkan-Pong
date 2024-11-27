#pragma once
#include "Object.h"
#include <string>

class VikingRoom : public Object
{
private:
	std::string MODEL_PATH = "models/viking_room.obj";
	std::string TEXTURE_PATH = "textures/viking_room.png";
	void loadModel();
	void updateVertices() override;

public:
	VikingRoom();
	void initialize() override;
	void render() override;
	void behave(float deltaTime) override;

};

