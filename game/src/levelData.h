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

	float getElapsedTime() { return elapsedTime; }
	void addElapsedTime(float pElapsedTime) { elapsedTime += pElapsedTime; }
	void resetElapsedTime() { elapsedTime = 0.0f; }

	float getTimeAcumulated() { return timeAcumulated; 	}
	float setTimeAcumulated(float pTime) { return timeAcumulated = pTime; }
	void resetTimeAcumulated() { timeAcumulated = 0.0f; }
	
	float getTotalGame() { return totalGame; }
	void addTotalGame(float pTime) { totalGame += pTime; }

	bool isGameOver() { return gameOver; }
	void setGameOver(bool pGameOver) { gameOver = pGameOver; }

};
