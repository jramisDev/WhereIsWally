#include "raylib.h"

int screenWidth = 800;
int screenHeight = 450;

// Devuelve un color aleatorio
Color GetRandomColor(){

    int r = GetRandomValue(0, 255);
    int g = GetRandomValue(0, 255);
    int b = GetRandomValue(0, 255);

    return Color{ static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255 };

}

// Devuelve un número aleatorio entre 1 y 5
int GetRandomShape(){
    return GetRandomValue(1, 5);
}

void GenerateRandomShapes(Vector2& circlePos, int& circleRadius, Color& circleColor,
    Vector2& rectPos, int& rectWidth, int& rectHeight, Color& rectColor,
    Vector2& triPos, Vector2& triP1, Vector2& triP2, Vector2& triP3, Color& triColor){

    circlePos = { (float)GetRandomValue(50, screenWidth - 50), (float)GetRandomValue(50, screenHeight - 50) };

    rectPos = { (float)GetRandomValue(50, screenWidth - 50), (float)GetRandomValue(50, screenHeight - 50) };

    triPos = { (float)GetRandomValue(50, screenWidth - 50), (float)GetRandomValue(50, screenHeight - 50) };
    triP1 = { triPos.x - 25, triPos.y + 25 };
    triP2 = { triPos.x + 25, triPos.y + 25 };
    triP3 = { triPos.x, triPos.y - 25 };
}

int main() {

    InitWindow(screenWidth, screenHeight, "Where is Wally?");

    SetTargetFPS(60);

    int level = 1;
    int score = 0;

    // Generar tres figuras aleatorias
    Vector2 circlePos = { GetRandomValue(50, screenWidth - 50), GetRandomValue(50, screenHeight - 50) };
    Vector2 rectPos = { GetRandomValue(50, screenWidth - 50), GetRandomValue(50, screenHeight - 50) };
    Vector2 triPos = { GetRandomValue(50, screenWidth - 50), GetRandomValue(50, screenHeight - 50) };

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

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

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

            } else if (CheckCollisionPointRec(mousePos, { rectPos.x - rectWidth / 2, rectPos.y - rectHeight / 2, (float)rectWidth, (float)rectHeight })) {
                                
                score++;
                rectPos = { -100, -100 }; // Eliminar la figura

            } else if (CheckCollisionPointTriangle(mousePos, triP1, triP2, triP3)) {
                
                score++;
                triPos = { -100, -100 }; // Eliminar la figura
                triP1 = { -500, -500 };
                triP2 = { -500, -500 };
                triP3 = { -500, -500 };

            }
        }

        // Si todas las figuras han sido eliminadas, pasar al siguiente nivel
        if (score == 3) {
            level++;
            score = 0;

            GenerateRandomShapes(circlePos, circleRadius, circleColor,
                rectPos, rectWidth, rectHeight, rectColor,
                triPos, triP1, triP2, triP3, triColor);

        }

        // Mostrar el nivel y la puntuación en la pantalla
        DrawText(TextFormat("Nivel: %i", level), 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}