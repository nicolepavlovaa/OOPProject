#ifndef __DOUBLE_CELL
#define __DOUBLE_CELL
#include "Cell.h"

class DoubleCell : public Cell
{
	double value;
	
public:
	DoubleCell();
	DoubleCell(char * cont);
	void setValue();
	virtual double getValue();
	virtual void printCell();
};
#endif
