#pragma once

class Figures {

	bool isFinded;

public:

	Figures() {
		isFinded = false;
	}

	bool getIsFinded() { return isFinded; }
	void setIsFinded(bool pFinded) { isFinded = pFinded; }

};