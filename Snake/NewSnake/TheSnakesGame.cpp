#include "TheSnakesGame.h"
#include <cstdlib>
#include <ctime>
#include <mmsystem.h>
#include <Windows.h>
#include <mmstream.h>
#include "Bullet.h"
#include "List.h"
#include "Creature.h"
#include "NumEater.h"
#include "ColsFlyer.h"
#include "RowsFlyer.h"
#include <fstream>
#include <string.h>
#include "dividesByX.h"
#include "inRange.h"
#include "Equation.h"
#include "sumDigits.h"
#include "dividesByAnotB.h"

void TheSnakesGame::init() {
	qm->setCurrQuestion(rand() % NUMQUEST);
	int currQ = qm->getCurrQuestion();
	qm->getQuestionFromArr(currQ)->randNum();
	qm->getQuestionFromArr(currQ)->set();
	qm->getQuestionFromArr(currQ)->print();
	//qArr[(*qArr)->getCurrQuestion()]->print(); //prints a random question

	for (int i = 0; i < 2; i++)
		s[i]->resetBulletCounter();
	restCreatuersPos();
}


bool TheSnakesGame::run() {
	int count = 0;
	char key = 2;
	int dir;
	int snakeShoot = -1;
	int shootNum[2] = { 0 };
	SnakeDisappear isSnakeDissaper[2];
	bool isCorrect;
	int dir1, dir2;

	restAllReplayData();
	saveBeginingSnakeData();
	saveCurrNumbersOnScreen();
	qm->setEatenClosestNum(true);

	NUMBER num;
	do {
		replayTimer = count;
		printScoreAndBullets();

		if (_kbhit())
		{
			key = _getch();
			// save the key that was hit at the replayTimer time 
			keys.push_back(key);
			timer.push_back(replayTimer);
			if (key == ESC)
				continue;
		}

		for (int i = 0; i < 5; i++)
		{
			if (!(cArr[i]->is_Dead()))
			{
				cArr[i]->draw();
				updateBoard(cArr[i]->getX(), cArr[i]->getY(), cArr[i]->getFigure());

				if (i != 0) // not a numEater
				{
					if (!(cArr[i]->is_Dead()))
					{
						moveCreature(cArr[i], isSnakeDissaper);
						if (cArr[i]->getSpeed() == 2)
							moveCreature(cArr[i], isSnakeDissaper);
					}
				}
			}
		}
		snakeOnSnakeCheck(isSnakeDissaper);

		for (int i = 0; i < 2; i++)
		{
			if (key == ESC)
				continue;
			snakeShoot = whoIsShooting(key);
			snakeShotABullet(snakeShoot, i, shootNum, isSnakeDissaper);

			if ((dir = s[i]->getDirection(key)) != -1) {
				if (s[i]->validDirection(dir))
					s[i]->setDirection(dir);
			}

			Point next = s[i]->getPos().next(s[i]->getDir());
			if ((isNum(next))) //checks if the snake ate a number
			{
				NUMBER resNum = checkNum(next.getX(), next.getY());
				int currQ = qm->getCurrQuestion();
				qm->getQuestionFromArr(currQ)->isCorrect(resNum.value, isCorrect);

				if (isCorrect)
				{
					setTextColor(LIGHTRED);
					s[i]->grow();
					s[i]->setScore();

					if (isWinner(s[i]->getScore(), i))
						return false;

					clearLines(1);
					gotoxy(0, 1);
					cout << "		       Snake " << i + 1 << " CORRECT!";
					soundEffect(true);
					Sleep(700);
					clearLines(1);
				}

				else
				{
					setTextColor(LIGHTRED);

					if (checkAndMarkCorrectAnswers(LIGHTRED))
					{
						gotoxy(0, 1);
						cout << "		       Snake " << i + 1 << " WORNG!    THE ANSWERS ARE: ";
						soundEffect(false);
						Sleep(700);
						checkAndMarkCorrectAnswers(WHITE);
					}
					else
					{
						gotoxy(0, 1);
						cout << "	   Snake " << i + 1 << " WORNG!    THERE WERE NO CORRECT ANSWERS ON THE SCREEN!! ";
						soundEffect(false);
						Sleep(1000);
					}

					clearLines(1);
					if (!worngAnswerAndAWin(i))
						return false;

				}
				//if (_kbhit())
				//{
				//	key = _getch();
				//	keys.push_back(key);
				//	timer.push_back(replayTimer);
				//	if (key == ESC)
				//		continue;
				//}

				Sleep(100);
				clearnNumberFromBoard(resNum);
				qm->removeNumberFromArr(resNum);
				removeHalfOfNumbersFromArrAndBoard();
				removeAllBulletsFromBoard();
				s[0]->resetBulletCounter();
				s[1]->resetBulletCounter();
				restCreatuersPos();
				clearLines(0);
				count = 0;

				// rest replay data and save all the begining data on screen 
				restAllReplayData();
				saveBeginingSnakeData();
				saveCurrNumbersOnScreen();

				qm->setCurrQuestion(rand() % NUMQUEST);
				currQ = qm->getCurrQuestion();
				qm->getQuestionFromArr(currQ)->randNum();
				qm->getQuestionFromArr(currQ)->set();
				qm->getQuestionFromArr(currQ)->print();
				checkDeadCreature();
				isSnakeStuck();
			}
			else if (isCreature(next))
			{
				int creatureType = whichCreature(next);
				if (creatureType != 0) // the creature is colsflyer or rowsflyer
				{
					isSnakeDissaper[i].isDisappear = true;
					s[i]->deleteSnake();
				}
				else // snake eaten by numEater 
				{
					count = 0;
					snakeTouchedNumEater(i, qm);
				}
			}
		}
		if (key == ESC)
			continue;
		count++;
		stepCounter(count, num, isSnakeDissaper,cArr[0], dir1,dir2);

		if (key != ESC)
			key = -1;
		Sleep(100);
	} while (key != ESC);

	clearLines(0);

	return true;

}

bool TheSnakesGame::isSnake(const Point& p) {
	return (board[p.getY()][p.getX()] == s[0]->getFigure() || board[p.getY()][p.getX()] == s[1]->getFigure());
}


bool TheSnakesGame::isNum(const Point& p) {
	if (('0' <= board[p.getY()][p.getX()]) && (board[p.getY()][p.getX()] <= '9'))
		return true;
	return false;

}

void TheSnakesGame::setBoard() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i + 3][j] = ' ';
		}
		board[i + 3][COLS] = '\0';
	}

	s[0]->setArrowKeys("wxadz");
	s[0]->setGame(this);

	s[1]->setArrowKeys("imjln");
	s[1]->setGame(this);

}

void TheSnakesGame::updateBoard(const int& x, const int& y, const char& ch)
{
	board[y][x] = ch;
}

bool TheSnakesGame::checkPlace(const int& x, const int& y, const int& size)
{
	for (int i = 0; i < size; i++)
	{

		if (board[y][x + i] != ' ')
		{
			return false;
		}

		if (board[y + 1][x + i] <= '9' && '0' <= board[y + 1][x + i])
		{
			return false;
		}


		if (board[y - 1][x + i] <= '9' && '0' <= board[y - 1][x + i])
		{
			return false;
		}
	}

	if (x > 0)
	{
		if (board[y][x - 1] != ' ')
		{
			return false;
		}
	}

	if (board[y][x + size] != ' ')
	{
		return false;
	}
	return true;

}


void TheSnakesGame::resGame(const int& choose)
{
	setTextColor(WHITE);
	system("cls");

	switch (choose)
	{
	case 3:
	{
		qm->getQuestionFromArr(qm->getCurrQuestion())->set();
		qm->getQuestionFromArr(qm->getCurrQuestion())->print();
		printBoard();
		for (int i = 0; i < 2; i++)
		{
			s[i]->draw();
		}
	}
	break;
	case 4:
	{
		clearBoard();
		resetSnakePos();
		qm->resetNumberArrSize();
		qm->getQuestionFromArr(qm->getCurrQuestion())->set();
		qm->getQuestionFromArr(qm->getCurrQuestion())->print();
		checkDeadCreature();
		restCreatuersPos();
		removeAllBulletsFromBoard();
		printBoard();
		for (int i = 0; i < 2; i++)
		{
			s[i]->resetBulletCounter();
			s[i]->move();
		}
	}
	break;
	case 5:
	{
		clearBoard();
		qm->setCurrQuestion(rand() % NUMQUEST);
		resetSnakePos();
		qm->resetNumberArrSize();
		qm->getQuestionFromArr(qm->getCurrQuestion())->randNum();
		qm->getQuestionFromArr(qm->getCurrQuestion())->set();
		qm->getQuestionFromArr(qm->getCurrQuestion())->print();
		checkDeadCreature();
		restCreatuersPos();
		removeAllBulletsFromBoard();
		printBoard();
		for (int i = 0; i < 2; i++)
		{
			s[i]->resetBulletCounter();
			s[i]->move();
		}
	}
	break;
	}
	gotoxy(0, 0);

}


int TheSnakesGame::randNum()
{

	int num;

	int range = rand() % 3;
	switch (range)
	{
	case 0:
	{
		num = rand() % 26;
		break;
	}
	case 1:
	{
		num = 27 + (rand() % 55);
		break;
	}
	default:
	{
		num = (rand() % 87) + 83;
		break;
	}
	}
	return num;
}

NUMBER TheSnakesGame::checkNum(int x, int y)
{
	while (board[y][x] <= '9' && board[y][x] >= '0')
	{
		x--;
	}
	x++;
	return (qm->getNum(x, y));
}

int TheSnakesGame::countDigits(int num)
{
	int res = 1;
	while (num >= 10)
	{
		num = num / 10;
		res++;
	}
	return res;
}

void TheSnakesGame::clearLines(const int& line)
{
	for (int i = 0; i < COLS; i++)
	{
		gotoxy(i, line);
		board[line][i] = ' ';
		cout << " ";
	}
}

void TheSnakesGame::clearBoard() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i + 3][j] = ' ';
		}
	}
}

void TheSnakesGame::printBoard()
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			gotoxy(j, i + 3);
			cout << board[i + 3][j];
		}
		cout << endl;
	}
}

void TheSnakesGame::clearnNumberFromBoard(const NUMBER& num)
{
	int currX = num.position.getX();
	for (int i = 0; i<num.size; i++)
	{
		updateBoard(currX, num.position.getY(), ' ');
		gotoxy(currX, num.position.getY());
		cout << ' ';
		currX++;
	}
}


void TheSnakesGame::printScoreAndBullets()
{
	setTextColor(s[0]->getColor());
	gotoxy(0, 2);
	cout << "  Score: " << s[0]->getScore() << "  Bullets:  " << s[0]->getNumOfBullets();
	setTextColor(s[1]->getColor());
	cout << "                                 Score: " << s[1]->getScore() << "  Bullets:  " << s[1]->getNumOfBullets();
}

void TheSnakesGame::removeHalfOfNumbersFromArrAndBoard()
{
	int logicSizeOfArr = (qm->getNumbersArrSize())/ 2;

	for (int i = 0; i < logicSizeOfArr; i++)
	{
		int randIndex = rand() % (qm->getNumbersArrSize() - 1);
		NUMBER removeNum = qm->getNumByIndex(randIndex);
		if ((removeNum.position.getX() == qm->getClosestNum().position.getX()) && (removeNum.position.getY() == qm->getClosestNum().position.getY()))
			qm->setEatenClosestNum(true);
		updateBoard(removeNum.position.getX(), removeNum.position.getY(), ' ');
		gotoxy(removeNum.position.getX(), removeNum.position.getY());
		clearnNumberFromBoard(removeNum);
		qm->removeNumberFromArr(removeNum);

	}
}


bool TheSnakesGame::checkAndMarkCorrectAnswers(const Color& color)
{
	bool res = false;

	for (int i = 0; i < qm->getNumbersArrSize(); i++) // going through the nubmers array 
	{
		NUMBER numFromArr = qm->getNumByIndex(i);
		bool isCorrect;
		qm->getQuestionFromArr(qm->getCurrQuestion())->isCorrect(numFromArr.value, isCorrect);
		if (isCorrect)
		{
			res = true;
			setTextColor(color);
			int currNum = numFromArr.value;
			for (int i = numFromArr.size - 1; i >= 0; i--)
			{
				gotoxy(numFromArr.position.getX() + i, numFromArr.position.getY());
				cout << currNum % 10;
				currNum = currNum / 10;
			}
		}
	}
	return res;
}

void TheSnakesGame::noOneFoundAnswer()
{
	clearLines(1);
	setTextColor(LIGHTRED);
	gotoxy(0, 1);
	cout << "		    OOPS! YOU DIDN'T FIND THE RIGHT ANSWERS!";
	PlaySound(TEXT("fail.wav"), NULL, SND_ASYNC);

	Sleep(3000);
	clearLines(1);

	if (checkAndMarkCorrectAnswers(LIGHTRED))
	{
		gotoxy(0, 1);
		cout << "                      HERE ARE THE CORRECT ANSWERS: ";
		Sleep(500);
	}

	else
	{
		gotoxy(0, 1);
		cout << "                      THERE WERE NO CORRECT ANSWERS! ";
	}

	Sleep(800);
	checkAndMarkCorrectAnswers(WHITE);
	clearLines(1);
	removeHalfOfNumbersFromArrAndBoard();

	//prints a random question
	clearLines(0);
	qm->setCurrQuestion(rand() % NUMQUEST);
	qm->getQuestionFromArr(qm->getCurrQuestion())->randNum();
	qm->getQuestionFromArr(qm->getCurrQuestion())->set();
	qm->getQuestionFromArr(qm->getCurrQuestion())->print();

	isSnakeStuck();
	checkDeadCreature();
}

bool TheSnakesGame::isWinner(const int& score, const int& snakeNum)
{
	setTextColor(LIGHTRED);
	if (score == HIGHSCORE)
	{
		system("cls");
		gotoxy(29, 10);
		if (snakeNum == 0)
			cout << "SNAKE 1 (@) IS THE WINNER!!!";
		else
			cout << "SNAKE 2 (#) IS THE WINNER!!!";
		PlaySound(TEXT("YouWinNew.wav"), NULL, SND_ASYNC);
		Sleep(1500);
		PlaySound(TEXT("Winner.wav"), NULL, SND_ASYNC);
		Sleep(3000);
		setTextColor(BLACK);
		gotoxy(0, 0);
		return true;
	}
	else
		return false;
}

void TheSnakesGame::startGame()
{
	removeAllBulletsFromBoard();
	s[0]->setSize(3);
	s[1]->setSize(3);
	resetSnakePos();
	s[0]->resetScore();
	s[1]->resetScore();
	if (qm->getNumbersArrSize() > 0) {
		qm->resetNumberArrSize();
	}
	
}

void TheSnakesGame::resetSnakePos()
{
	s[0]->setPosition(10, 9);
	s[1]->setPosition(70, 9);
	s[0]->setDirection(0); // in case the snake's direction is left ( we can't move right )
	s[0]->setDirection(3);
	s[1]->setDirection(0); // in case the snake's direction is right ( we can't move left )
	s[1]->setDirection(2);
}

void TheSnakesGame::soundEffect(const bool& correct)
{
	if (correct)
	{
		int randSound = rand() % 4;
		switch (randSound)
		{
		case 0:
			PlaySound(TEXT("RightAnswer.wav"), NULL, SND_ASYNC);
			break;
		case 1:
			PlaySound(TEXT("Wow.wav"), NULL, SND_ASYNC);
			break;
		case 2:
			PlaySound(TEXT("GOODJOB.wav"), NULL, SND_ASYNC);

			break;
		default:
			PlaySound(TEXT("Great.wav"), NULL, SND_ASYNC);
			break;
		}
	}
	else
	{
		int randSound = rand() % 3;
		switch (randSound)
		{
		case 0:
			PlaySound(TEXT("oops.wav"), NULL, SND_ASYNC);
			break;
		case 1:
			PlaySound(TEXT("nopeNew.wav"), NULL, SND_ASYNC);

			break;
		default:
			PlaySound(TEXT("REALLY.wav"), NULL, SND_ASYNC);
			break;
		}

	}
}


bool TheSnakesGame::worngAnswerAndAWin(const int& i)
{
	if (i == 0)
	{
		s[1]->grow();
		s[1]->setScore();
		if (isWinner(s[1]->getScore(), 1))
			return false;
		else
			return true;
	}
	else
	{
		s[0]->grow();
		s[0]->setScore();
		if (isWinner(s[0]->getScore(), 0))
			return false;
		else
			return true;
	}
}

void TheSnakesGame::stepCounter(const int& count, NUMBER num, SnakeDisappear disappear[2], Creature *eater, int&dir1, int&dir2)
{
	bool isCorrect;
	bool isValid;
	int x, y;
	bool newNumOnScreen = false;

	if (count % STEPS == 0) //prints random numbers to the screen
	{
		for (int i = 0; i < 2; i++)
		{
			if (disappear[i].isDisappear && ((disappear[i].timer % STEPS) == 0) && (disappear[i].timer != 0))
			{
				s[i]->AppearSnake(s0LD,s1LD);
				disappear[i].isDisappear = false;
				disappear[i].timer = 0;
			}

			if (disappear[i].isDisappear)
				disappear[i].timer++;
		}
		
		if (!replay)
		{
			num.value = randNum();
			int numDigits = countDigits(num.value);
			num.size = numDigits;
			do {
				x = rand() % (COLS + 1);
				y = 3 + (rand() % ROWS);
				isValid = checkPlace(x, y, num.size);
			} while (isValid == false);
			num.position.set(x, y);

		}
		else
		{
			num = numbers[newNumbersIndex].num;
			newNumbersIndex++;
		}

		int numCopy = num.value;

		for (int i = num.size - 1; i >= 0; i--)//updates the board with the number
		{
			updateBoard(num.position.getX()+ i, num.position.getY(), (numCopy % 10) + '0');
			numCopy = numCopy / 10;
		}

		bool isFull = qm->insertNum(num);
		if (isFull)
			noOneFoundAnswer();
		else
		{
			newNumOnScreen = true;
			if (!replay)
			{
				replayNum.enterNum = 1;
				replayNum.num = num;
				numbers.push_back(replayNum);
			}
		}
	}

	if (qm->isNumberOnScreen())
	{
		if (!qm->getisEatenClosestNum()) //no one ate the closest num
		{
			if (newNumOnScreen)
			{
				qm->getQuestionFromArr(qm->getCurrQuestion())->isCorrect(num.value, isCorrect);
				if (isCorrect)
				{
					bool res;
					eater->isFastWay(num, dir1, dir2, res);
					if (res) // the new number is the closest number to the numEater 
					{
						qm->setClosestNum(num);
						qm->setEatenClosestNum(false);
						goToClosestNum(dir1, dir2, eater);
					}
					else // the new num is not the closest, it will keep moving to the last closest num
					{
						bool res;
						qm->getQuestionFromArr(qm->getCurrQuestion())->isCorrect(qm->getClosestNum().value, res);
						if (res) // checks if the curr closest num is correct answer
						{
							goToClosestNum(dir1, dir2, eater);
						}

						else // the curr closest num is not a correct answer
						{
							searchNewClosestNum(dir1, dir2, eater);
						}
					}
				}
				else // if no one ate the closest num and there is no new num on screen
				{
					bool res;
					qm->getQuestionFromArr(qm->getCurrQuestion())->isCorrect(qm->getClosestNum().value, res);
					if (res) // check if the curr closest num is correct answer
						goToClosestNum(dir1, dir2, eater);
					else
						searchNewClosestNum(dir1, dir2, eater);
				}
			}
			else // if there is no new num on screen 
			{
				bool res;
				qm->getQuestionFromArr(qm->getCurrQuestion())->isCorrect(qm->getClosestNum().value, res);
				if (res) // check if the curr closest num is correct answer
					goToClosestNum(dir1, dir2, eater);
				else
					searchNewClosestNum(dir1, dir2, eater);
			}
		}

		else // someone ate the closest num
		{
			searchNewClosestNum(dir1, dir2, eater);
		}
	}
}



void TheSnakesGame::snakeOnSnakeCheck(SnakeDisappear missingSanke[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (!missingSanke[i].isDisappear) // if the snake didn't disapper
		{
			Point next = s[i]->getPos().next(s[i]->getDir());
			if ((!(isSnake(Point(next.getX(), next.getY()))))) // if the snake's next poing isn't a snake
				if(!isCreature(next))
					s[i]->move();
		}
	}
}

int TheSnakesGame::whoIsShooting(const char& key)
{
	if (key == 'z')
		return 0;
	else if (key == 'n')
		return 1;
	else
		return (-1);
}


Point TheSnakesGame::getNextPointBullet(Node* curr)
{
	switch (curr->bullet.getBulletDir())
	{
	case 0: // up
	{
		int newY = (curr->bullet.getBulletY()) - 1;
		if (newY < 3)
			newY = 23;
		return (Point(curr->bullet.getBulletX(), newY));
	}
	break;
	case 1:  // down 
	{
		int newY = (curr->bullet.getBulletY()) + 1;
		if (newY > 23)
			newY = 3;
		return (Point(curr->bullet.getBulletX(), newY));
	}
	break;
	case 2: // left
	{
		int newX = (curr->bullet.getBulletX()) - 1;
		if (newX < 0)
			newX = 79;
		return (Point(newX, curr->bullet.getBulletY()));
	}
	break;
	default:  // right 
	{
		int newX = (curr->bullet.getBulletX()) + 1;
		if (newX > 79)
			newX = 0;
		return (Point(newX, curr->bullet.getBulletY()));
	}
	break;
	}
}

Point TheSnakesGame::getBulletBornPos(const int& dir, const int& i)
{
	switch (dir)
	{
	case 0: // up
	{
		int newY = (s[i]->getPos().getY()) - 1;
		if (newY < 3)
			newY = 23;
		return (Point(s[i]->getPos().getX(), newY));
	}
	break;
	case 1: // down
	{
		int newY = (s[i]->getPos().getY()) + 1;
		if (newY > 23)
			newY = 3;
		return (Point(s[i]->getPos().getX(), newY));
	}
	break;
	case 2: // left
	{
		int newX = (s[i]->getPos().getX()) - 1;
		if (newX < 0)
			newX = 79;
		return (Point(newX, s[i]->getPos().getY()));
	}
	break;
	default: //right
	{
		int newX = (s[i]->getPos().getX()) + 1;
		if (newX > 79)
			newX = 0;
		return (Point(newX, s[i]->getPos().getY()));
	}
	break;
	}
}

int TheSnakesGame::checkShotHit(const Point& p, Node* curr, const int& i)
{
	if (board[p.getY()][p.getX()] == ' ' || board[p.getY()][p.getX()] == '*')
	{
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');
		gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
		cout << ' ';
		curr->bullet.moveBullet(p);
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), curr->bullet.getBulletFigure());
		return 1;
	}

	else if (board[p.getY()][p.getX()] == '$' || board[p.getY()][p.getX()] == '%')
	{
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');
		gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
		cout << ' ';
		s[i]->winBullet();
		/*gotoxy(p.getX(), p.getY());
		cout << " ";*/
		// delete the creature
		for (int i = 0; i < 5; i++)
		{
			if (cArr[i]->getX() == p.getX() && cArr[i]->getY() == p.getY())
			{
				cArr[i]->setIsDead(true);
				cArr[i]->deleteCreature();
			}
		}
		updateBoard(p.getX(), p.getY(), ' ');
		return 4;

	}

	else if (board[p.getY()][p.getX()] == '!')
	{
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');
		gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
		cout << ' ';
		return 4;

	}
	else if (isNum(p))
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_ASYNC);
		NUMBER numHitByBullet = checkNum(p.getX(), p.getY());
		clearnNumberFromBoard(numHitByBullet);
		qm->removeNumberFromArr(numHitByBullet);
		if(qm->getClosestNum().position.getX() == numHitByBullet.position.getX() && qm->getClosestNum().position.getY() == numHitByBullet.position.getY())
			qm->setEatenClosestNum(false);
		gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
		cout << ' ';
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');
		return 0;
	}
	else if (whichSnake(p) == i) // the snake shot itself
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_ASYNC);
		s[i]->deleteSnake();
		gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
		cout << ' ';
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');
		return 3;
	}
	else if (whichSnake(p) != i)				    // the snake shot the other snake
	{
		PlaySound(TEXT("hit.wav"), NULL, SND_ASYNC);
		s[(i + 1) % 2]->deleteSnake();
		gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
		cout << ' ';
		updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');

		s[i]->winBullet();
		return 2;
	}
}

int TheSnakesGame::whichSnake(const Point& p)
{
	if (board[p.getY()][p.getX()] == s[0]->getFigure())
		return 0;
	else
		return 1;
}

void TheSnakesGame::removeAllBulletsFromBoard()
{
	Node* curr;

	for (int i = 0; i < 2; i++)
	{
		curr = s[i]->getList()->getHead();

		while (curr != NULL)
		{
			updateBoard(curr->bullet.getBulletX(), curr->bullet.getBulletY(), ' ');
			gotoxy(curr->bullet.getBulletX(), curr->bullet.getBulletY());
			cout << ' ';
			curr = s[i]->getList()->removeNodeFromList(curr);
		}
		s[i]->getList()->makeEmpty();
	}
}

void TheSnakesGame::landOnNum(const int& x, const int& y, const int& dir, const char&  figure)
{
	Point p;
	p.set(x, y);
	int i;

	if (figure == '@')
		i = 0;
	else if(figure == '#')
		i = 1;

	if (figure == '#' || figure == '@')
	{
		for (int j = 0; j < s[i]->getSize(); j++)
		{
			if (isNum(Point(p.getX(), p.getY())))
			{
				NUMBER numToRemove = checkNum(p.getX(), p.getY());
				clearnNumberFromBoard(numToRemove);
				qm->removeNumberFromArr(numToRemove);
			}
			p.move(dir);
		}
	}

	else // if rest creature pos fall on numbers 
	{
		if (isNum(Point(p.getX(), p.getY())))
		{
			NUMBER numToRemove = checkNum(p.getX(), p.getY());
			clearnNumberFromBoard(numToRemove);
			qm->removeNumberFromArr(numToRemove);
		}
	}
}

void TheSnakesGame::isSnakeStuck()
{
	char ch1 = s[0]->getFigure();
	char ch2 = s[1]->getFigure();

	for (int i = 0; i < 2; i++)
	{
		int x, y;
		
		// The point of the snake's head 
		x = s[i]->getPos().getX();
		y = s[i]->getPos().getY();

		// check if the snake srounded by his or the other snake's body
		if ((board[y][x + 1] == ch1 || board[y][x + 1] == ch2) && (board[y][x - 1] == ch1 || board[y][x - 1] == ch2 )&& (board[y + 1][x] == ch1 || board[y + 1][x] == ch2) && (board[y - 1][x] == ch1 || board[y - 1][x] == ch2))
		{
			s[i]->deleteSnake();
			s[i]->move();
		}
	}
}

void TheSnakesGame::snakeShotABullet(const int& snakeShoot, const int& i, int shootNum[2], SnakeDisappear isSnakeDissaper[2])
{
	if (snakeShoot == i)
	{
		if ((s[i]->getNumOfBullets() > 0)&&(isSnakeDissaper[i].isDisappear == false)) // if the snake has any bullets to shoot 
		{
			PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC);
			shootNum[i]++;
			Point bulletPos = getBulletBornPos(s[i]->getDir(), i);
			Bullet snakeShot(bulletPos.getX(), bulletPos.getY(), s[i]->getColor(), i, s[i]->getDir(), shootNum[i]);
			Node* NewNode = s[i]->getList()->creatNewNode(snakeShot, NULL);
			s[i]->getList()->insertNodeToTail(NewNode);
			s[i]->loseBullet();

			// check where the bullet will be born and if it's going to hit something
			int bornHit = checkShotHit(bulletPos, NewNode, i);
			if (bornHit != 1)
			{
				if (bornHit == 2)
					isSnakeDissaper[(i + 1) % 2].isDisappear = true;
				else if (bornHit == 3)
					isSnakeDissaper[i].isDisappear = true;

				s[i]->getList()->removeNodeFromList(NewNode->bullet.getShotNum());
			}
		}
	}

	// going over the snake's list, moving the bullets and checking where they hit
	if (!(s[i]->getList()->isEmpty()))
	{
		Node* curr = s[i]->getList()->getHead();
		while ((curr != NULL))
		{
			Point nextPointOfBullet1 = getNextPointBullet(curr);

			int hit = checkShotHit(nextPointOfBullet1, curr, i);
			if (hit == 1)
			{
				Point nextPointOfBullet2 = getNextPointBullet(curr);
				int nexthit = checkShotHit(nextPointOfBullet2, curr, i);
				// next point of bullet is ' ' or '*'
				if (nexthit == 1)
					curr = curr->next;
				else
				{
					// the snake shot the other snake
					if (nexthit == 2)
						isSnakeDissaper[(i + 1) % 2].isDisappear = true;

					// the snake shot itself
					else if (nexthit == 3)
						isSnakeDissaper[i].isDisappear = true;
					curr = s[i]->getList()->removeNodeFromList(curr->bullet.getShotNum());
				}
			}
			else
			{
				// the snake shot the other snake
				if (hit == 2)
					isSnakeDissaper[(i + 1) % 2].isDisappear = true;

				// the snake shot itself
				else if (hit == 3)
					isSnakeDissaper[i].isDisappear = true;
				curr = s[i]->getList()->removeNodeFromList(curr->bullet.getShotNum());
			}
		}
	}
}

int TheSnakesGame::creatCreature(Creature ***cArr)
{
	Creature **temp;
	int size = 5;
	temp = new Creature*[size];

	temp[0] = new NumEater(10, 19, '%', GREEN, -1, 2, false, false, ROWS*COLS, this);
	temp[1] = new RowsFlyer(30, 23, '!', LIGHTRED, 3, 2, false, false);
	temp[2] = new RowsFlyer(50, 15, '!', LIGHTRED, 2, 2,true, false);
	temp[3] = new ColsFlyer(45, 23, '$', LIGHTCYAN, 0, 1, true, false);
	temp[4] = new ColsFlyer(55, 15, '$', LIGHTCYAN, 1, 1,false, false);

	*cArr = temp;
	return size;
}

void TheSnakesGame::moveCreature(Creature *pc, SnakeDisappear isSnakeDissaper[2])
{
		updateBoard(pc->getX(), pc->getY(), ' ');
		gotoxy(pc->getX(), pc->getY());
		cout << " ";
	
		pc->move(pc->getDir());
		Point next = Point(pc->getX(), pc->getY());

	if (isNum(next))
	{
		NUMBER numHitByCreature = checkNum(pc->getX(), pc->getY());
		clearnNumberFromBoard(numHitByCreature);
		qm->removeNumberFromArr(numHitByCreature);

	}
	else if (isSnake(next))
	{
		int snakeNum = whichSnake(next);
		s[snakeNum]->deleteSnake();
		isSnakeDissaper[snakeNum].isDisappear = true;
	}

	else if (isBullet(next))
	{
		bool found = false;
		updateBoard(next.getX(), next.getY(), ' ');
		gotoxy(next.getX(), next.getY());
		cout << " ";
		for (int i = 0; !found, i < 2; i++)
		{
			Node* curr = s[i]->getList()->getHead();
			while (!found && curr != NULL)
			{
				if (curr->bullet.getBulletX() == next.getX() && curr->bullet.getBulletY() == next.getY())
				{
					found = true;
					curr = s[i]->getList()->removeNodeFromList(curr->bullet.getShotNum());
				}
				else
					curr = curr->next;
			}
		}
	}

	pc->draw();
	updateBoard(pc->getX(), pc->getY(), pc->getFigure());

}

bool TheSnakesGame:: isCreature(Point p)
{
	for(int i = 0; i<5; i++)
	{
		if (board[p.getY()][p.getX()] == cArr[i]->getFigure())
		{
			return true;
		}
	}
	return false;
}

int TheSnakesGame::whichCreature(Point p)
{
	if (board[p.getY()][p.getX()] == '%')
		return 0;
	return 1;
}

bool TheSnakesGame::isBullet(Point p)
{
	if (board[p.getY()][p.getX()] == '*')
		return true;
	return false;
}

void TheSnakesGame::snakeTouchedNumEater(int i, qManager *q)
{
	setTextColor(LIGHTRED);
	gotoxy(0, 1);
	cout << "		           OH NO! SNAKE " << i + 1 << " EATEN BY THE NUMEATER!! ";
	soundEffect(false);
	Sleep(2000);
	clearLines(1);

	s[(i + 1) % 2]->setScore();
	s[(i + 1) % 2]->grow();
	isWinner(s[(i + 1) % 2]->getScore(), i);

	s[i]->deleteSnake();
	s[i]->AppearSnake(s0LD, s1LD);

	removeHalfOfNumbersFromArrAndBoard();
	removeAllBulletsFromBoard();
	restCreatuersPos();
	clearLines(0);

	// rest replay data and save all the begining data on screen 
	restAllReplayData();
	saveBeginingSnakeData();
	saveCurrNumbersOnScreen();
	restCreatuersPos();

	qm->setCurrQuestion(rand() % NUMQUEST);
	qm->getQuestionFromArr(qm->getCurrQuestion())->randNum();
	qm->getQuestionFromArr(qm->getCurrQuestion())->set();
	qm->getQuestionFromArr(qm->getCurrQuestion())->print();
	checkDeadCreature();
	isSnakeStuck();
}

int TheSnakesGame::SwitchDir(int dir)
{
	switch (dir)
	{
	case 0:
		return 1;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 3;
		break;
	case 3:
		return 2;
		break;
	}
}

bool TheSnakesGame::checkEqEatenNumAndClosestNum(NUMBER resNum, NUMBER ClosestNum)
{
	if (resNum.position.getX() == ClosestNum.position.getX())
		if (resNum.position.getY() == ClosestNum.position.getX())
			return true;

	return false;			
}

void TheSnakesGame::goToClosestNum(int &dir1, int &dir2,Creature* eater)
{
	if (qm->getClosestNum().position.getY() != eater->getY())
	{
		eater->setDir(dir1);
		eater->moveAndCheckWay(qm, qm->getClosestNum(), s);
		if (qm->getClosestNum().position.getY() != eater->getY())
			eater->moveAndCheckWay(qm, qm->getClosestNum(), s);
		else
		{
			if (qm->getClosestNum().position.getX() != eater->getX())
			{
				eater->setDir(dir2);
				eater->moveAndCheckWay(qm, qm->getClosestNum(), s);
			}
		}
	}
	else
	{
		if (qm->getClosestNum().position.getX() != eater->getX())
		{
			eater->setDir(dir2);
			eater->moveAndCheckWay(qm, qm->getClosestNum(), s);
			if (qm->getClosestNum().position.getX() != eater->getX())
				eater->moveAndCheckWay(qm, qm->getClosestNum(), s);
		}
	}
}

void TheSnakesGame::searchNewClosestNum(int &dir1, int &dir2, Creature* eater)
{
	bool res;
	eater->restSteps();
	bool correctAnswerFound = false;
	NUMBER* arr = qm->getArr();
	int size = qm->getNumbersArrSize();
	for (int i = 0; i < size; i++)
	{
		qm->isCorrect(arr[i].value, res);
		if (res)
		{
			correctAnswerFound = true;
			bool res;
			eater->isFastWay(arr[i], dir1, dir2, res);
			if (res)
			{
				qm->setClosestNum(arr[i]);
				qm->setEatenClosestNum(false);
			}
		}
	}
	if (correctAnswerFound)
	{
		goToClosestNum(dir1, dir2, eater);
	}
}

void TheSnakesGame::checkDeadCreature()
{
	for (int i = 0; i < 5; i++)
	{
		if (cArr[i]->is_Dead())
		{
			cArr[i]->setIsDead(false);
		}
	}
}

void TheSnakesGame::saveBeginingSnakeData()
{
	for (int i = 0; i < 2; i++)
	{
		snakeData[i].p = s[i]->getPos();
		snakeData[i].dir = s[i]->getDir();
		snakeData[i].score = s[i]->getScore();
		snakeData[i].size = s[i]->getSize();
	}
}

void TheSnakesGame::saveCurrNumbersOnScreen()
{
	int arrSize = qm->getNumbersArrSize();
	NUMBER * arr = qm->getArr();

	for (int i = 0; i < arrSize; i++)
	{
		replayNum.enterNum = 0;
		replayNum.num = arr[i];
		numbers.push_back(replayNum);
	}
}

void TheSnakesGame::restAllReplayData()
{
	keys.clear();
	timer.clear();
	s0LD.clear();
	s1LD.clear();
	numbers.clear();

	newNumbersIndex = 0;
	s0Index = 0;
	s1Index = 0;
	timerIndex = 0;
	replayTimer = 0;
}


void TheSnakesGame::replayRun()
{
	int count = 0;
	int replayCounter = count; // will hold the timer for replay 
	char key = 2;
	int dir;
	int snakeShoot = -1;
	int shootNum[2] = { 0 };
	SnakeDisappear isSnakeDissaper[2];
	bool isCorrect;
	int dir1, dir2;
	timerIndex = 0;

	// clear the screen and board 
	system("cls");
	removeAllBulletsFromBoard();
	clearBoard();
	restCreatuersPos();

	// print the question
	gotoxy(0, 0);
	qm->getQuestionFromArr(qm->getCurrQuestion())->set();
	qm->getQuestionFromArr(qm->getCurrQuestion())->print();

	// print the numbers on screen at the begining of the replay 
	setTextColor(WHITE);
	printNumbersOnScreen();

	// resotre the data of the sankes +  rest the bullet counter + rest creatures pos
	restoreSnakeData();

	NUMBER num;
	do {
		printScoreAndBullets();
		replayCounter = count;
		if (replayCounter == timer[timerIndex])
		{
			key = keys[timerIndex];
			timerIndex++;
			if (key == ESC)
				continue;
		}

		for (int i = 0; i < 5; i++)
		{
			cArr[i]->draw();
			updateBoard(cArr[i]->getX(), cArr[i]->getY(), cArr[i]->getFigure());

			if (i != 0) // not a numEater
			{
				if (!(cArr[i]->is_Dead()))
				{
					moveCreature(cArr[i], isSnakeDissaper);
					if (cArr[i]->getSpeed() == 2)
						moveCreature(cArr[i], isSnakeDissaper);
				}
			}
		}

		snakeOnSnakeCheck(isSnakeDissaper);

		for (int i = 0; i < 2; i++)
		{
			snakeShoot = whoIsShooting(key);
			snakeShotABullet(snakeShoot, i, shootNum, isSnakeDissaper);

			if ((dir = s[i]->getDirection(key)) != -1) {
				if (s[i]->validDirection(dir))
					s[i]->setDirection(dir);
			}

			Point next = s[i]->getPos().next(s[i]->getDir());

			if (isCreature(next))
			{
				int creatureType = whichCreature(next);
				if (creatureType != 0) // the creature is colsflyer or rowsflyer
				{
					isSnakeDissaper[i].isDisappear = true;
					s[i]->deleteSnake();
				}
			}
		}

		count++;
		stepCounter(count, num, isSnakeDissaper, cArr[0], dir1, dir2);

		if (key != ESC)
			key = -1;
		Sleep(100);
	} while (key != ESC);

	qm->setEatenClosestNum(true);
	clearLines(0);
}

void TheSnakesGame::printNumbersOnScreen()
{
	newNumbersIndex = 0;
	bool stop = false; // will be true if there were no more numbers on screen at the begining
	qm->resetNumberArrSize(); // rest the numbers arr 

	for (int i = 0; (!stop) && (i < numbers.size()); i++)
	{
		if (numbers[i].enterNum == 0)
		{
			qm->insertNum(numbers[i].num);
			int x, y;
			x = numbers[i].num.position.getX();
			y = numbers[i].num.position.getY();

			//updates the board with the number
			int numCopy = numbers[i].num.value;
			for (int j = numbers[i].num.size - 1; j >= 0; j--)
			{
				updateBoard(x + j, y, (numCopy % 10) + '0');
				numCopy = numCopy / 10;
			}

			gotoxy(x, y);
			cout << numbers[i].num.value;
			newNumbersIndex++;
		}
		else
			stop = true;
	}
}

void TheSnakesGame::restoreSnakeData()
{
	for (int i = 0; i < 2; i++)
	{
		s[i]->setPosition(snakeData[i].p.getX(), snakeData[i].p.getY());
		s[i]->setDirection(snakeData[i].dir);
		s[i]->setReplayScore(snakeData[i].score);
		s[i]->setSize(snakeData[i].size);
		s[i]->resetBulletCounter();
		s[i]->resetBulletCounter();
	}
}

void TheSnakesGame::restCreatuersPos()
{
	qm->setEatenClosestNum(true);

	for (int i = 0; i < 5; i++)
	{
		updateBoard(cArr[i]->getX(), cArr[i]->getY(), ' ');
		gotoxy(cArr[i]->getX(), cArr[i]->getY());
		cout << ' ';

		switch (i) {
		case 0:
			cArr[i]->setPoint(10, 19);
			cArr[i]->setDir(-1);
			break;
		case 1:
			cArr[i]->setPoint(30, 23);
			cArr[i]->setDir(3);
			break;
		case 2:
			cArr[i]->setPoint(50, 15);
			cArr[i]->setDir(2);
			break;
		case 3:
			cArr[i]->setPoint(45, 23);
			cArr[i]->setDir(0);
			break;
		case 4:
			cArr[i]->setPoint(55, 15);
			cArr[i]->setDir(1);
			break;
		}

		landOnNum(cArr[i]->getX(), cArr[i]->getY(), cArr[i]->getDir(), cArr[i]->getFigure());
	}
}
