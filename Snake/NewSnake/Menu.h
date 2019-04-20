#ifndef _MENU_H_
#define _MENU_H_
#include "TheSnakesGame.h"



class Menu {
	TheSnakesGame game;
public:
	void initMenu(); //copy original board to actual board and set Snakes Start point
	int pauseMenu();
	void printInstructions();
	void getInput();
	void byeBye();
	void preGameScreen();

};



#endif