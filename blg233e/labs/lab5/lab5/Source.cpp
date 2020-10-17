#include <cstdio>
#include <iostream>
#include "Header.h"

#define UP 0
#define DOWN 2
#define RIGHT 1
#define LEFT 3

using namespace std;

void printMaze(char labry[10][16]);
bool findPoint(char labry[10][16],int *x,int *y,char ch);
int moveControl(pos *p, char labry[10][16]);

char maze1[10][16] = {
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
	{ '#', '.', 'S', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '#' },
	{ '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '.', '#', '.', '#' },
	{ '#', '.', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '#', '#', '.', '#' },
	{ '#', '#', '.', '.', '#', '.', '.', '.', '.', '#', '.', '#', 'E', '.', '.', '#' },
	{ '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#' },
	{ '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.', '.', '.', '#' },
	{ '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '.', '#' },
	{ '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#' },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' }
};

char maze0[10][16] = {
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
	{ '#', '.', 'S', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#' },
	{ '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '.', '#', '.', '#' },
	{ '#', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '#', '#', '.', '#' },
	{ '#', '#', '.', '.', '#', '.', '.', '.', '.', '#', '.', '#', 'E', '.', '.', '#' },
	{ '#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#' },
	{ '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#' },
	{ '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '.', '#' },
	{ '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#' },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' }
}; 

int main()
{
	int startX=0, startY=0,endX=0,endY=0;
	stack *s=new stack;
	
	findPoint(maze0, &startX, &startY, 'S');
	findPoint(maze0, &endX, &endY, 'E');
	pos traverse = { startX, startY, 0, 0, 0, 0, 0 };
	traverse.prev_direct = LEFT;
	int mvCounter = 0;	//birden fazla yola girebiliyorsa
	bool moved = false;

	while( !(traverse.x == endX && traverse.y==endY))
	{
		moved = false;
		if (maze0[traverse.y][traverse.x] == 'E')
			break;

		maze0[traverse.y][traverse.x] = 'o';
		printMaze(maze0);
		mvCounter=moveControl(&traverse, maze0);

		if (mvCounter > 1)
			s->push(traverse.x, traverse.y);
			


		// select a possible move
		if (traverse.avaible[DOWN] == 1 && traverse.prev_direct != DOWN)
		{
			traverse.y++;
			traverse.prev_direct = UP;
			moved = true;
		}

		else if (traverse.avaible[UP] == 1 && traverse.prev_direct != UP)
		{
			traverse.y--;
			traverse.prev_direct = DOWN;
			moved = true;
		}
		else if (traverse.avaible[RIGHT] == 1 && traverse.prev_direct != RIGHT)
		{
			traverse.x++;
			traverse.prev_direct = LEFT;
			moved = true;
		}
		else if (traverse.avaible[LEFT] == 1 && traverse.prev_direct != LEFT)
		{
			traverse.x--;
			traverse.prev_direct = RIGHT;
			moved = true;
		}
		
		
		if (moved == false)
		{
			node temp=s->pop();
			traverse.x = temp.x;
			traverse.y = temp.y;
		}

	}


	cout << "path found" << endl;
	delete s;
	getchar();
	return 0;
}

void printMaze(char labry[10][16])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
			cout << labry[i][j];
		cout << endl;
	}
	cout << endl;
}

bool findPoint(char labry[10][16], int *x, int *y,char ch)
{
	for (int i = 0; i < 10; i++)	
	{
		for (int j = 0; j < 16; j++){	
			if (labry[i][j] == ch)
			{
				*x = j;
				*y = i;
				return true;
			}
		}
	}
	return false;
}

int moveControl(pos *p, char labry[10][16])
{
/*	if (labry[p->y][(p->x) + 1] != '#') p->r = 1;
	if (labry[p->y][(p->x) - 1] != '#') p->l = 1;
	if (labry[(p->y) + 1][p->x] != '#') p->d = 1;
	if (labry[(p->y) - 1][p->x] != '#') p->u = 1;
*/
	int movecount = 0;
	for (int i = 0; i < 4; i++)
		p->avaible[i] = 0;

	if (labry[p->y][(p->x) + 1] == '.'){ p->avaible[1] = 1; movecount++;} //r 
	if (labry[p->y][(p->x) - 1] == '.'){ p->avaible[3] = 1; movecount++; }  //l
	if (labry[(p->y) + 1][p->x] == '.'){ p->avaible[2] = 1; movecount++; }  //d
	if (labry[(p->y) - 1][p->x] == '.'){ p->avaible[0] = 1;  movecount++; } //u
	return movecount;
}