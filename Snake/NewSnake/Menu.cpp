#include "Menu.h"
#include "TheSnakesGame.h"
#include <iostream>
#include <time.h>
#include <mmsystem.h>
#include <Windows.h>
#include <mmstream.h>

enum { EXITGAME = 0, MAINMENU = 1, KEEPPLAYING = 2 };

void Menu::initMenu()
{
	system("cls");
	srand((unsigned)time(0));

	gotoxy(32, 6);
	setTextColor(Color::LIGHTMAGENTA);

	cout << "*** WELCOME *** ";
	gotoxy(20, 7);

	setTextColor(Color::WHITE);
	gotoxy(20, 10);
	cout << "Please choose one of the optionts below:";
	gotoxy(32, 13);
	cout << "(1) Let's play!";
	gotoxy(32, 14);
	cout << "(9) Exit \n";
	getInput();
}

void Menu::getInput()
{
	char ch = _getch();
	PlaySound(TEXT("choose.wav"), NULL, SND_ASYNC);

	int choose = -1;
	switch (ch)
	{
	case '1':
	{
		bool exit1 = false;

		system("cls");
		preGameScreen();

		game.startGame();
		game.setBoard();
		game.init();
		while (exit1 != true)
		{
			if (game.run())//the user pressed ESC
			{
				choose = pauseMenu();
				if (choose == EXITGAME)
				{
					byeBye();
					exit1 = true;
				}
				else if (choose == MAINMENU)
					exit1 = true;

			}
			else
				exit1 = true; // if someone win the game 
		}

		if (choose == MAINMENU)
		{
			initMenu();
		}
		break;
	}

	case '9':
	{
		byeBye();
		break;
	}
	}
}


int Menu::pauseMenu()
{
	game.clearLines(2);
	char ch;
	gotoxy(0, 0);
	setTextColor(Color::WHITE);

	cout << "                    Please choose one of the options below:\n";
	setTextColor(Color::LIGHTCYAN);

	cout << " (1) Exit   ";
	cout << "(2) Back to main menu   ";
	cout << " (3) Resume game   ";
	cout << " (4) Restart this mission\n ";
	cout << "(5) Start a new mission       ";
	cout << "(6) Restart the game     (7) Replay\n";

	ch = _getch();
	PlaySound(TEXT("choose.wav"), NULL, SND_ASYNC);

	switch (ch)
	{
	case '1':
	{
		return EXITGAME;
		break;
	}


	case '2':
	{
		return MAINMENU;
		break;
	}


	case '3':
	{
		game.resGame(3);
		return KEEPPLAYING;
		break;
	}

	case '4':
	{
		game.resGame(4);
		return KEEPPLAYING;
		break;
	}


	case '5':
	{
		game.resGame(5);
		return KEEPPLAYING;
		break;
	}

	case '6':
	{
		system("cls");
		setTextColor(WHITE);
		game.startGame();
		game.setBoard();
		game.init();
		game.restCreatuersPos();
		return KEEPPLAYING;
		break;
	}
	default:
	{
		game.setReplay(true);
		game.replayRun();
		game.setReplay(false);
		pauseMenu();
		break;
	}
	}
}


void Menu::byeBye()
{
	PlaySound(TEXT("byebye.wav"), NULL, SND_ASYNC);
	system("cls");
	setTextColor(Color::LIGHTRED);
	gotoxy(37, 10);
	cout << "Bye Bye!\n";
	Sleep(500);
	setTextColor(Color::LIGHTMAGENTA);
	gotoxy(37, 10);
	cout << "Bye Bye!\n";
	Sleep(500);
	setTextColor(Color::LIGHTGREEN);
	gotoxy(37, 10);
	cout << "Bye Bye!\n";
	setTextColor(Color::LIGHTRED);
	gotoxy(37, 10);
	cout << "Bye Bye!\n";
	gotoxy(0, 0);
	setTextColor(Color::BLACK);
}

void Menu::preGameScreen()
{
	PlaySound(TEXT("GONEW.wav"), NULL, SND_ASYNC);
	setTextColor(LIGHTRED);

	gotoxy(0, 6);
	cout << "                                    _____________\n";
	cout << "                                   |\n";
	cout << "                                   |\n";
	cout << "                                   |\n";
	cout << "                                   |\n";
	cout << "                                   |_____________\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                   ______________|\n";

	Sleep(1200);

	system("cls");

	gotoxy(0, 6);
	cout << "                                   |             |\n";
	cout << "                                   |             |\n";
	cout << "                                   |             |\n";
	cout << "                                   |             |\n";
	cout << "                                   |             |\n";
	cout << "                                   |_____________|\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";

	Sleep(1200);

	system("cls");

	gotoxy(0, 6);
	cout << "                                    _____________\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                    _____________|\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                    _____________|\n";

	Sleep(1200);


	system("cls");

	gotoxy(0, 6);
	cout << "                                    _____________\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                                 |\n";
	cout << "                                    _____________|\n";
	cout << "                                   |\n";
	cout << "                                   |\n";
	cout << "                                   |\n";
	cout << "                                   |\n";
	cout << "                                   |_____________\n";

	Sleep(1000);

	system("cls");

	gotoxy(0, 6);
	cout << "                                        ___\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	cout << "                                           |\n";
	Sleep(1100);

	system("cls");

	gotoxy(0, 6);
	cout << "                            _____________     _____________ \n";
	cout << "                           |                 |             |\n";
	cout << "                           |                 |             |\n";
	cout << "                           |                 |             |\n";
	cout << "                           |                 |             |\n";
	cout << "                           |      _______    |             |\n";
	cout << "                           |             |   |             |\n";
	cout << "                           |             |   |             |\n";
	cout << "                           |             |   |             |\n";
	cout << "                           |             |   |             |\n";
	cout << "                           |_____________|   |_____________|\n";

	Sleep(1000);
	system("cls");
}