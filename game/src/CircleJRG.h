#pragma once

#include "raylib.h"

class CircleJRG :public Figures {

	int radius;

public:
	CircleJRG() {
		radius = 25;
	}

	int getRadius() { return radius; }

};
