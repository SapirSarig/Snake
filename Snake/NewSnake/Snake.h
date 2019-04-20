#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include "List.h"
#include <vector>

class TheSnakesGame;

typedef struct LocationAndDir {
	Point p;
	int dir;
}LocationAndDir;


class Snake {

	enum { MAXSIZE = 15 };
	Point* body;
	int direction;
	int size;
	char arrowKeys[5];
	Color color;
	char figure;
	TheSnakesGame* theGame;
	int score = 0;
	int bulletCounter = 5;
	List* bulletList;

public:
	Snake(Color c, Point head, int dir, char ch, int length)
	{
		body = new Point[MAXSIZE];
		color = c;
		figure = ch;
		body[0] = head;
		size = length;
		direction = dir;
		bulletList = new List;
	}
	~Snake()
	{
		delete[] body;
	}
	void setReplayScore(int _score)
	{
		score = _score;
	}
	void setScore()
	{
		score++;
	}
	void resetScore()
	{
		score = 0;
	}
	int getScore()
	{
		return score;
	}

	void grow()
	{
		if (size < MAXSIZE)
			size++;
	}

	void setFigure(const char& ch) {
		figure = ch;
	}
	char getFigure() {
		return figure;
	}
	int getDir() {
		return direction;
	}
	Point getPos() {
		return body[0];
	}
	void setGame(TheSnakesGame* _theGame) {
		theGame = _theGame;
	}
	void setPosition(const int& x, const int& y) {
		body[0].set(x, y);
	}
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
		arrowKeys[4] = keys[4];
	}
	void setColor(const Color& c) {
		color = c;
	}
	void move();
	int getDirection(const char& key);
	void setDirection(const int& dir) {
		direction = dir;
	}
	bool validDirection(const int& newDir);
	void draw();
	void setSize(const int& _size)
	{
		size = _size;
	}

	int getNumOfBullets()
	{
		return bulletCounter;
	}
	void winBullet()
	{
		bulletCounter++;
	}
	void loseBullet()
	{
		bulletCounter--;
	}
	void resetBulletCounter()
	{
		bulletCounter = 5;
	}

	Color getColor()
	{
		return color;
	}
	List* getList()
	{
		return bulletList;
	}
	int getSize()
	{
		return size;
	}

	void deleteSnake(); // the function makes the snake disappear from the board 
	void AppearSnake(vector <LocationAndDir> & LD0, vector <LocationAndDir> & LD1);// the function return the sanke to the board 
}; 

#endif