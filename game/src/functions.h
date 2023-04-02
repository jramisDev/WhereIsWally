#pragma once

#include "raylib.h"

// Devuelve un color aleatorio
Color GetRandomColor() {

    int r = GetRandomValue(0, 255);
    int g = GetRandomValue(0, 255);
    int b = GetRandomValue(0, 255);

    return Color{ static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255 };

}

// Devuelve un número aleatorio entre 1 y 5
int GetRandomShape() {
    return GetRandomValue(1, 5);
}

void GenerateRandomShapes(Vector2& circlePos, int& circleRadius, Color& circleColor,
    Vector2& rectPos, int& rectWidth, int& rectHeight, Color& rectColor,
    Vector2& triPos, Vector2& triP1, Vector2& triP2, Vector2& triP3, Color& triColor) {

    circlePos = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(50, SCREEN_HEIGHT - 50) };

    rectPos = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(50, SCREEN_HEIGHT - 50) };

    triPos = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(50, SCREEN_HEIGHT - 50) };
    triP1 = { triPos.x - 25, triPos.y + 25 };
    triP2 = { triPos.x + 25, triPos.y + 25 };
    triP3 = { triPos.x, triPos.y - 25 };
}