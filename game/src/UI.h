#pragma once

#include "raylib.h"

class UI {

	Rectangle rectTime;
	Rectangle rectFigures;
	Color backgroundColor;

public:

	UI(){

		Rectangle r;
		r.x = 0;
		r.y = 0;
		r.width = 200;
		r.height = 100;
		rectTime = r;

		r.x = SCREEN_WIDTH - 200;
		r.y = 0;
		r.width = 200;
		r.height = 100;
		rectFigures = r;

		backgroundColor = BLACK;

		//DrawRectangle(0, 0, 200, 100, BLACK);
		//DrawRectangle(SCREEN_WIDTH - 200, 0, 200, 100, BLACK);
	}

	
	//UI(Color pNormal, Color pHover, int pDescLength, char* pDesc, float posX, float posY, float pWidth, float pHeight) {
	//	backgroundColor = pNormal;

	//	Rectangle r;
	//	r.x = posX;
	//	r.y = posY;
	//	r.width = pWidth;
	//	r.height = pHeight;
	//	rect = r;
	//}

	

private:

};