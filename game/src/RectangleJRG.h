class RectangleJRG :public Figures{

	int width;
	int height;
	Vector2 position;

public:
	RectangleJRG() {
		width = 100;
		height = 50;
		position = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(100, SCREEN_HEIGHT - 200) };
	}
	RectangleJRG(Color pColor) {
		width = 100;
		height = 50;
		position = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(100, SCREEN_HEIGHT - 200) };
		setColor(pColor);
	}

	int getWidth() { return width; }
	int getHeight() { return height; }

	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pPosition) { position = pPosition; }
};