#include"History.h"
#include<iostream>
using namespace std;

History::History(int nRows, int nCols)
	: m_rows(nRows), m_cols(nCols)
{
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
			rcd[i][j] = 0;
}


bool History::record(int r, int c)
{
	if ((r > m_rows) || (c > m_cols) || (r <= 0) || (c <= 0)) return false;
	else rcd[r - 1][c - 1] += 1;
	return true;
	}

void History::display() const
{
	clearScreen();
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			if (rcd[i][j] == 0) cout << '.';
			else if (rcd[i][j] < 26) cout << static_cast<char> (rcd[i][j] - 1 + 'A');
			else cout << 'Z';
		}
		cout << endl;
	}
	cout << endl;
}