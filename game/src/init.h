#pragma once

//FPS
#define FPS 60

//WindowScreen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define GAME_TITLE "Where is Wally?"

#define SKY_WIDTH 14

enum Screens { MENU, GAME, NEXTLEVEL, WIN, GAMEOVER };

//Background
Texture2D background;

Color GetRandomColor();

int GetRandomShape();

void GenerateRandomShapes(Vector2& circlePos, int& circleRadius, Color& circleColor,
    Vector2& rectPos, int& rectWidth, int& rectHeight, Color& rectColor,
    Vector2& triPos, Vector2& triP1, Vector2& triP2, Vector2& triP3, Color& triColor);