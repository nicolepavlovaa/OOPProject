#include "IntegerCell.h"

void IntegerCell::setValue()
{
	this->value = atoi(getCellContent());
}
double IntegerCell::getValue()
{
	return (double)this->value;
}
IntegerCell::IntegerCell(char * c) :Cell(c)
{
	setType(TYPE_INT);
	setValue();
}
void IntegerCell::printCell()
{
	cout << value;
}
