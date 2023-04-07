#pragma warning(disable : 4838)//Quito warnings de cast que me molestan
#pragma warning(disable : 4244)

#include "raylib.h"
#include "Init.h"
#include "LevelData.h"
#include "Figures.h"
#include "CircleJRG.h"
#include "TriangleJRG.h"
#include "RectangleJRG.h"
#include "Functions.h"

LevelData game;

RectangleJRG rectangle;
CircleJRG circle;
TriangleJRG triangle;


int main() {

    initApp();

    while (globalRunning) {

        if (WindowShouldClose()) globalRunning = false;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (game.getScreenActual()) {
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

    game = LevelData();

    rectangle = RectangleJRG();
    circle = CircleJRG();
    triangle = TriangleJRG();

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RAYWHITE);
    DrawText(GAME_TITLE, 250, 100, 40, RED);
    DrawText("PRESS ENTER to GAME", 275, 140, 20, DARKBLUE);

    DrawText("CONTROLS:", 275, 180, 20, BLACK);
    DrawText("LEFT CLICK mouse button to CONFIRM object", 275, 200, 15, BLACK);

    DrawText("Records:", 275, 235, 15, DARKGREEN);

    loadRecord();

    if (IsKeyDown(KEY_ENTER)) game.setScreenActual(GAME);

}

void gameScreen() {

    DrawTexture(background, 0, 0, WHITE);

    DrawRectangle(0, 0, 150, 40, BLACK);//Left backbroundUI
    DrawRectangle(SCREEN_WIDTH - 300, 0, 300, 100, BLACK);//Right backgroundUI

    // Dibujar las tres figuras en la UI
    if (!circle.getIsFinded())  DrawCircle(550, 50, circle.getRadius(), circle.getColor());
    if (!rectangle.getIsFinded())  DrawRectangle(600, 25, rectangle.getWidth(), rectangle.getHeight(), rectangle.getColor());
    if (!triangle.getIsFinded())   DrawTriangle({ 750,25 }, { 725,75 }, { 775,75 }, triangle.getColor());

    // Dibujar las tres figuras generadas aleatoriamente
    DrawCircle(circle.getPosition().x, circle.getPosition().y, circle.getRadius(), circle.getColor());
    DrawRectangle(rectangle.getPosition().x - rectangle.getWidth() / 2, rectangle.getPosition().y - rectangle.getHeight() / 2, rectangle.getWidth(), rectangle.getHeight(), rectangle.getColor());
    DrawTriangle(triangle.getTriP1(), triangle.getTriP2(), triangle.getTriP3(), triangle.getColor());

    // Si el usuario hace clic en una figura, aumentar la puntuación y eliminar la figura
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointCircle(mousePos, circle.getPosition(), circle.getRadius())) {

            game.sumScore();
            circle.setPosition({ -100, -100 });
            circle.setIsFinded(true);

        } else if (CheckCollisionPointRec(mousePos, { rectangle.getPosition().x - rectangle.getWidth() / 2, rectangle.getPosition().y - rectangle.getHeight() / 2, (float)rectangle.getWidth(), (float)rectangle.getHeight() })) {

            game.sumScore();
            rectangle.setPosition({ -100, -100 });
            rectangle.setIsFinded(true);

        } else if (CheckCollisionPointTriangle(mousePos, triangle.getTriP1(), triangle.getTriP2(), triangle.getTriP3())) {

            game.sumScore();
            triangle.setPosition({ -100, -100 });
            triangle.setTriP1({ -500, -500 });
            triangle.setTriP2({ -500, -500 });
            triangle.setTrip3({ -500, -500 });
            triangle.setIsFinded(true);

        }
    }

    // Si todas las figuras han sido eliminadas, pasar al siguiente nivel
    if (!game.isGameOver() && game.getScore() == 3) {

        game.addTotalGame(game.getElapsedTime());
        game.setTimeAcumulated(game.getLevelTime() - game.getElapsedTime());

        game.sumLevel();
        game.resetScore();
        game.resetElapsedTime();// Reiniciar el tiempo transcurrido

        rectangle = RectangleJRG(rectangle.getColor());
        circle = CircleJRG(circle.getColor());
        triangle = TriangleJRG(triangle.getColor());

        if (game.getLevel() == 2) background = backgroundTwo;
        if (game.getLevel() == 3) background = backgroundThree;

        if (game.getLevel() < 4) game.setScreenActual(NEXTLEVEL);
        if (game.getLevel() == 4) game.setScreenActual(WIN);

    }

    DrawText(TextFormat("Tiempo: %.0f", game.getLevelTime() - game.getElapsedTime()), 10, 10, 20, WHITE);

    // Actualizar el tiempo transcurrido
    game.addElapsedTime(GetFrameTime());

    if (game.getElapsedTime() >= game.getLevelTime()) {
        game.setGameOver(true); // El tiempo ha terminado
        game.setScreenActual(GAMEOVER);
    }

}

void nextScreen() {

    DrawText("YOU WIN! Loading next level", 150, 150, 40, GREEN);
    DrawText("PRESS SPACE to MENU", 250, 195, 20, DARKGREEN);

    //DrawText(TextFormat("Time acumulated: %.0f", game.getTimeAcumulated()), 10, 10, 20, BLACK);

    if (IsKeyDown(KEY_SPACE)) {
        game.setScreenActual(GAME);
        game.sumLevelTime(game.getTimeAcumulated());
        game.resetTimeAcumulated();
    }

}

void winScreen() {

    DrawText("YOU WIN!", 250, 150, 40, GREEN);
    DrawText("PRESS SPACE to EXIT", 250, 195, 20, DARKGREEN);

    DrawText(TextFormat("Duration game: %.0f", game.getTotalGame()), 10, 10, 20, BLACK);

    saveRecord(game.getTotalGame());

    if (IsKeyDown(KEY_SPACE)) game.setScreenActual(MENU);

}

void endScreen() {

    if (IsKeyDown(KEY_SPACE)) game.setScreenActual(MENU);

    DrawText("Fin del juego", SCREEN_WIDTH / 2 - MeasureText("Fin del juego", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
    DrawText("PRESS SPACE to MENU", 250, 200, 20, DARKGREEN);

}