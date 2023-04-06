/*
    TO-DO:
    Bug tiempo acumulado al pasar de pantalla
    Refactirar c�digo

*/

#pragma once
#pragma warning(disable : 4838)//Quito warnings de cast que me molestan
#pragma warning(disable : 4244)

#include "raylib.h"
#include "Init.h"
#include "Functions.h"
#include "LevelData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Generar tres figuras aleatorias
Vector2 circlePos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(100, SCREEN_HEIGHT - 200) };
Vector2 rectPos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(100, SCREEN_HEIGHT - 200) };
Vector2 triPos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(100, SCREEN_HEIGHT - 200) };

Color circleColor = GetRandomColor();
Color rectColor = GetRandomColor();
Color triColor = GetRandomColor();

int circleRadius = 25;
int rectWidth = 100;
int rectHeight = 50;

Vector2 triP1 = { triPos.x - 25, triPos.y + 25 };
Vector2 triP2 = { triPos.x + 25, triPos.y + 25 };
Vector2 triP3 = { triPos.x, triPos.y - 25 };
// Cada figura debe tener una posici�n aleatoria en la pantalla y una forma aleatoria

bool rectUI = false;
bool circUI = false;
bool triUI = false;


int main() {

    initApp();

    while (globalRunning) {

        if (WindowShouldClose()) globalRunning = false;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (actualScreen) {
            case MENU: {

                mainScreen();

            }break;
            case GAME: {

                gameScreen();

            }break;
            case NEXTLEVEL: {

                nextScreen();

            }break;
            case WIN: {

                winScreen();
               
            }break;
            case GAMEOVER: {

                endScreen();
                
            }break;
        }        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void initApp() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(FPS);

    //Background
    background = LoadTexture("resources/background/one.png");
    backgroundTwo = LoadTexture("resources/background/two.png");
    backgroundThree = LoadTexture("resources/background/three.png");

}

void mainScreen() {

    level = 1;
    score = 0;
    elapsedTime = 0.0f;
    gameOver = false;
    rectUI = false;
    circUI = false;
    triUI = false;

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RAYWHITE);
    DrawText(GAME_TITLE, 250, 100, 40, RED);
    DrawText("PRESS ENTER to GAME", 275, 140, 20, DARKBLUE);

    DrawText("CONTROLS:", 275, 180, 20, BLACK);
    DrawText("LEFT CLICK mouse button to CONFIRM object", 275, 200, 15, BLACK);

    DrawText("Records:", 275, 235, 15, DARKGREEN);

    std::string linea;
    std::ifstream MyFile(urlRecordFile);
    std::vector<int> numeros;
    int numero;
    while (MyFile >> numero) {
        numeros.push_back(numero);
    }
    MyFile.close();

    // Ordenar el vector en orden descendente
    std::sort(numeros.begin(), numeros.end(), std::greater<int>());

    int j = 0;
    for (int i = 0; i < 3 && i < numeros.size(); i++) {
        DrawText(std::to_string(numeros[i]).c_str(), 275, 250 + j, 15, DARKGREEN);
        j += 20;
    }

    if (IsKeyDown(KEY_ENTER)) actualScreen = GAME;

}

void gameScreen() {

    DrawTexture(background, 0, 0, WHITE);


    DrawRectangle(0, 0, 150, 40, { 0,0,0,122 });//Left backbroundUI
    DrawRectangle(SCREEN_WIDTH - 300, 0, 300, 100, { 0,0,0,122 });//Right backgroundUI

    // Dibujar las tres figuras en la UI
    if (!circUI) DrawCircle(550, 50, circleRadius, circleColor);
    if (!rectUI)  DrawRectangle(600, 25, rectWidth, rectHeight, rectColor);
    if (!triUI) DrawTriangle({ 750,25 }, { 725,75 }, { 775,75 }, triColor);

    // Dibujar las tres figuras generadas aleatoriamente
    DrawCircle(circlePos.x, circlePos.y, circleRadius, circleColor);
    DrawRectangle(rectPos.x - rectWidth / 2, rectPos.y - rectHeight / 2, rectWidth, rectHeight, rectColor);
    DrawTriangle(triP1, triP2, triP3, triColor);

    // Si el usuario hace clic en una figura, aumentar la puntuaci�n y eliminar la figura
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointCircle(mousePos, circlePos, circleRadius)) {

            score++;
            circlePos = { -100, -100 }; // Eliminar la figura
            circUI = true;

        }
        else if (CheckCollisionPointRec(mousePos, { rectPos.x - rectWidth / 2, rectPos.y - rectHeight / 2, (float)rectWidth, (float)rectHeight })) {

            score++;
            rectPos = { -100, -100 }; // Eliminar la figura
            rectUI = true;

        }
        else if (CheckCollisionPointTriangle(mousePos, triP1, triP2, triP3)) {

            score++;
            triPos = { -100, -100 }; // Eliminar la figura
            triP1 = { -500, -500 };
            triP2 = { -500, -500 };
            triP3 = { -500, -500 };
            triUI = true;

        }
    }

    // Si todas las figuras han sido eliminadas, pasar al siguiente nivel
    if (!gameOver && score == 3) {
        totalGame = totalGame + elapsedTime;
        timeAcumulated = levelTime - elapsedTime;
        level++;
        score = 0;
        elapsedTime = 0.0f; // Reiniciar el tiempo transcurrido
        rectUI = false;
        circUI = false;
        triUI = false;

        GenerateRandomShapes(circlePos, circleRadius, circleColor,
            rectPos, rectWidth, rectHeight, rectColor,
            triPos, triP1, triP2, triP3, triColor);


        if (level == 2) background = backgroundTwo;
        if (level == 3) background = backgroundThree;

        if (level < 4) actualScreen = NEXTLEVEL;
        if (level == 4) actualScreen = WIN;

    }

    // Mostrar el nivel y la puntuaci�n en la pantalla
    DrawText(TextFormat("Tiempo: %.0f", levelTime - elapsedTime), 10, 10, 20, WHITE);

    // Actualizar el tiempo transcurrido
    elapsedTime += GetFrameTime();
    if (elapsedTime >= levelTime) {
        gameOver = true; // El tiempo ha terminado
        actualScreen = GAMEOVER;
    }

}

void nextScreen() {

    DrawText("YOU WIN! Loading next level", 150, 150, 40, GREEN);
    DrawText("PRESS SPACE to MENU", 250, 195, 20, DARKGREEN);

    DrawText(TextFormat("timeAcumulated: %.0f", timeAcumulated), 10, 10, 20, BLACK);

    if (IsKeyDown(KEY_SPACE)) {
        actualScreen = GAME;
        levelTime = levelTime + timeAcumulated;
        timeAcumulated = 0;

    }

}

void winScreen() {

    DrawText("YOU WIN!", 250, 150, 40, GREEN);
    DrawText("PRESS SPACE to EXIT", 250, 195, 20, DARKGREEN);

    DrawText(TextFormat("Duration game: %.0f", totalGame), 10, 10, 20, BLACK);

    //Guardamos el tiempo, poniendo un bool para hacerlo s�lo una vez en el bucle
    if (!bWriteFile) {

        std::ofstream MyFile(urlRecordFile, std::ios_base::app);

        if (MyFile.is_open()) {
            MyFile << "\n" << (int)totalGame + 1;
            MyFile.close();
        }

        bWriteFile = true;
    }

    if (IsKeyDown(KEY_SPACE)) actualScreen = MENU;

}

void endScreen() {

    if (IsKeyDown(KEY_SPACE)) actualScreen = MENU;

    DrawText("Fin del juego", SCREEN_WIDTH / 2 - MeasureText("Fin del juego", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
    DrawText("PRESS SPACE to MENU", 250, 200, 20, DARKGREEN);

}