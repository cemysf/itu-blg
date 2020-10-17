

struct pos
{
	int x, y;	//coordn
	int avaible[4];//up rigth down left
	//int u, d, r, l;	//avaible points up down..
	int prev_direct; //
};


struct node
{
	int x, y;
	node *next;
};

struct stack
{
	node *head;

	void init();
	void push(int &x, int &y);
	node pop();
};


void stack::init()
{
	head = NULL;
}

void stack::push(int  &x, int &y)
{
	node *newnode = new node;
	newnode->x = x;
	newnode->y = y;
	if (head == NULL)
	{	
		head = newnode;
		head->next = NULL;
	}
	else
	{
		newnode->next = head;
		head = newnode;
	}
}

node stack::pop()
{
	node *temp = head;
	head = head->next;

	node ret;
	ret.x = temp->x;
	ret.y = temp->y;

	delete temp;
	return ret;
}


/*
int main()
{
	int startX = 0, startY = 0, endX = 0, endY = 0;
	//stack s;

	findPoint(maze0, &startX, &startY, 'S');
	findPoint(maze0, &endX, &endY, 'E');
	pos traverse = { startX, startY, 0, 0, 0, 0, 0 };
	traverse.direct = RIGHT;
	int mvCounter = 0;	//birden fazla yola girebiliyorsa
	bool moved = false;

	while (!(traverse.x == endX && traverse.y == endY))
	{
		maze0[traverse.y][traverse.x] = 'o';
		printMaze(maze0);
		mvCounter = moveControl(&traverse, maze0);

		//if (mvCounter>2) 
		//push to stack

		if (traverse.avaible[traverse.direct] != 1) //mevcut yön uygun değil
		{
			if (traverse.direct % 2 == 0) //yön up veya down
			{
				if (traverse.avaible[1] == 1)	//rigth uygun
					traverse.direct = 1;
				if (traverse.avaible[3] == 1)	//left uygun
					traverse.direct = 3;
			}
			if (traverse.direct % 2 == 1) //yön right veya left
			{
				if (traverse.avaible[0] == 1)	//up uygun
					traverse.direct = 0;
				if (traverse.avaible[2] == 1)	//down uygun
					traverse.direct = 2;
			}
		}

		//	for (int i = 0; i < 4; i++)	//hareket ettir
		//	{


		if (traverse.avaible[traverse.direct] == 1)//(traverse.avaible[i] == 1 && i == traverse.direct) //yön uygunsa
		{
			switch (traverse.direct)
			{
			case 0:	//up
				traverse.y--;
				moved = true;
				break;
			case 1: //right
				traverse.x++;
				moved = true;
				break;
			case 2: //down
				traverse.y++;
				moved = true;
				break;
			case 3: //left
				traverse.x--;
				moved = true;
				break;
			}
		}
		//	}


	}


	//cout << startX << startY;
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

bool findPoint(char labry[10][16], int *x, int *y, char ch)
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

	int movecount = 0;
	if (labry[p->y][(p->x) + 1] != '#'){ p->avaible[1] = 1; movecount++; } //r 
	if (labry[p->y][(p->x) - 1] != '#'){ p->avaible[3] = 1; movecount++; }  //l
	if (labry[(p->y) + 1][p->x] != '#'){ p->avaible[2] = 1; movecount++; }  //d
	if (labry[(p->y) - 1][p->x] != '#'){ p->avaible[0] = 1;  movecount++; } //u
	return movecount;
}

*/