#pragma once

#include "raylib.h"

class RectangleJRG :public Figures{

	int width;
	int height;

public:
	RectangleJRG() {
		width = 100;
		height = 50;
	}

	int getWidth() { return width; }
	int getHeight() { return height; }
};