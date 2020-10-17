#include <iostream>
#include <ctype.h>
#include <istream>
#include <string.h>
#include <stdlib.h>
#include "dizi.h"

using namespace std;

void printScr();
bool selectChoi(char &s);

PhoneBook book;

void kayitEkle();
void kayitListele();
void kayitSil();


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

	book.remove();

	getchar();
	return 0;
}


void printScr()
{
	system("cls");
	cout << "Phonebook" << endl;
	cout << "a: add record" << endl;
	cout << "l: list records" << endl;
	cout << "r: remove record" << endl;
	cout << "select: " << endl;
	//getchar();
	return;
}

bool selectChoi(char &s)
{
	s = tolower(s);
	switch (s)
	{
		case 'a':
			kayitEkle();
			cin.ignore();
			getchar();
			break;

		case 'l':
			kayitListele();
			cin.ignore();
			getchar();
			break;

		case 'r':
			//kayitSil();
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

void kayitEkle()
{
	telKayit newrec;
	//char *temp_ad = new char[15];
	newrec.ad = new char[15];
	newrec.soyad = new char[15];
	newrec.telno = new char[15];

	cout << "new record" << endl;
	cout << "name: ";
	cin.ignore(1000, '\n');
	//cin >> newrec.ad;
	//cin.get(newrec.ad);
	cin.getline(newrec.ad, 15, '\n');

	cout << "surname: ";
	cin.getline(newrec.soyad, 15, '\n');

	cout << "tel number: ";
	cin.getline(newrec.telno, 15, '\n');
	

	//cout << newrec.ad << strlen(newrec.ad) << endl;
	//cout << newrec.soyad << strlen(newrec.soyad) << endl;
	//cout << newrec.telno << strlen(newrec.telno) << endl;

	book.add(newrec);

	delete[] newrec.ad;
	delete[] newrec.soyad;
	delete[] newrec.telno;
}


void kayitListele()
{
	telKayit *nodeptr;
	nodeptr = book.arr;

	int ctr = 1;

	while (1)
	{
		if (nodeptr->ad != NULL && nodeptr->soyad != NULL && nodeptr->telno != NULL)
			cout << ctr++ << nodeptr->ad << '\t' << nodeptr->soyad << '\t' << nodeptr->telno << endl;
		else
			break;
		nodeptr++;
	}


}