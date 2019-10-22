#ifndef History_H
#define History_H

#include"globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	int   m_rows;
	int   m_cols;
	int   rcd[MAXROWS][MAXCOLS];
};
#endif // !History_H
