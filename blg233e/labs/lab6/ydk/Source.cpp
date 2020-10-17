#include <cstdio>
#include <iostream>
#include "Header.h"
#define MAZESIZE 10

using namespace std;

void print(cell m[][MAZESIZE]);

cell m[MAZESIZE][MAZESIZE];

int main()
{

	return 0;
}

void print(cell m[][MAZESIZE])
{
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (m[i][j].up)
				cout << " -";
			else cout << " ";
		}
		cout << endl;
		cout << "|";
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < MAZESIZE; i++)
	{
		if (m[MAZESIZE - 1][i].down)
			cout << " -";
	}
	cout << endl;
}