class CircleJRG :public Figures {

	int radius;
	Vector2 position;

public:
	CircleJRG() {
		radius = 25;
		position = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(100, SCREEN_HEIGHT - 200) };
	}
	CircleJRG(Color pColor) {
		radius = 25;
		position = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(100, SCREEN_HEIGHT - 200) };
		setColor(pColor);
	}

	int getRadius() { return radius; }

	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pPosition) { position = pPosition; }

};
