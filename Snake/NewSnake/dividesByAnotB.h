#ifndef __DIVIDESBYANOTB_H_
#define __DIVIDESBYANOTB_H_
#include "Questions.h"

class dividesByAnotB : public Questions {

	int A;
	int B;

public:
	virtual void print();
	virtual void isCorrect(int num, bool &res);
	virtual void randNum();
	


};

#endif
