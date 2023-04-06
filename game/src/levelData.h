#pragma once

#include "raylib.h"

class LevelData {

	//Level Data
	int level;
	int score;
	int levelTime;

	float elapsedTime = 0.0f;
	float timeAcumulated = 0.0f;
	float totalGame = 0.0f;

	bool gameOver = false;

	//Rectangulo
	//Rectangle rectFigure;
	//Color backgroundColor;

	//Circulo

	//Triangulo

public:

	LevelData() {

		level = 1;
		levelTime = 10;
		score = 0;

		elapsedTime = 0.0f;
		timeAcumulated = 0.0f;
		totalGame = 0.0f;

		gameOver = false;

	}

	int getLevel() { return level; }
	void sumLevel() { level++; }

	int getLevelTime() { return levelTime; }
	void sumLevelTime(int addTime) { levelTime += addTime; }

	int getScore() { return score; }
	void sumScore() { score++; };
	void resetScore() { score = 0; }

	float getElapsedTime() { return elapsedTime; };
	void addElapsedTime(float pElapsedTime) { elapsedTime += pElapsedTime; }
	void resetElapsedTime() { elapsedTime = 0.0f; }

	bool isGameOver() { return gameOver; }
	void setGameOver(bool pGameOver) { gameOver = pGameOver; }


	//void Draw() {

	//	DrawRectangleRec(rectTime, backgroundColor);
	//	DrawRectangleRec(rectFigures, backgroundColor);

	//};

};
