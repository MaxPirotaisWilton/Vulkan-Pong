#include "Quad.h"
#include "Ball.h"

#include <iostream>


Ball::Ball(glm::vec3 pos, float size, std::vector<Quad*> paddles): 
	Quad(pos, size, size, CENTER),
	velocity(glm::vec2(0.f)),
	paddles(paddles)
{
	std::vector<glm::vec3> ballVColors;
	ballVColors.assign(4, glm::vec3(1.0));
	setVertexColors(ballVColors);
}

Ball::Ball(glm::vec3 pos, float size, std::vector<Quad*> paddles, GameManager* gm):
	Quad(pos,size,size,CENTER),
	velocity(glm::vec2(0.f)),
	paddles(paddles),
	gm(gm)
{
	std::vector<glm::vec3> ballVColors;
	ballVColors.assign(4, glm::vec3(1.0));
	setVertexColors(ballVColors);
}

void Ball::behave(float deltaTime)
{
	move(deltaTime);

	auto pos = getPos();

	/*std::cout.precision(2);
	std::cout << "behave loop called: new pos = { X: " << pos.x  << ", Y: " << pos.y << ", for deltaTime: " << deltaTime << " } \n";*/

	//Bounce Vertically
	if (pos.y - getHeight() / 2.f < -1.01) {
		setPos(glm::vec3(getPos().x, -0.99f, getPos().z));
		bounce(glm::vec2(1.0f, -1.0f));
	}
	if (pos.y + getHeight()/2.f > 1.01) {
		setPos(glm::vec3(getPos().x,  0.99f, getPos().z));
		bounce(glm::vec2(1.0f, -1.0f));
	}

	//Bounce Horizontally (Ball should Score)
	if (pos.x - getWidth() / 2.f < -1.35) {
		setPos(glm::vec3(-1.33f, getPos().y, getPos().z));
		bounce(glm::vec2(-1.0f, 1.0f));
		if (gm != nullptr) {
			gm->Score('>');
		}
	}
	if (pos.x + getWidth() / 2.f >  1.35) {
		setPos(glm::vec3(1.33f, getPos().y, getPos().z));
		bounce(glm::vec2(-1.0f, 1.0f));
		if (gm != nullptr) {
			gm->Score('<');
		}
	}

	if (pos.x < 0) {
		resolveCollision(*(paddles.front()), &Ball::onCollisionThunk);
	}

	if (pos.x > 0) {
		resolveCollision(*(paddles.back()), &Ball::onCollisionThunk);
	}

}


void Ball::bounce(glm::vec2 bounceMult)
{
	setVelocity(glm::vec2(velocity.x * bounceMult.x, velocity.y * bounceMult.y));
}

void Ball::move(float deltaTime)
{
	glm::vec2 displacement = glm::vec2(velocity.x * deltaTime, velocity.y * deltaTime);

	//std::cout << "behave loop called: new displacement = { X: " << displacement.x * 100 << ", Y: " << displacement.y * 100 << ", for deltaTime: " << deltaTime << " } \n";

	setPos(getPos() + glm::vec3(displacement, 0.0f));
}



void Ball::onCollision(Quad other, glm::vec3 dif)
{
	float speed = glm::length(velocity);
	glm::vec2 normalisedDif = glm::normalize(glm::vec2(dif.x * 2.5f,dif.y));

	setVelocity(normalisedDif * speed * 1.01f);
}
