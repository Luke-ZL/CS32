#include<iostream>
#include<string>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec) return true;
	maze[sr][sc] = '#';
	if (maze[sr][sc + 1] == '.') if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) return true;
	if (maze[sr][sc - 1] == '.') if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) return true;
	if (maze[sr + 1][sc] == '.') if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) return true;
	if (maze[sr - 1][sc] == '.') if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) return true;
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



/*If the start location is equal to the ending location, then we've
solved the maze, so return true.
Mark the start location as visted.
For each of the four directions,
If the location one step in that direction(from the start
	location) is unvisited,
	then call pathExists starting from that location(and
		ending at the same ending location as in the
		current call).
	If that returned true,
	then return true.
	Return false.*/