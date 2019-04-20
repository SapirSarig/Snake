#ifndef __SUMDIGITS_H_
#define __SUMDIGITS_H_
#include "Questions.h"

class sumDigits : public Questions {

	int x;

public:
	virtual void print();
	virtual void isCorrect(int num, bool &res);
	virtual void randNum();



};

#endif