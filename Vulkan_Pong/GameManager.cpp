#include "GameManager.h"
#include "Paddle.h"
#include "Quad.h"
#include "TranslateSawWave.h"

#include "UtilRand.h"

#include <iostream>
#include <random>
#include <algorithm>

//Middle line 
int lineNum = 29;

std::vector<Quad*> middleLine;

Paddle* paddleLeft;
Paddle* paddleRight;

TranslateSawWave* crown;
TranslateSawWave* crownBack;

std::vector<Quad*> paddles;

bool forceObjAssign = false;

bool _ballBlink = false;
bool _scoreBlink = false;
int	_ballBlinkCount = 0;
int	_scoreBlinkCount = 0;

float crownRot = 0.5f;
float deltaTimeCrown = 0.0f;

int winningScore = 11;

GameManager::GameManager(std::vector<Object*>* ptr)
{
	prevGameState = gameState;

	inputManager = new InputManager();
	inputManager->setInputManagerPtr(inputManager);

	objArrPtr = ptr;

	//Left Paddle
	paddleLeft = new Paddle(glm::vec3(-1.25f, 0.0f, 0.0f), 0.03f, 0.17f, 2.0f, 10.f, inputManager, GLFW_KEY_TAB, GLFW_KEY_LEFT_SHIFT);
	paddleLeft->setServeBallPos(glm::vec3(0.08f, 0.0f, 1.0f));

	//Right Paddle
	paddleRight = new Paddle(glm::vec3(1.25f, 0.0f, 0.0f), 0.03f, 0.17f, 2.0f, 10.f, inputManager, GLFW_KEY_BACKSLASH, GLFW_KEY_RIGHT_SHIFT);
	paddleRight->setServeBallPos(glm::vec3(-0.08f, 0.0f, 1.0f));

	//Ball
	paddles.push_back(paddleLeft);
	paddles.push_back(paddleRight);

	ball = new Ball(glm::vec3(0.1f, 0.0f, 0.0f), 0.03f, paddles, this);

	//Score counting digits for each player
	leftCounter0 = new Digit(0, glm::vec3(-0.75f, 0.6f, 0.0f), glm::vec2(0.15f, 0.3f));
	leftCounter1 = new Digit(1, glm::vec3(-0.95f, 0.6f, -1.0f), glm::vec2(0.15f, 0.3f));
	rightCounter0 = new Digit(0, glm::vec3(0.6f, 0.6f, 0.0f), glm::vec2(0.15f, 0.3f));
	rightCounter1 = new Digit(1, glm::vec3(0.40f, 0.6f, -1.0f), glm::vec2(0.15f, 0.3f));

	//Title Text
	float letterWidth = 0.575f;
	float letterHeigth = 0.45f;

	glm::vec2 letterDimensions = glm::vec2(letterWidth, letterHeigth);

	float letterHeigthHalf = letterHeigth / 2.0f;

	float spacingVarHalf = (2.4f - (letterWidth * 4)) / 6.0f;

	letter1 = new Letter(P, glm::vec3(-1.2f, -letterHeigthHalf, 0.f), letterDimensions);
	letter2 = new Letter(O, glm::vec3(-letterWidth - spacingVarHalf, -letterHeigthHalf, 0.f), letterDimensions);
	letter3 = new Letter(N, glm::vec3(spacingVarHalf, -letterHeigthHalf, 0.f), letterDimensions);
	letter4 = new Letter(G, glm::vec3(1.2f - letterWidth, -letterHeigthHalf, 0.f), letterDimensions);

	//Crown
	crown = new TranslateSawWave(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.15f));
	crown->setVertexColors(glm::vec3(1.0f, 0.7f, 0.0f));
	crownBack = new TranslateSawWave(glm::vec3(0.0f, 0.0f, 0.8f), glm::vec2(0.15f, 0.12f));
	crownBack->setVertexColors((glm::vec3(1.0f, 0.7f, 0.0f)/2.5f));
}

void GameManager::Score(char side)
{
	//Stop ball
	ball->setVelocity(glm::vec2(0.0f));
	
	//Start Blinking ball Timers
	_ballBlinkTimer.Start();

	//Start Blinking score Timer
	_scoreBlinkTimer.Start();

	//Start Timer before score is updated

	//Start Timer before next Serve
	_scoreSequenceTimer.Start();

	if (side == '<') {
		// Left Player Scores
		leftScore++;

		serveIndicator = 1;
	}
	else if (side == '>') {
		// Right Player Scores
		rightScore++;

		serveIndicator = -1;
	}
	else {
		// ERROR
		// TODO(?): throw/log error with score indicator being incorrect
	}
	
}

void GameManager::Start()
{
	// Populate All relevant Objects (Paddles, Ball, Letters, Digits, )

	//Middle lines
	for (int i = 0; i < lineNum + 1; i++) {

		float height = (2.0f * (i / (float)lineNum)) - 1.0f;

		middleLine.push_back(new Quad(glm::vec3(0.0f, height, 0.0f), 0.015f, 0.04f, CENTER, glm::vec3(1.0f)));

	}

	//ball->setVelocity(glm::vec2(1.0f, 0.01f));

	permanentObjects.push_back(paddleLeft);
	permanentObjects.push_back(paddleRight);

	permanentObjects.insert(permanentObjects.begin(), middleLine.begin(), middleLine.end());

	//Objects.insert(Objects.end(), permanentObjects.begin(), permanentObjects.end());

	loadMenu(true);

	passObjsToMain();
}

void GameManager::Update(float deltaTime)
{
	switch (gameState) {
	case MENU:
		{
			if (hasStateChanged(MENU)) {
				loadMenu(true);
				ball->setVertexColors(glm::vec3(1.0f));

				leftCounter0->setValue(0);
				rightCounter0->setValue(0);
			}

			moduloTime += deltaTime;

			if (moduloTime > 2) {
				moduloTime = 0;
			}

			float interval = -0.1f;

			float letterClr1 = glm::sin(2 * glm::pi<float>() * (moduloTime));
			float letterClr2 = glm::sin(2 * glm::pi<float>() * (moduloTime + interval));
			float letterClr3 = glm::sin(2 * glm::pi<float>() * (moduloTime + interval * 2));
			float letterClr4 = glm::sin(2 * glm::pi<float>() * (moduloTime + interval * 3));

			letter1->setVertexColors(glm::vec3((letterClr1 + 2.0f) / 3.0f));
			letter2->setVertexColors(glm::vec3((letterClr2 + 2.0f) / 3.0f));
			letter3->setVertexColors(glm::vec3((letterClr3 + 2.0f) / 3.0f));
			letter4->setVertexColors(glm::vec3((letterClr4 + 2.0f) / 3.0f));

			if (inputManager->getInput(StartKey)) {
				gameState = START;
			}
		}
		break;
	case START:
		{
			// Prepare scores and display timers
			if (hasStateChanged(START)) {
				loadGame(false, false, false);

				leftScore = 0;
				rightScore = 0;

				_scoreAppearTimer.Start();
				_ballAppearTimer.Start();
			}

			// Display the score digits
			if (_scoreAppearTimer.IsFinished()) {
				loadGame(true, false, false);
				_scoreAppearTimer.StopAndReset();
			}

			// Display ball and setup random first serve selection
			if (_ballAppearTimer.IsFinished()) {
				loadGame(true, true, false);
				_ballAppearTimer.StopAndReset();

				_firstServeTimer.Configure(UtilRand::randomDouble(10.0, 15.0));
				std::cout << "" << _firstServeTimer.GetSeconds() << "\n";
				_firstServeTimer.Start();

				serveIndicator = 1;
			}

			// Visually Ping Pong ball between either player paddle 
			if (_firstServeTimer.IsRunning()) {
				if (_firstServeTimer.GetElapsedTime() - _firstStoredTime0 > _firstServeInterval0) {

					serveIndicator = -serveIndicator;
					_firstStoredTime0 += _firstServeInterval0;

					//std::cout << "" << "_firstStoredTime" << "\n";
				}

				//slow down ping ponging every 
				if (_firstServeTimer.GetElapsedTime() - _firstStoredTime1 > _firstServeInterval1) {
					_firstServeInterval0 *= 3.0;
					_firstServeInterval0 = std::clamp(_firstServeInterval0, 0.0f, _firstServeIntervalMax);
					_firstStoredTime1 += _firstServeInterval1;
				}
			}

			// Setup for visual indicator decision is made
			if (_firstServeTimer.IsFinished()) {
				_firstStoredTime0 = 0.0;
				_firstStoredTime1 = 0.0;
				_firstServeTimer.StopAndReset();

				_firstServeBlinkTimer0.Start();
				_ballBlinkTimer.Start();
			}

			// Blink the ball
			if (_ballBlinkTimer.IsFinished()) {
				if (_ballBlink) {
					ball->setVertexColors(glm::vec3(0.0f));
					_ballBlink = false;
				}
				else {
					ball->setVertexColors(glm::vec3(1.0f));
					_ballBlink = true;
				}
				_ballBlinkTimer.StopAndReset();
				_ballBlinkTimer.Start();
			}

			// Finish this all, Transition to Serve to then start game
			if (_firstServeBlinkTimer0.IsFinished()) {


				_firstServeInterval0 = 0.05f;
				_firstStoredTime0 = 0.0f;
				_firstStoredTime1 = 0.0f;

				ball->setVertexColors(glm::vec3(1.0f));

				gameState = SERVE;

				_ballBlinkTimer.StopAndReset();
				_firstServeBlinkTimer0.StopAndReset();
			}

			// Set ball pos to paddle that should serve
			if (serveIndicator < 0) {
				ball->setPos(paddleLeft->getServeBallPos());
			}
			else {
				ball->setPos(paddleRight->getServeBallPos());
			}
		}
		break;

	case SERVE:
		{
			int serveKey;

			// Set ball pos to paddle that should serve
			if (serveIndicator < 0) {
				ball->setPos(paddleLeft->getServeBallPos());
				serveKey = LeftServeKey;
			}
			else if  (serveIndicator > 0) {
				ball->setPos(paddleRight->getServeBallPos());
				serveKey = RightServeKey;
			}

			// Set Ball Velocity and transition gameState to GAME
			if (inputManager->getInput(serveKey)) {
				ball->setVelocity(-glm::normalize(ball->getPos()) * 1.2f);
				gameState = GAME;
			}

			if (hasStateChanged(SERVE)) {
				ball->setVertexColors(glm::vec3(1.0f));
			}
		}
		break;

	case GAME:
		{
			// Blink the ball
			if (_ballBlinkTimer.IsFinished()) {
				if (_ballBlink) {
					ball->setVertexColors(glm::vec3(0.0f));
					_ballBlink = false;
				}
				else {
					ball->setVertexColors(glm::vec3(1.0f));
					_ballBlink = true;
					_ballBlinkCount++;
				}
				_ballBlinkTimer.StopAndReset();
				_ballBlinkTimer.Start();
			}
			//Stop timer when blink count reached (ball)
			if (_ballBlinkCount >= 5 && !_ballBlink) {
				ball->setVertexColors(glm::vec3(0.0f));
				_ballBlinkTimer.StopAndReset();
				_ballBlinkCount = 0;
			}

			// Blink the score
			if (_scoreBlinkTimer.IsFinished()) {
				if (_scoreBlink) {
					if (serveIndicator > 0) {
						leftCounter0->setVertexColors(glm::vec3(0.0f));
						leftCounter1->setVertexColors(glm::vec3(0.0f));
					}
					else if (serveIndicator < 0) {
						rightCounter0->setVertexColors(glm::vec3(0.0f));
						rightCounter1->setVertexColors(glm::vec3(0.0f));
					}
					_scoreBlink = false;
				}
				else {
					if (serveIndicator > 0) {
						leftCounter0->setVertexColors(glm::vec3(1.0f));
						leftCounter1->setVertexColors(glm::vec3(1.0f));
					}
					else if (serveIndicator < 0) {
						rightCounter0->setVertexColors(glm::vec3(1.0f));
						rightCounter1->setVertexColors(glm::vec3(1.0f));
					}
					_scoreBlink = true;
					_scoreBlinkCount++;
				}
				_scoreBlinkTimer.StopAndReset();
				_scoreBlinkTimer.Start();
			}
			//Stop timer when blink count reached (ball)
			if (_scoreBlinkCount >= 8 && _scoreBlink) {
				leftCounter0->setValue(leftScore);
				rightCounter0->setValue(rightScore);

				leftCounter1->setValue(leftScore / 10);
				rightCounter1->setValue(rightScore / 10);
				_scoreBlinkTimer.StopAndReset();
				_scoreBlinkCount = 0;
			}

			//Return to SERVE or END State
			if (_scoreSequenceTimer.IsFinished())
			{
				prevGameState = gameState;
				//Redirect to END state if a player scored 11
				if (leftScore > winningScore -1 || rightScore > winningScore - 1) {
					gameState = END;
				}
				else {
					gameState = SERVE;
				}
				_scoreSequenceTimer.StopAndReset();
			}
		}
		break;

	case END:
		{
			if(hasStateChanged(END)) {
				_endScreenTimer.Start();

				loadGame(true, false, true);

				deltaTimeCrown = 0.0f;
			}

			deltaTimeCrown += deltaTime;
			if (deltaTimeCrown > 1.0f) {
				deltaTimeCrown -= 1.0f;
			}

			crownRot = 0.5f + ((std::cos(std::_Pi_val * (1 + deltaTimeCrown)) + 1) / 2.0f) * 2;

			int crownRotInt = crownRot;

			crownRot -= (float)crownRotInt;

			crown->setCentreRot(crownRot);

			crownBack->setCentreRot(1 - crownRot);

			if (leftScore == winningScore) {
				crown->setPos(paddleLeft->getPos() + glm::vec3(0.0f, paddleLeft->getHeight(), 0.0f) * 1.2f);
				crownBack->setPos(paddleLeft->getPos() + glm::vec3(0.0f, paddleLeft->getHeight(), 0.0f) * 1.2f);
			}
			else if (rightScore == winningScore) {
				crown->setPos(paddleRight->getPos() + glm::vec3(0.0f, paddleRight->getHeight(), 0.0f)* 1.2f);
				crownBack->setPos(paddleRight->getPos() + glm::vec3(0.0f, paddleRight->getHeight(), 0.0f) * 1.2f);
			}

			if (_endScreenTimer.IsFinished()) {
				leftScore = 0;
				rightScore = 0;

				serveIndicator = 0;

				gameState = MENU;
			}
		}
		break;
	}

	//Only apply a visible colour to second score digit if a given score is above 9
	if (leftCounter0->GetValue() < 10) {
		leftCounter1->setVertexColors(glm::vec3(0.0f));
	}

	if (rightCounter0->GetValue() < 10) {
		rightCounter1->setVertexColors(glm::vec3(0.0f));
	}

	// Update objects to pass for Vulkan to use for rendering
	if (Objects.size() != prevObjNum || forceObjAssign) {
		passObjsToMain();
		forceObjAssign = false;
	}

}

bool GameManager::hasStateChanged(GameState state) {
	if (prevGameState != gameState && gameState == state) {
		prevGameState = gameState;
		return true;
	}
	return false;
}

void GameManager::loadMenu(bool renderTitle) {
	
	dynamicObjects.clear();
	if (renderTitle) {
		dynamicObjects.push_back(letter1);
		dynamicObjects.push_back(letter2);
		dynamicObjects.push_back(letter3);
		dynamicObjects.push_back(letter4);
	}


	Objects.clear();
	Objects.insert(Objects.end(), permanentObjects.begin(), permanentObjects.end());
	Objects.insert(Objects.end(), dynamicObjects.begin(), dynamicObjects.end());

	forceObjAssign = true;
}

void GameManager::loadGame(bool showScores, bool showBall, bool renderCrown) {

	ball->setPos(glm::vec3(0.1f, 0.1f, 0.0f));

	dynamicObjects.clear();

	if (showScores) {
		dynamicObjects.push_back(leftCounter0);
		dynamicObjects.push_back(rightCounter0);
		dynamicObjects.push_back(leftCounter1);
		dynamicObjects.push_back(rightCounter1);
	}

	if (showBall) {
		dynamicObjects.push_back(ball);
	}

	if (renderCrown) {
		dynamicObjects.push_back(crown);
		dynamicObjects.push_back(crownBack);
	}

	Objects.clear();
	Objects.insert(Objects.end(), permanentObjects.begin(), permanentObjects.end());
	Objects.insert(Objects.end(), dynamicObjects.begin(), dynamicObjects.end());
}

void GameManager::passObjsToMain() {
	prevObjNum = Objects.size();
	objArrPtr->clear();

	objArrPtr->insert(objArrPtr->end(), Objects.begin(), Objects.end());


	bool arbitrary = true;
}

