#ifndef LIST_H
#define LIST_H
#include "records.h"
#include <iostream>
#include <ctype.h>
#include <istream>
#include <string.h>
#include <cctype>
#include <stdlib.h>

using namespace std;

typedef struct list
{
	phoneNode *head, *tail;
	int personcount;

	void create();
	void close();

	//phoneNode * createNode(char *isim, char *num, char * tip);

	void addPerson(char *isim);
	void addNumber(char *isim, char *num, char * tip);

	void delPerson(char *isim);
	void delNum(char *isim,char *num);

	void updName(char *isim, char *eskiisim);

	phoneNode * search(char *isim);
	void listele();

}LinkedList;

void list::create()
{
	head = NULL;
	tail = NULL;
	personcount = 0;
}

void list::close()
{
	phoneNode *temp = head;
	phoneNode *next_temp = NULL;

	while (temp != NULL)
	{
		next_temp = temp->next;

		// numaralarý sil
		numberNode *tempnumb = temp->numb;
		numberNode *nextnumb;
		while (tempnumb != NULL)
		{
			nextnumb = tempnumb->next;
			delete tempnumb;
			tempnumb = nextnumb;
		}
		delete temp;
		temp = next_temp;
	}
}

void list::addPerson(char *isim)
{
	phoneNode *newnode;
	if (head == NULL)
	{
		newnode = new phoneNode;
		newnode->numb = NULL;
		strcpy(newnode->name, isim);

		head = newnode;
		tail = head;

		head->next = NULL;
		head->prev = NULL;

		personcount++;
		return;
	}

	if (strcmp(isim, head->name) < 0)//headden once
	{
		newnode = new phoneNode;
		strcpy(newnode->name, isim);

		
		newnode->numb = NULL;
		newnode->next = head;
		head->prev = newnode;
		head = newnode;
		head->prev = NULL;
		return;
	}

	phoneNode *temp = head;
	//tempi götür
	while (temp && (strcmp(isim, temp->name)>0))
	{
		temp = temp->next;
	}

	if (temp && (strcmp(isim, temp->name) == 0))//isim bulundu
	{
		cout << "person already exists." << endl;
		return;
	}
	else
	{
		newnode = new phoneNode;
		strcpy(newnode->name, isim);
		newnode->numb = NULL;
		if (temp)//iki node arasý
		{
			newnode->next = temp;
			(temp->prev)->next = newnode;
			temp->prev = newnode;
			newnode->prev = temp->prev;
		}
		else //en son
		{
			tail->next = newnode;
			newnode->prev = tail;
			newnode->next = NULL;
			tail = newnode;
		}
		personcount++;
	}
}


void list::addNumber(char *isim, char *num, char * tip)
{
	phoneNode *temp = search(isim);
	if (temp == NULL)
	{
		cout << "no person found. add first." << endl;
	}
	else
	{
		numberNode *newnum = new numberNode;
		newnum->next = NULL;
		strcpy(newnum->number, num);
		strcpy(newnum->type, tip);

		if (temp->numb != NULL) newnum->next = temp->numb;
		temp->numb = newnum;

	}
}

phoneNode * list::search(char *isim)
{
	phoneNode *temp = head;

	while (temp!=NULL)
	{
		if (strcmp(temp->name, isim) == 0) return temp;

		temp = temp->next;
	}
	temp = NULL;//yoksa boþ döndür
	return temp;
}

void list::listele()
{
	phoneNode *temp = head;
	int ctr = 0;
	while (temp != NULL)
	{
		cout << ++ctr << ": " << temp->name << endl;

		numberNode *tempnumb = temp->numb;
		while (tempnumb != NULL)
		{
			cout << "  " << tempnumb->number <<" "<<  tempnumb->type << endl;
			tempnumb = tempnumb->next;
		}
		temp = temp->next;
	}
}

void list::delPerson(char *isim)
{
	phoneNode *temp = search(isim);
	if (temp == NULL)
	{
		cout << "no person found. add first." << endl;
		return;
	}

	numberNode *tempnumb = temp->numb;
	numberNode *nextnumb;

	while (tempnumb != NULL)
	{
		nextnumb = tempnumb->next;
		delete tempnumb;
		tempnumb = nextnumb;
	}

	if (temp == head)
	{
		head = head->next;
		head->prev = NULL;
		delete temp;
		return;
	}
	else if (temp == tail)
	{
		tail = tail->prev;
		tail->next = NULL;
		delete temp;
		return;
	}
	else
	{
		(temp->prev)->next = temp->next;
		(temp->next)->prev = temp->prev;
		temp->next = NULL;
		temp->prev = NULL;
		delete temp;
		return;
	}
	
}

void list::delNum(char *isim,char *num)
{
	phoneNode *temp = search(isim);
	if (temp == NULL)
	{
		cout << "no person found. add first." << endl;
		return;
	}

	if (temp->numb == NULL)
	{
		cout << "no number found" << endl;
		return;
	}

	numberNode *tempnum = temp->numb;
	int numcount = 0;

	while (tempnum != NULL)
	{
		if (strcmp(temp->name, num) == 0) break;
		numcount++;
		tempnum = tempnum->next;
	}

	if (numcount == 1)
	{
		temp->numb = NULL;
		delete tempnum;
	}
	/*
	numberNode *nextnumb;
	while (tempnum != NULL)
	{
		nextnumb = tempnumb->next;
		delete tempnumb;
		tempnumb = nextnumb;
	}
	temp->numb = NULL;*/
}

void list::updName(char *isim,char *eskiisim)
{
	phoneNode *temp = search(eskiisim);
	if (temp == NULL)
	{
		cout << "no person found. add first." << endl;
		return;
	}

	strcpy(temp->name, isim);
	cout << "updated..." << endl;

}


#endif