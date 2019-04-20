#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "io_utils.h"
#include "Snake.h"
#include "Point.h"
#include "Questions.h"
#include "Bullet.h"
#include "List.h"
#include "Creature.h"
#include "qManager.h"
#include <vector>
using namespace std;

enum { ROWS = 21, COLS = 80 };
enum { STEPS = 5, HIGHSCORE = 12 };
enum { NUMQUEST = 5 };

typedef struct replaySnakeData {
	int score;
	int size;
	int dir;
	Point p;
};

typedef struct replayNumbers {
	NUMBER num;
	int enterNum; // if it's 0, then the number was on screen, else the num added while playing
};

typedef struct SnakeDisappear {
	int timer = 0;
	bool isDisappear = false;
}SnakeDisappear;

class TheSnakesGame {
	enum { ESC = 27 };
	qManager* qm;
	int qArrSize, cArrSize;
	Snake *s[2];
	char board[ROWS + 3][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	Creature** cArr;

	// replay data
	bool replay = false;
	vector <int> timer; // will hold the time of each key that was hit
	vector <char> keys; // will hold the keys that were hit 
	vector <replayNumbers> numbers; // will hold the number that will be print on board
	// will hold the location and the dir of the snakes before they appear on screen 
	vector <LocationAndDir> s0LD;
	vector <LocationAndDir> s1LD;
	int saveCurrQ; // will hold the currQ for replay 
	char resBoardFromReplay[ROWS][COLS];
	int replayTimer = 0;
	LocationAndDir SLD[2]; // will hold the snakes pos nad dir int a struct
	replayNumbers replayNum;
	replaySnakeData snakeData[2]; // will hold the socre and size of the snakes before winning a score 
	int newNumbersIndex = 0, s0Index = 0, s1Index = 0, timerIndex = 0;

public:
	TheSnakesGame() {
		s[0] = new Snake(YELLOW, Point(10, 9), 3, '@', 3);
		s[1] = new Snake(MAGENTA, Point(70, 9), 2, '#', 3);

		cArrSize = creatCreature(&cArr);
		qm = new qManager;
	}
	~TheSnakesGame()
	{
		
		for (int i = 0; i < 2; i++)
		{
			delete s[i];
		}
		for (int i = 0; i < cArrSize; i++)
		{
			delete cArr[i];
		}
		delete cArr;
		delete qm;


	}
	void setBoard(); //copy board sent to us into originalBoard, setArrowKeys, setColor
	void init(); //copy original board to actual board and set Snakes Start point
	bool isSnake(const Point& p); // gets a point and checks if it's a part of any snake's body
	bool isNum(const Point& p); // gets a point and checks if it's a number on the board 
	bool run(); // run 2 Snakes with Keyboard
	void updateBoard(const int& x, const int& y, const char& ch); // get a point and a char. puts the char at the point in the board
	bool checkPlace(const int& x, const int& y, const int& size); // check if the poing is a valid point to put a number on the board
	void resGame(const int& choose); // function that start all the function for resume game, restart mission and restart game
	int randNum(); // will return a random number between 0 to 169 
	NUMBER checkNum(int x, int y); // gets a point and check if it's a nubmber 
	int countDigits(int num); // get a number and check how many digits are in the number
	void clearLines(const int& line); 
	void clearBoard();
	void printBoard();
	void clearnNumberFromBoard(const NUMBER& num);
	void printScoreAndBullets();
	void removeHalfOfNumbersFromArrAndBoard();
	bool checkAndMarkCorrectAnswers(const Color& color);
	void noOneFoundAnswer(); // if there are 60 answers and no one found an answer, the function will mark the correct answer and start a new mission
	bool isWinner(const int& score, const int& snakeNum); // check if any snake got the winning score 
	void startGame();
	void resetSnakePos();
	void soundEffect(const bool& correct);
	bool worngAnswerAndAWin(const int& i); // if the snake collect a worng answer, it will make the other sanke grow and win a socre.
	void stepCounter(const int& count, NUMBER num, SnakeDisappear disappear[2], Creature* eater, int&dir1, int&dir2); // check how many steps the snakes did and if the steps%5 ==0 then it will print a random number 
	void snakeOnSnakeCheck(SnakeDisappear missingSanke[2]); // check if the snake ran into each other 
	int whoIsShooting(const char& key);
	Point getNextPointBullet(Node* curr);
	Point getBulletBornPos(const int& dir, const int& i);
	int checkShotHit(const Point& p, Node* curr, const int& i); // check all the options of the next point of bullet ( ' ', '*' , snakes' figure, a number)
	int whichSnake(const Point& p);
	void removeAllBulletsFromBoard();
	void landOnNum(const int& x, const int& y, const int& dir, const char&  figure); // check if the body of the snake going to land on a number in the board. it will remove the number if it does
	void isSnakeStuck(); 		// check if the snake ran into itself and can't move direction
	void snakeShotABullet(const int& snakeShoot, const int& i, int shootNum[2], SnakeDisappear isSnakeDissaper[2]); // check if the snake have bullets on stack and add them into the list of bullets.
	int creatCreature(Creature ***cArr);
	void moveCreature(Creature *pc, SnakeDisappear isSnakeDissaper[2]);
	bool isCreature(Point p);
	int whichCreature(Point p);
	bool isBullet(Point p);
	void snakeTouchedNumEater(int i, qManager *q);
	int SwitchDir(int dir);
	bool checkEqEatenNumAndClosestNum(NUMBER resNum, NUMBER ClosestNum);
	void goToClosestNum(int &dir1, int &dir2, Creature* eater);
	void searchNewClosestNum(int &dir1, int &dir2, Creature* eater);
	//int createQuestionsArr(Questions ***qArr);
	void checkDeadCreature();
	void saveBeginingSnakeData();
	void saveCurrNumbersOnScreen();
	void restAllReplayData();
	bool isReplay() { return replay; }
	LocationAndDir* getSLD() { return SLD; }
	vector <LocationAndDir> *getVecS0() { return &s0LD;}
	vector <LocationAndDir> *getVecS1() { return &s1LD; }
	int getIndexS0() { return s0Index; }
	void setIndexS0() { s0Index++; }
	int getIndexS1() { return s1Index; }
	void setIndexS1() { s1Index++; }
	void setReplay(bool _replay) { replay = _replay; }
	void replayRun();
	void printNumbersOnScreen();
	void restoreSnakeData();
	void restCreatuersPos();



};

#endif