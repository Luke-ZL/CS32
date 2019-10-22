#include <queue>
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
	queue<Coord> coordQueue;
	Coord current(sr, sc);
	coordQueue.push(current);
	maze[sr][sc] = '#';
	while (!coordQueue.empty())
	{
		current = coordQueue.front();
		//cout << current.r() << ' ' << current.c() << endl;
		coordQueue.pop();
		if ((current.r() == er) && (current.c() == ec)) return true;
		Coord east(current.r(), current.c() + 1);
		Coord south(current.r() + 1, current.c());
		Coord west(current.r(), current.c() - 1);
		Coord north(current.r() - 1, current.c());
		if (maze[east.r()][east.c()] == '.') {
			coordQueue.push(east);
			maze[east.r()][east.c()] = '#';
		}
		if (maze[south.r()][south.c()] == '.') {
			coordQueue.push(south);
			maze[south.r()][south.c()] = '#';
		}
		if (maze[west.r()][west.c()] == '.') {
			coordQueue.push(west);
			maze[west.r()][west.c()] = '#';
		}
		if (maze[north.r()][north.c()] == '.') {
			coordQueue.push(north);
			maze[north.r()][north.c()] = '#';
		}
	}
	return false;
}

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