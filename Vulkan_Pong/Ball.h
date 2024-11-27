#pragma once
#include "Quad.h"
#include "GameManager.h"

#include <vector>

class GameManager;

class Ball : public Quad
{
private:

	glm::vec2 velocity = glm::vec2(0.0f);

	void bounce(glm::vec2 bounceMult);
	void move(float deltaTime);

	std::vector<Quad*> paddles;

	GameManager* gm;

public:
	//	Constructors

	Ball(glm::vec3 pos, float size, std::vector<Quad*> paddles);
	Ball(glm::vec3 pos, float size, std::vector<Quad*> paddles, GameManager* gm);

	//	Getters

	glm::vec2 getVelocity() const { return velocity; }
	std::vector<Quad*> getPaddles() const { return paddles; }

	//	Setters

	void setVelocity(glm::vec2 v) { velocity = v; }
	void setPaddles(std::vector<Quad*> p) { paddles = p; }

	//	Other Functions
	void behave(float deltaTime) override;
	void onCollision(Quad other, glm::vec3 dif);

	static void onCollisionThunk(void* obj, Quad other, glm::vec3 dif) {
		static_cast<Ball *>(obj)->onCollision(other, dif);
	}
};

