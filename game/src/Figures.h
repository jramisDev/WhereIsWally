#pragma once

#include "raylib.h"

class Figures {

	bool isFinded;

public:

	Figures() {
		isFinded = false;
	}

	bool isFinded() { return isFinded; }
	void setIsFinded(bool pFinded) { isFinded = pFinded; }

};