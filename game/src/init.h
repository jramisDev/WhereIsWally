//FPS
#define FPS 60

//WindowScreen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define GAME_TITLE "Where is Wally?"

enum Screens { MENU, GAME, NEXTLEVEL, WIN, GAMEOVER };

//Save records files
const char urlRecordFile[31] = "resources/saveGame/records.txt";
bool bWriteFile = false;

//Background
Texture2D background;
Texture2D backgroundTwo;
Texture2D backgroundThree;

//Variables
bool globalRunning = true;

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

void saveRecord();

void loadRecord();

void drawRecord(int recordIndex, int record, int height);