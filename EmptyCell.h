#ifndef __EMPTYCELL_H
#define __EMPTYCELL_H
#include "Cell.h"

class EmptyCell :public Cell
{
	int value;
public:
	void setValue();
	virtual double getValue();
	virtual void printCell();
	EmptyCell();
};

#endif