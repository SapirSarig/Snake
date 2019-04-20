#ifndef __DIVIDESBYX_H_
#define __DIVIDESBYX_H_
#include "Questions.h"

class dividesByX : public Questions {

	int x;
public:
	virtual void print();
	virtual void isCorrect(int num,bool &res);
	virtual void randNum();

	


};

#endif