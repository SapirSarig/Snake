#ifndef __QMANAGER_H_
#define __QMANAGER_H_

#include "Questions.h"
#include <string.h>
#include "dividesByX.h"
#include "inRange.h"
#include "Equation.h"
#include "sumDigits.h"
#include "dividesByAnotB.h"

typedef struct Number {
	int size = 0;
	int value;
	Point position;
}NUMBER;

class qManager {

	int currQuestion;
	int qArrSize, numbersSize;
	Questions** qArr;
	NUMBER numbers[60];
	bool numberOnScreen = false;
	NUMBER ClosestNum;
	bool isEatenClosestNum = true;

public:
	qManager()
	{
		createQuestionsArr(&qArr, qArrSize);
	}
	void setCurrQuestion(int i) {
		currQuestion = i;
	}
	int getCurrQuestion() {
		return currQuestion;
	}
	void print(int index)
	{
		qArr[index]->print();
	}
	void isCorrect(int num, bool& res)
	{
		qArr[currQuestion]->isCorrect(num,res);
	}
	void createQuestionsArr(Questions*** qArr, int& size);
	Questions* getQuestionFromArr(int index)
	{
		return qArr[index];
	}
	void resetNumberArrSize() {
		numbersSize = 0;
	}
	void removeNumberFromArr(NUMBER num);
	NUMBER getNum(int x, int y); // get's a point and return the full number
	int getNumbersArrSize() {
		return numbersSize;
	}
	int getqArrSize() {
		return qArrSize;
	}
	NUMBER getNumByIndex(int index);
	bool insertNum(NUMBER num);
	bool isNumberOnScreen() 
	{
		if (numbersSize > 0) 
			return true;
		else 
			return false; 
	}
	bool getisEatenClosestNum() { return isEatenClosestNum; }
	void setClosestNum(NUMBER num) { ClosestNum = num; }
	void setEatenClosestNum(bool eaten) { isEatenClosestNum = eaten; }
	NUMBER getClosestNum() { return ClosestNum; } 
	NUMBER *getArr() { return numbers;}
};


#endif