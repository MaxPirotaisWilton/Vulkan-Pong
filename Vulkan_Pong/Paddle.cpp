#include "Paddle.h"
#include <iostream>


Paddle::Paddle(glm::vec3 pos, float width, float height, float speedMult, float accelMult, InputManager* _inputManagerPtr, int upK, int downK):
	Quad(pos, width, height, CENTER, glm::vec3(1.0f)),
	speedMult(speedMult),
	accelerationMult(accelMult),
	inputManagerPtr(_inputManagerPtr),
	upKey(upK),
	downKey(downK)
{
}

void Paddle::behave(float deltaTime)
{
	bool goUp = inputManagerPtr->getInput(upKey);
	bool goDown = inputManagerPtr->getInput(downKey);
	glm::vec2 currentVel = getVelocity();


	if (goUp && !goDown) {
		setVelocity(currentVel + glm::vec2(0.0f, deltaTime * accelerationMult));
	}
	else if (goDown && !goUp) {
		setVelocity(currentVel - glm::vec2(0.0f, deltaTime * accelerationMult));
	}
	else {
		setVelocity(currentVel + glm::vec2(0.0f, glm::clamp(-currentVel.y, -deltaTime * accelerationMult, deltaTime * accelerationMult)));
	}

	setVelocity(glm::clamp(getVelocity(), glm::vec2(0.0, -speedMult), glm::vec2(0.0, speedMult)));
	move(deltaTime);
	clampPos(0.985f - getHeight()/2);
}

void Paddle::move(float deltaTime)
{
	glm::vec2 displacement = glm::vec2(velocity.x * deltaTime, velocity.y * deltaTime);
	setPos(getPos() + glm::vec3(displacement, 0.0f));
}

void Paddle::clampPos(float maxVertPos)
{
	//std::cout << "clampPos is being called \n";

	glm::vec3 currentPos = getPos();
	float clampedHeight = glm::clamp(currentPos.y, -maxVertPos, maxVertPos);
	if (getPos().y < -maxVertPos || getPos().y > maxVertPos) {

		setPos(glm::vec3(currentPos.x, clampedHeight, currentPos.z));
		setVelocity(glm::vec2(0.0f));
	
	}
}
