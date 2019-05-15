#ifndef __STRINGCELL_H
#define __STRINGCELL_H
#include "Cell.h"

class StringCell :public Cell
{
	double value;
	char * printValue;

public:
	void setValue();
	void setPrintValue();
	virtual double getValue();
	virtual void printCell();
	StringCell();
	StringCell(char * cont);
	~StringCell();
};

#endif
