#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

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

void GenerateRandomShapes(Vector2& circlePos,
    Vector2& rectPos,
    Vector2& triPos, Vector2& triP1, Vector2& triP2, Vector2& triP3) {

    circlePos = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(50, SCREEN_HEIGHT - 50) };

    rectPos = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(50, SCREEN_HEIGHT - 50) };

    triPos = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(50, SCREEN_HEIGHT - 50) };
    triP1 = { triPos.x - 25, triPos.y + 25 };
    triP2 = { triPos.x + 25, triPos.y + 25 };
    triP3 = { triPos.x, triPos.y - 25 };
}

void loadRecord() {

    std::string linea;
    std::ifstream MyFile(urlRecordFile);
    std::vector<int> numeros;
    int numero;

    while (MyFile >> numero) {
        numeros.push_back(numero);
    }
    MyFile.close();

    // Ordenar el vector en orden descendente
    std::sort(numeros.begin(), numeros.end(), std::less<int>());

    int j = 0;
    for (int i = 0; i < 3 && i < numeros.size(); i++) {
        drawRecord(i, numeros[i], j);
        j += 20;
    }

}

void saveRecord(int totalGame) {

    //Guardamos el tiempo, poniendo un bool para hacerlo sólo una vez en el bucle
    if (!bWriteFile) {

        std::ofstream MyFile(urlRecordFile, std::ios_base::app);

        if (MyFile.is_open()) {
            MyFile << "\n" << totalGame;
            MyFile.close();
        }

        bWriteFile = true;
    }

}

void drawRecord(int recordIndex, int record, int height) {

    std::string position = "First: ";

    if (recordIndex == 1) {
        position = "Second: ";
    } else if(recordIndex == 2){
        position = "Third: ";
    }

    DrawText(position.append(std::to_string(record)).append(" s").c_str(), 275, 250 + height, 15, DARKGREEN);

}