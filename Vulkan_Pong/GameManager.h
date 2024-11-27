#pragma once
#include "Ball.h"
#include "Digit.h"
#include "Object.h"
#include "Letter.h"
#include "InputManager.h"
#include "Timer.h"

#include <random>

enum GameState {
	MENU,
	START,
	SERVE,
	GAME,
	END
};

class Ball;
class Digit;

class GameManager
{
private:

	GameState gameState = MENU;
	GameState prevGameState = MENU;

	int leftScore = 0;
	int rightScore = 0;

	InputManager* inputManager;

	Ball* ball;

	Digit* leftCounter0;
	Digit* leftCounter1;
	Digit* rightCounter0;
	Digit* rightCounter1;

	Letter* letter1;
	Letter* letter2;
	Letter* letter3;
	Letter* letter4;

	std::vector<Object*> permanentObjects;
	std::vector<Object*> dynamicObjects;

	std::vector<Object*>* objArrPtr;
	std::vector<Object*> Objects = {};

	int prevObjNum = 0;

	float moduloTime = 0.0f;

	int StartKey = GLFW_KEY_SPACE;
	int LeftServeKey = GLFW_KEY_CAPS_LOCK;
	int RightServeKey = GLFW_KEY_ENTER;

	int serveIndicator = 0;

	Timer _scoreAppearTimer = Timer(0.5f);

	Timer _ballAppearTimer = Timer(1.5f);

	Timer _firstServeTimer = Timer(1.0f);

	Timer _firstServeBlinkTimer0 = Timer(1.0);
	Timer _ballBlinkTimer = Timer(0.1f);
	Timer _scoreBlinkTimer = Timer(0.125f);

	Timer _scoreSequenceTimer = Timer(3.0f);

	Timer _endScreenTimer = Timer(8.0f);

	float _firstServeInterval0 = 0.05f;
	float _firstServeInterval1 = 2.0f;
	float _firstServeIntervalMax = 0.83f;
	float _firstStoredTime0 = 0.0f;
	float _firstStoredTime1 = 0.0f;

public: 

	GameManager(std::vector<Object*>* ptr) ;

	GameState getGameState()const { return gameState; }
	int GetScoreLeft()		const { return leftScore; }
	int GetScoreRight()		const { return rightScore; }
	InputManager* getInputManager() const { return inputManager; }

	std::vector<Object*> getObjects() const { return Objects; }
	
	void Score(char side);

	void Start();
	void Update(float deltaTime);
	bool hasStateChanged(GameState state);
	void loadMenu(bool renderTitle);
	void loadGame(bool showScores, bool showBall, bool renderCrown);
	void passObjsToMain();

};

