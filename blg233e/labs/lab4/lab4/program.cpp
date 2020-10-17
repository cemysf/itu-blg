
#include <iostream>
#include <ctype.h>
#include <istream>
#include <string.h>
#include <cctype>
#include <stdlib.h>
#include "list.h"
using namespace std;

//Book phonebook;
LinkedList book;

void printScr();
bool selectChoi(char &s);

///
void kisiEkle();
void numEkle();

void kayitListele();

void kisiSil();
void numSil();

void kisiGunc();

void kisiAra();
void kisiList();

int main()
{
	book.create();
	char ch;
	bool end = false;
	while (!end)
	{
		printScr();
		cin >> ch;
		end = selectChoi(ch);

	}

	book.close();

	getchar();
	return 0;
}


void printScr()
{
	system("cls");
	cout << "Phonebook" << endl;
	cout << "a: add person" << endl;
	cout << "n: add number" << endl;
	
	cout << "r: remove person" << endl;
	cout << "t: remove number" << endl;
	
	cout << "u: update person" << endl;
	cout << "y: update number" << endl;

	cout << "s: search " << endl;
	cout << "l: list " << endl;
	cout << endl << "e: exit " << endl;
	cout << endl <<"select: " << endl;
	//getchar();
	return;
}

bool selectChoi(char &s)
{
	s = tolower(s);
	switch (s)
	{
	case 'a':
		kisiEkle();
		cin.ignore();
		getchar();
		break;

	case 'n':
		numEkle();
		cin.ignore();
		getchar();
		break;

	case 'r':
		kisiSil();
		cin.ignore();
		getchar();
		break;

	case 't':
		numSil();
		cin.ignore();
		getchar();
		break;

	case 'u':
		kisiGunc();
		cin.ignore();
		getchar();

	case 'y':
		//numGunc();
		cin.ignore();
		getchar();

	case 's':
		kisiAra();
		getchar();
		break;

	case 'l':
		kisiList();
		getchar();
		break;

	case 'e':
		cout << "program exits" << endl;
		//getchar();
		return true;

	default:
		cout << "invalid input" << endl;
		getchar();
		break;
	}

	return false;
}

void kisiEkle()
{
	char ad[NAME_LEN];
	cout << "name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad, NAME_LEN, '\n');

	book.addPerson(ad);
}

void numEkle()
{
	
	char ad[NAME_LEN], numara[NUM_LEN], type[TYPE_LEN];
	cout << "name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad, NAME_LEN, '\n');

	if (book.search(ad) == NULL)
	{
		cout << " no record found. add first" << endl;
		//getchar();
		return;
	}
	
	cout << "number: " << endl;
	//cin.ignore(1000, '\n');
	cin.getline(numara, NUM_LEN, '\n');

	cout << "type: " << endl;
	//cin.ignore(1000, '\n');
	cin.getline(type, TYPE_LEN, '\n');

	cout << "eklendi" << endl;

	book.addNumber(ad, numara, type);
}

void kisiAra()
{
	char ad[NAME_LEN];
	phoneNode *temp;

	book.search(ad);
	cout << "name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad, NAME_LEN, '\n');

	temp=book.search(ad);
	if (temp == NULL)
	{
		cout << "no person found. add first." << endl;
		return;
	}
	else
	{
		cout << "found: "<< endl << temp->name << endl;

		numberNode *tempnumb = temp->numb;
		while (tempnumb != NULL)
		{
			cout << "  " << tempnumb->number << " " << tempnumb->type << endl;
			tempnumb = tempnumb->next;
		}
	}

	getchar();

}

void kisiSil()
{
	char ad[NAME_LEN];
	cout << "name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad, NAME_LEN, '\n');

	book.delPerson(ad);
}

void numSil()
{
	char ad[NAME_LEN],numara[NUM_LEN];
	cout << "name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad, NAME_LEN, '\n');

	cout << "number: " << endl;
	//cin.ignore(1000, '\n');
	cin.getline(numara, NUM_LEN, '\n');


	book.delNum(ad,numara);
}

void kisiList()
{
	book.listele();
	getchar();
}

void kisiGunc()
{
	char ad[NAME_LEN],yeniad[NAME_LEN];
	cout << "old name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad, NAME_LEN, '\n');

	cout << "new name: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(yeniad, NAME_LEN, '\n');

	book.updName(yeniad,ad);


}