#ifndef __INTEGERCELL_H
#define __INTEGERCELL_H
#include "Cell.h"

class IntegerCell :public Cell
{
	int value;
//	char * printValue;
public:
	IntegerCell():Cell() {value = 0;};
	IntegerCell(char * c);
	void setValue();
	virtual double getValue();
	/*void setPrintValue();
	virtual char * getPrintValue() const;*/
	virtual void printCell();
};

#endif