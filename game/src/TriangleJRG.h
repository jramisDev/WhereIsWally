class TriangleJRG :public Figures {

	Vector2 position;

	Vector2 triP1;
	Vector2 triP2;
	Vector2 triP3;

public:
	TriangleJRG() {
		position = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(200, SCREEN_HEIGHT - 50) };
		triP1 = { position.x - 25, position.y + 25 };
		triP2 = { position.x + 25, position.y + 25 };
		triP3 = { position.x, position.y - 25 };
	}
	TriangleJRG(Color pColor) {
		position = { (float)GetRandomValue(50, SCREEN_WIDTH - 50), (float)GetRandomValue(200, SCREEN_HEIGHT - 50) };
		triP1 = { position.x - 25, position.y + 25 };
		triP2 = { position.x + 25, position.y + 25 };
		triP3 = { position.x, position.y - 25 };
		setColor(pColor);
	}

	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pPosition) { position = pPosition; }

	Vector2 getTriP1() { return triP1; }
	void setTriP1(Vector2 pTriP1) { triP1 = pTriP1; }

	Vector2 getTriP2() { return triP2; }
	void setTriP2(Vector2 pTriP2) { triP2 = pTriP2; }

	Vector2 getTriP3() { return triP3; }
	void setTrip3(Vector2 pTriP3) { triP3 = pTriP3; }

};