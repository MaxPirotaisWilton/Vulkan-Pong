#pragma once
#include "Quad.h"
#include "InputManager.h"

class Paddle : public Quad
{
	private:
		int upKey, downKey;
		InputManager* inputManagerPtr;
		glm::vec2 velocity = glm::vec2(0.0f);

		glm::vec3 serveBallPos = glm::vec3(0.0f);

		float speedMult;
		float accelerationMult;

		void move(float deltaTime);
		void clampPos(float maxVertPos);

	public:

		// Constructors

		Paddle(glm::vec3 pos, float width, float height, float speedMult, float accelMult, InputManager* _inputManagerPtr, int upK, int downK);

		// Getters

		glm::vec2 getVelocity() const { return velocity; }
		glm::vec3 getServeBallPos() const { return (serveBallPos + getPos()); }

		// Setters

		void setVelocity(glm::vec2 v) { velocity = v; }
		void setServeBallPos(glm::vec3 p) { serveBallPos = p; }

		//Other Methods

		void behave(float deltaTime) override;
};

