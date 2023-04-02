#pragma once
#pragma warning(disable : 4838)
#pragma warning(disable : 4244)


#include "raylib.h"
#include "init.h"
#include "functions.h"
#include <iostream>

Screens actualScreen = MENU;

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Where is Wally?");

    SetTargetFPS(FPS);

    bool globalRunning = true;

    int level = 1;
    int score = 0;
    bool gameOver = false;

    int levelTime = 20; // Duración del nivel en segundos
    float elapsedTime = 0.0f; // Tiempo transcurrido en segundos
    float timeAcumulated = 0.0f;

    // Generar tres figuras aleatorias
    Vector2 circlePos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(50, SCREEN_HEIGHT - 50) };
    Vector2 rectPos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(50, SCREEN_HEIGHT - 50) };
    Vector2 triPos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(50, SCREEN_HEIGHT - 50) };

    Color circleColor = GetRandomColor();
    Color rectColor = GetRandomColor();
    Color triColor = GetRandomColor();

    int circleRadius = GetRandomValue(10,50);
    int rectWidth = GetRandomShape() * 20 + 20;
    int rectHeight = GetRandomShape() * 20 + 20;
    Vector2 triP1 = { triPos.x - 25, triPos.y + 25 };
    Vector2 triP2 = { triPos.x + 25, triPos.y + 25 };
    Vector2 triP3 = { triPos.x, triPos.y - 25 };
    // Cada figura debe tener una posición aleatoria en la pantalla y una forma aleatoria


    while (globalRunning) {

        if (WindowShouldClose()) globalRunning = false;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        std::cout << "\n\nPantalla actual: " << actualScreen;

        switch (actualScreen) {
            case MENU: {

                actualScreen = MENU;

                level = 1;
                score = 0;
                gameOver = false;

                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RAYWHITE);
                DrawText(GAME_TITLE, 250, 150, 40, RED);
                DrawText("PRESS ENTER to GAME", 275, 195, 20, DARKGREEN);

                DrawText("CONTROLS:", 275, 250, 20, BLACK);
                DrawText("LEFT CLICK mouse button to CONFIRM object", 275, 275, 15, BLACK);

                if (IsKeyDown(KEY_ENTER)) actualScreen = GAME;

            }break;
            case GAME: {

                // Dibujar las tres figuras generadas aleatoriamente
                DrawCircle(circlePos.x, circlePos.y, circleRadius, circleColor);
                DrawRectangle(rectPos.x - rectWidth / 2, rectPos.y - rectHeight / 2, rectWidth, rectHeight, rectColor);
                DrawTriangle(triP1, triP2, triP3, triColor);

                // Si el usuario hace clic en una figura, aumentar la puntuación y eliminar la figura
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                    Vector2 mousePos = GetMousePosition();

                    if (CheckCollisionPointCircle(mousePos, circlePos, circleRadius)) {

                        score++;
                        circlePos = { -100, -100 }; // Eliminar la figura

                    }
                    else if (CheckCollisionPointRec(mousePos, { rectPos.x - rectWidth / 2, rectPos.y - rectHeight / 2, (float)rectWidth, (float)rectHeight })) {

                        score++;
                        rectPos = { -100, -100 }; // Eliminar la figura

                    }
                    else if (CheckCollisionPointTriangle(mousePos, triP1, triP2, triP3)) {

                        score++;
                        triPos = { -100, -100 }; // Eliminar la figura
                        triP1 = { -500, -500 };
                        triP2 = { -500, -500 };
                        triP3 = { -500, -500 };

                    }
                }

                // Si todas las figuras han sido eliminadas, pasar al siguiente nivel
                if (!gameOver && score == 3) {
                    timeAcumulated = levelTime - elapsedTime;
                    level++;
                    score = 0;
                    elapsedTime = 0.0f; // Reiniciar el tiempo transcurrido

                    GenerateRandomShapes(circlePos, circleRadius, circleColor,
                        rectPos, rectWidth, rectHeight, rectColor,
                        triPos, triP1, triP2, triP3, triColor);

                    

                    if (level < 4) actualScreen = NEXTLEVEL;
                    if (level == 4) actualScreen = WIN;

                    

                }

                



                // Mostrar el nivel y la puntuación en la pantalla
                DrawText(TextFormat("Nivel: %i", level), 10, 10, 20, BLACK);
                DrawText(TextFormat("Tiempo: %.0f", levelTime - elapsedTime), 10, 30, 20, BLACK);
                DrawText(TextFormat("elapsedTime: %.0f", elapsedTime), 10, 50, 20, BLACK);
                DrawText(TextFormat("timeAcumulated: %i", timeAcumulated), 10, 70, 20, BLACK);

                // Actualizar el tiempo transcurrido
                elapsedTime += GetFrameTime();
                if (elapsedTime >= levelTime) {
                    gameOver = true; // El tiempo ha terminado
                    actualScreen = GAMEOVER;
                }

            }break;
            case NEXTLEVEL: {

                DrawText("YOU WIN! Loading next level", 150, 150, 40, GREEN);
                DrawText("PRESS SPACE to MENU", 250, 195, 20, DARKGREEN);

                DrawText(TextFormat("timeAcumulated: %.0f", timeAcumulated), 10, 70, 20, BLACK);
                

                if (IsKeyDown(KEY_SPACE)) actualScreen = GAME;
            }break;
            case WIN: {

                DrawText("YOU WIN!", 250, 150, 40, GREEN);
                DrawText("PRESS SPACE to EXIT", 250, 195, 20, DARKGREEN);

                //if (IsKeyDown(KEY_SPACE)) actualScreen = MENU;
                if (IsKeyDown(KEY_SPACE)) {
                    //SaveStorageValue(STORAGE_POSITION_SCORE, score);
                    globalRunning = false;
                } 
            }break;
            case GAMEOVER: {

                DrawText("Fin del juego", SCREEN_WIDTH / 2 - MeasureText("Fin del juego", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
                DrawText("PRESS SPACE to MENU", 250, 200, 20, DARKGREEN);

                if (IsKeyDown(KEY_SPACE)) actualScreen = MENU;
            }break;
        }        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}