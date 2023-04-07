class Figures {

	bool isFinded;
	Color color;

public:

	Figures() {
		isFinded = false;
		color = GetRandomColor();
	}

	bool getIsFinded() { return isFinded; }
	void setIsFinded(bool pFinded) { isFinded = pFinded; }

	Color getColor() { return color; }
	void setColor(Color pColor) { color = pColor; };

};