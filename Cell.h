#ifndef __CELL_H
#define __CELL_H
#pragma warning(disable : 4996)
using namespace std;

#define TYPE_EMPTY 0
#define TYPE_INT 1
#define TYPE_DOUBLE 2
#define TYPE_STRING 3
#define TYPE_EXPRESSION 4
#define TYPE_UNKNOWN 5

#include <iostream>
#include <vector>
#include <cstring>
#include <regex>

class Cell
{
	int type;
	char * content;

public:
	int getType() const;
	virtual void setType(int t);
	void setCellContent(const char * cont);
	char * getCellContent() const;
	char * getSubstring(char * string, int position, int length) const;
	int determineContentType() const;
	bool isInt(const char * content) const;
	bool isDouble(const char * content) const;
	bool isString(const char * content) const;
	bool isExpression(const char * content) const;
//	virtual char * getPrintValue() const = 0;
	virtual double getValue() = 0;
	virtual void printCell() = 0;

	Cell();
	Cell(const char * cont);
	Cell(const Cell& other);
	Cell & operator=(const Cell & other);
	virtual ~Cell();
};
#endif 
