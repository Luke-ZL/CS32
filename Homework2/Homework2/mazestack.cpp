#include <stack>
#include <string>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;
	Coord current(sr, sc);
	coordStack.push(current);
	maze[sr][sc] = '#';
	while(!coordStack.empty())
	{
		current = coordStack.top();
		//cout << current.r() << ' ' << current.c() << endl;
		coordStack.pop();
		if ((current.r() == er) && (current.c() == ec)) return true;
		Coord east(current.r(), current.c() + 1);
		Coord south(current.r() + 1, current.c());
		Coord west(current.r(), current.c() - 1);
		Coord north(current.r() - 1, current.c());
		if (maze[east.r()][east.c()] == '.') {
			coordStack.push(east);
			maze[east.r()][east.c()] = '#';
		}
		if (maze[south.r()][south.c()] == '.') {
			coordStack.push(south);
			maze[south.r()][south.c()] = '#';
		}
		if (maze[west.r()][west.c()] == '.') {
			coordStack.push(west);
			maze[west.r()][west.c()] = '#';
		}
		if (maze[north.r()][north.c()] == '.') {
			coordStack.push(north);
			maze[north.r()][north.c()] = '#';
		}
	}
	return false;
}
	/*Push the starting coordinate(sr, sc) onto the coordinate stack and
		update maze[sr][sc] to indicate that the algorithm has encountered
		it(i.e., set maze[sr][sc] to have a value other than '.').
		While the stack is not empty,
		{ Pop the top coordinate off the stack.This gives you the current
		(r,c) location that your algorithm is exploring.
		If the current(r,c) coordinate is equal to the ending coordinate,
		then we've solved the maze so return true! 
		Check each place you can move from the current cell as follows :
	If you can move EAST and haven't encountered that cell yet,
		then push the coordinate(r,c + 1) onto the stack and update
		maze[r][c + 1] to indicate the algorithm has encountered it.
		If you can move SOUTH and haven't encountered that cell yet,
		then push the coordinate(r + 1,c) onto the stack and update
		maze[r + 1][c] to indicate the algorithm has encountered it.
		If you can move WEST and haven't encountered that cell yet,
		then push the coordinate(r,c - 1) onto the stack and update
		maze[r][c - 1] to indicate the algorithm has encountered it.
		If you can move NORTH and haven't encountered that cell yet,
		then push the coordinate(r - 1,c) onto the stack and update
		maze[r - 1][c] to indicate the algorithm has encountered it.
		}
		There was no solution, so return false*/

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}