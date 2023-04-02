/*
    TO-DO:

    Añadir cuadro de color sobre el texto de arriba a la izquierda para que se vea bien el tiempo
    Figuras arriba a la derecha, sobre un fondo de color para que se vean, se eliminan los iconos al pulsar sobre la figura.
    Bug del cambio de pantallas
    Bug tiempo acumulado al pasar de pantalla
    Refactirar código

*/

#pragma once
#pragma warning(disable : 4838)//Quito warnings de cast que me molestan
#pragma warning(disable : 4244)

#include "raylib.h"
#include "init.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    //Background
    Texture2D background = LoadTexture("resources/background/one.png");
    Texture2D backgroundTwo = LoadTexture("resources/background/two.png");
    Texture2D backgroundThree = LoadTexture("resources/background/three.png");    

    SetTargetFPS(FPS);

    float elapsedTime = 0.0f; // Tiempo transcurrido en segundos
    float timeAcumulated = 0.0f;
    float totalGame = 0.0f;

    // Generar tres figuras aleatorias
    Vector2 circlePos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(50, SCREEN_HEIGHT - 100) };
    Vector2 rectPos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(50, SCREEN_HEIGHT - 100) };
    Vector2 triPos = { GetRandomValue(50, SCREEN_WIDTH - 50), GetRandomValue(50, SCREEN_HEIGHT - 100) };

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

            }break;
            case GAME: {

                DrawTexture(background, 0, 0, WHITE);

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
                    totalGame = totalGame + elapsedTime;
                    timeAcumulated = levelTime - elapsedTime;
                    level++;
                    score = 0;
                    elapsedTime = 0.0f; // Reiniciar el tiempo transcurrido

                    GenerateRandomShapes(circlePos, circleRadius, circleColor,
                        rectPos, rectWidth, rectHeight, rectColor,
                        triPos, triP1, triP2, triP3, triColor);

                    
                    if (level == 2) background = backgroundTwo;
                    if (level == 3) background = backgroundThree;

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

                DrawText(TextFormat("Duration game: %.0f", totalGame), 10, 10, 20, BLACK);

                //Guardamos el tiempo, poniendo un bool para hacerlo sólo una vez en el bucle
                if (!bWriteFile) {

                    std::ofstream MyFile(urlRecordFile, std::ios_base::app);

                    if (MyFile.is_open()) {
                        MyFile << "\n" << (int)totalGame+1;
                        MyFile.close();
                    }

                    bWriteFile = true;
                }


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