#include <cstdio>
#include <iostream>
using namespace std;

typedef struct cell
{
	bool left, right, up, down;
	char val;
	bool visited;
};

struct  node
{
	int y_x[2];
	node *next;
};

typedef struct str
{
	node *head;

	void init();
	void close();

	void push(int &y, int &x);
	int *pop();
	bool isempty();
	void print();
}Stack;

void str::init()
{
	head = NULL;
}

void str::close()
{
	while (head != NULL) pop();
}

void str::push(int &y, int &x)
{
	node *newnode = new node;
	newnode->y_x[0] = y;
	newnode->y_x[1] = x;
	newnode->next = head;
	head = newnode;	
}

int * str::pop()
{
	node *temp = head;
	int tempy_x[2];
	tempy_x[0] = head->y_x[0];
	tempy_x[1] = head->y_x[1];
	head = head->next;
	delete temp;
	return tempy_x;
}

bool str::isempty()
{
	if(head == NULL) return true;
	else return false;
}

void str::print()
{
	node *temp = head;
	while (temp != NULL)
	{
		cout << "y: " << temp->y_x[0] << "x: " << temp->y_x[1] << endl;
		temp = temp->next;
	}

}
