#ifndef _QUESTIONS_H_
#define _QUESTIONS_H_

#include "Point.h"
#include <string.h>


class Questions 
{
	string text;
	int Brange;
	int Trange;
	int index; //type of question
	int currQuestion;


public:


	virtual void print() = 0;
	virtual void isCorrect(int num,bool &res) = 0;
	virtual void randNum() = 0;

	int getTrange() { return Trange; }
	int getBrange() { return Brange; }
	int getIndex() { return index; }
	string getText() { return text; }
	void set();

	void setTrange(int _Trange) 
	{
		 Trange = _Trange;
	
	}
	void setBrange(int _Brange)
	{
		Brange = _Brange;

	}
	void setIndex(int _index)
	{
		index = _index;

	}
	void setText(char* str)
	{
		text = _strdup(str);
	}
	void setCurrQuestion(int i)
	{
		currQuestion = i;
	}
	int getCurrQuestion()
	{
		return currQuestion;
	}


};

#endif