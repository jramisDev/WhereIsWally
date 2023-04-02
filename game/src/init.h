#pragma once

//FPS
#define FPS 60

//WindowScreen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define GAME_TITLE "Where is Wally?"

enum Screens { MENU, GAME, NEXTLEVEL, WIN, GAMEOVER };

const char urlRecordFile[31] = "resources/saveGame/records.txt";

Screens actualScreen = MENU;


bool globalRunning = true;

int level = 1;
int score = 0;
bool gameOver = false;

int levelTime = 10; // Duraci�n del nivel en segundos

bool bWriteFile = false;

//Functions
Color GetRandomColor();

int GetRandomShape();

void GenerateRandomShapes(Vector2& circlePos, int& circleRadius, Color& circleColor,
    Vector2& rectPos, int& rectWidth, int& rectHeight, Color& rectColor,
    Vector2& triPos, Vector2& triP1, Vector2& triP2, Vector2& triP3, Color& triColor);