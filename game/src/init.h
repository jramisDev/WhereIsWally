#pragma once

//FPS
#define FPS 60

//WindowScreen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define GAME_TITLE "Where is Wally?"

enum Screens { MENU, GAME, NEXTLEVEL, WIN, GAMEOVER };

Screens actualScreen = MENU;

//Save records files
const char urlRecordFile[31] = "resources/saveGame/records.txt";
bool bWriteFile = false;

//Background
Texture2D background;
Texture2D backgroundTwo;
Texture2D backgroundThree;

//Variables
bool globalRunning = true;

int level = 1;
int score = 0;
bool gameOver = false;

int levelTime = 20; // Duración del nivel en segundos

float elapsedTime = 0.0f; // Tiempo transcurrido en segundos
float timeAcumulated = 0.0f;
float totalGame = 0.0f;

//Functions
Color GetRandomColor();

int GetRandomShape();

void GenerateRandomShapes(Vector2& circlePos, int& circleRadius, Color& circleColor,
    Vector2& rectPos, int& rectWidth, int& rectHeight, Color& rectColor,
    Vector2& triPos, Vector2& triP1, Vector2& triP2, Vector2& triP3, Color& triColor);

void initApp();

void mainScreen();

void gameScreen();

void nextScreen();

void winScreen();

void endScreen();