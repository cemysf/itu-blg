#include <cstdio>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "head.h"
#define MAZESIZE 10

using namespace std;
cell m[MAZESIZE][MAZESIZE];

void print();
void maze_init();
void maze_create();
bool unvisited_cell_exist();
Stack stck;

int main()
{
	
	stck.init();

	maze_init();
	maze_create();
	print();


	getchar();
	stck.close();
	return 0;
}

void maze_init()
{
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			m[i][j].down = true;
			m[i][j].left = true;
			m[i][j].right = true;
			m[i][j].up= true;
			m[i][j].val = ' ';
			m[i][j].visited = false;
		}
	}

}

void maze_create()
{
	int initCell[2] = { 0, 0 };
	int currCell[2];	//y,x sýrasýyla

	srand(time(NULL));

	currCell[0] = initCell[0];
	currCell[1] = initCell[1];
	m[currCell[0]][currCell[1]].visited = true;

	while (unvisited_cell_exist())
	{
		bool neigh_contr = false;
		//int unvisited_neighbours[4][4];

		for (int j = -1; j <= 1; j++)	//y
		{
			for (int i = -1; i <= 1; i++)	//x
			{
				if ((j == -1 && i == -1) || (j == -1 && i == 1) || (j == 1 && i == -1) || (j == 1 && i == 1) || (j==0 && i==0))	 //komþu sadece sað sol aþaðý yukarý
					continue;
				if ((currCell[0] == 0 && j == -1 )	//üst			//köþe veya kenar ise bazý komþularý yok
					|| (currCell[1] == 0 &&  i == -1) //sol
					|| (currCell[1] == MAZESIZE - 1 && i == 1) //sað
					|| (currCell[0] == MAZESIZE - 1 && j == 1)) //alt
					continue;

				if (m[currCell[0] + j][currCell[1] + i].visited == false)	//komþu kontrol
				{
					neigh_contr = true;
					break;

				}
			}
				
			if (neigh_contr == true) break;
		}

		// if curr cell has any neigh which is not visited...
		if (neigh_contr == true) 
		{
			bool komsuvar_unvisited = false;
			int y, x;
			do
			{
				y = (rand() % 3 - 1); //-1,0,1
				x = (rand() % 3 - 1);
				komsuvar_unvisited = !((y == -1 && x == -1) || (y == -1 && x == 1) || (y == 1 && x == -1) || (y == 1 && x == 1) || (y == 0 && x == 0))  //komþu sadece sað sol aþaðý yukarý
									&& !((currCell[0] == 0 && y == -1) || (currCell[1] == 0 && x == -1) || (currCell[1] == MAZESIZE - 1 && x == 1) || (currCell[0] == MAZESIZE - 1 && y == 1)); //köþe kenar kontrl
				if ( komsuvar_unvisited==true && m[currCell[0] + y][currCell[1] + x].visited == true) komsuvar_unvisited = false;

			} while(!komsuvar_unvisited);
			
			if (komsuvar_unvisited)
			{

				stck.push(currCell[0], currCell[1]);	//push curr cell

				//remove wall
				if (y == -1 && x == 0)	//komþu üst ise		
				{	
					m[currCell[0]][currCell[1]].up = false;
					m[currCell[0] + y][currCell[1] + x].down = false;

				}
				else if (y == 1 && x == 0) // komþu altta
				{
					m[currCell[0]][currCell[1]].down = false;
					m[currCell[0] + y][currCell[1] + x].up = false;
				}
				else if (y == 0 && x == -1) // solda
				{
					m[currCell[0]][currCell[1]].left = false;
					m[currCell[0] + y][currCell[1] + x].right = false;
				}
				else if (y == 0 && x == 1) //sað
				{
					m[currCell[0]][currCell[1]].right = false;
					m[currCell[0] + y][currCell[1] + x].left = false;
				}

				//make choosen curr,..
				currCell[0] += y;
				currCell[1] += x;
				//cout << currCell[0] << " " << currCell[1] << endl;
				m[currCell[0]][currCell[1]].visited = true;
			}

		}

		else if (stck.isempty()==false)
		{
			int *temp = stck.pop();
			currCell[0] = *(temp);
			currCell[0] = *(temp +1);

		}

		else
		{
			int y, x;
			bool isvisit = false;
			do
			{
				y = rand() % MAZESIZE; //-1,0,1
				x = rand() % MAZESIZE ;
				isvisit = m[y][x].visited;
			} while (!isvisit);

			currCell[0] = y;
			currCell[1] = x;
			m[currCell[0]][currCell[1]].visited = true;
			
		}

	}
}

/*
((currCell[0] == 0 && currCell[1] == 0) && (y == -1 && x == -1)				//köþe kontrol
	|| (currCell[0] == 0 && currCell[1] == MAZESIZE - 1) && (y == -1 && x == 1)
	|| (currCell[0] == MAZESIZE - 1 && currCell[1] == 0) && (y == 1 && x == -1)
	|| (currCell[0] == 0 && currCell[1] == MAZESIZE - 1) && (y == 1 && x == 1))
	*/
bool unvisited_cell_exist()
{
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (m[i][j].visited == false)
				return true;
		}
	}
	return false;
}

void print()
{
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (m[i][j].up)
				cout << " -";
			else cout << "  ";
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

