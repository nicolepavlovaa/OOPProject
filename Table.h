#ifndef __TABLE_H
#define __TABLE_H
#include "Cell.h"
#include "IntegerCell.h"
#include "DoubleCell.h"
#include "StringCell.h"
#include "EmptyCell.h"
#include <vector>
#include <iomanip>

class ExpressionCell;

class Table
{
public:
	void deleteTable();
	vector<Cell*> * getTable();
	void resizee(int r, int c);
	int getSize() const; //getRows-rename
	void setSize(int s);
	int longestRowLength();
	void addCell(int row, int col, const char * content);
	Cell* getCell(int r, int c);
	double getCellValue(int r, int c);
	int getLongestColumnContent(int c) const;
	int printValueLength(Cell* c) const;
	void printTable() ;
	Cell* createInstance(int type, char * c);

	Table();
	Table & operator=(const Table & t);
	Table(const Table& t);
	~Table();

private: 
	vector<Cell*> * table;
	unsigned int size = 0;
};
#endif 
