#include <iostream>
#include <ctype.h>
#include <istream>
#include <string.h>
#include <cctype>
#include <stdlib.h>
#include "dizi.h"

#define TEMPSIZE 15

using namespace std;

void printScr();
bool selectChoi(char &s);

PhoneBook book;

void kayitEkle();
void kayitListele();
void kayitSil();
void kayitAra();

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
	cout << "s: search record" << endl;
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
			kayitSil();
			break;

		case 's':
			kayitAra();
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

void kayitEkle()
{
	telKayit newrec;
	//char *temp_ad = new char[TEMPSIZE];
	newrec.ad = new char[TEMPSIZE];
	newrec.soyad = new char[TEMPSIZE];
	newrec.telno = new char[TEMPSIZE];

	cout << "new record" << endl;
	cout << "name: ";
	cin.ignore(1000, '\n');
	//cin >> newrec.ad;
	//cin.get(newrec.ad);
	cin.getline(newrec.ad, TEMPSIZE, '\n');

	cout << "surname: ";
	cin.getline(newrec.soyad, TEMPSIZE, '\n');

	cout << "tel number: ";
	cin.getline(newrec.telno, TEMPSIZE, '\n');
	

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
		if (nodeptr->ad != NULL && nodeptr->soyad != NULL && nodeptr->telno != NULL 
			&& ctr<=book.listCounter) //(isalnum((int)(nodeptr->ad[0])))
			cout << ctr++ << ": " <<  nodeptr->ad << '\t' << nodeptr->soyad << '\t' << nodeptr->telno << endl;
		else
			break;
		nodeptr++;
	}
}

void kayitSil()
{
	cout << "enter index (-1 to delete all): " << endl;
	int indx;
	cin.ignore();
	cin >> indx;
	indx--;
	book.remove(indx);
}

void kayitAra()
{
	telKayit *nodeptr;
	nodeptr = book.arr;
	int ctr = 1;
	bool found = false;

	char *input=new char[TEMPSIZE];
	cout << "enter name:";
	//cin.ignore();
	//cin.getline(&input, TEMPSIZE, '\n');
	cin.ignore(1000, '\n');
	cin.getline(input, TEMPSIZE, '\n');
	
	while ((nodeptr->ad != NULL && nodeptr->soyad != NULL && nodeptr->telno != NULL && ctr <= book.listCounter))
	{
	
		if (strcmp(input, nodeptr->ad) == 0){
			cout << ctr << ": " << nodeptr->ad << '\t' << nodeptr->soyad << '\t' << nodeptr->telno << endl;
			found = true;
		}

		/*if (ctr > book.listCounter)
			break;*/

		ctr++;
		nodeptr++;
	}

	if (!found) cout << "not found" << endl;
	getchar();
	
}
