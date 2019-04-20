#ifndef __INRANGE_H_
#define __INRANGE_H_
#include "Questions.h"

class inRange : public Questions {

	int x;
public:
	virtual void print();
	virtual void isCorrect(int num, bool &res);
	virtual void randNum();

};

#endif
