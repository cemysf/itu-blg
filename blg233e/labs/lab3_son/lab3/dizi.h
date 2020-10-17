#ifndef DIZI_H
#define DIZI_H

#include <cstdio>
#include <string.h>
#include "kayit.h"
using namespace std;

typedef struct dizi
{
	telKayit *arr;
	//telKayit *currentElement;
	//


	int size;
	int listCounter;
	
	void create(); 
	void add(telKayit &yenikyt);
	void arrange();

	void extend();

	void remove();
	void remove(int &index);

	void list();

}PhoneBook;

void dizi::create()
{
	//arr = NULL;
	size = 2;
	arr = new telKayit[size];
	
	for (int i = 0; i < size; i++)
	{
		memset(arr+i, 0, 1);
	}

	listCounter = 0;
	//currentElement = arr;
}

void dizi::extend()
{
	//int old_size = size;
	//size *= 3;
	//telKayit *old_arr = arr;	//eski arrayi kaybetme

	//create();

	//cout << sizeof(arr) << sizeof(old_arr) << endl;

	//for (int i = 0; i < old_size-1; i++)
	//{

	//	(arr + i)->ad = new char[strlen((old_arr + i)->ad)];
	//	arr[i].soyad = new char[strlen(old_arr[i].soyad)];
	//	arr[i].telno = new char[strlen(old_arr[i].telno)];

	//	strcpy((arr + i)->ad, (old_arr + i)->ad);
	//	strcpy(arr[i].soyad, old_arr[i].soyad);
	//	strcpy(arr[i].telno, old_arr[i].telno);
	//}
	//delete[] old_arr;

	int newsize = size * 2;
	telKayit *newArr=new telKayit[newsize];

	for (int i = 0; i <size ; i++)
	{
		newArr[i].ad = new char[strlen(arr[i].ad)];
		newArr[i].soyad = new char[strlen(arr[i].soyad)];
		newArr[i].telno = new char[strlen(arr[i].telno)];

		strcpy(newArr[i].ad, arr[i].ad);
		strcpy(newArr[i].soyad, arr[i].soyad);
		strcpy(newArr[i].telno, arr[i].telno);
	}

	delete[] arr;
	arr = newArr;
	size = newsize;

}


void dizi::add(telKayit &yenikyt)
{
	if (listCounter > (size-1))
	{
		extend();
	}
	

	//initialize
	arr[listCounter].ad = new char[strlen(yenikyt.ad)];
	arr[listCounter].soyad = new char[strlen(yenikyt.soyad)];
	arr[listCounter].telno = new char[strlen(yenikyt.telno)];
	
	strcpy(arr[listCounter].ad, yenikyt.ad);
	strcpy(arr[listCounter].soyad, yenikyt.soyad);
	strcpy(arr[listCounter].telno, yenikyt.telno);

	if(listCounter>=1) arrange();

	listCounter++;
	
}

//alfabetik duzenle
void dizi::arrange()
{
	telKayit tmp;
	
	for (int i = 0; i < listCounter; i++)
	{
		for (int j = i+1; j < listCounter+1; j++)
		{
			if (strcmp(arr[i].ad, arr[j].ad)>0)
			{
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
	}


}

void dizi::remove()
{
	delete[] arr;
}

//removes all array
void dizi::remove(int &index)
{
	for (int i = index+1; i < listCounter; i++)
	{
		strcpy(arr[i - 1].ad, arr[i].ad);
		strcpy(arr[i - 1].soyad, arr[i].soyad);
		strcpy(arr[i - 1].telno, arr[i].telno);
	}

	int newsize = size - 1;
	telKayit *newArr = new telKayit[newsize];

	for (int i = 0; i < newsize; i++)
	{		
		newArr[i].ad = new char[strlen(arr[i].ad)];
		newArr[i].soyad = new char[strlen(arr[i].soyad)];
		newArr[i].telno = new char[strlen(arr[i].telno)];

		strcpy(newArr[i].ad, arr[i].ad);
		strcpy(newArr[i].soyad, arr[i].soyad);
		strcpy(newArr[i].telno, arr[i].telno);
	}

	delete[] arr;
	arr = newArr;
	size = newsize;
	listCounter--;
	
	
	//if (index == -1)
	//{
	//	delete[] arr;
	//	return;
	//}

	////cout << listCounter<<size;
	//
	////sondaki
	//if (index==size-1 || index==listCounter-1)
	//{
	//	//strlen(arr[index].ad);
	//	//(arr[index].ad)[strlen(arr[index].ad)] = '\0';
	//	
	//	/*char *temp;
	//	temp = arr[index].ad;
	//	arr[index].ad = NULL;*/

	//	//delete[] temp;		
	//	

	//	delete[] arr[index].ad;
	//	//memset(arr[index].ad, 0, 1);
	//	//delete[] arr[index].soyad;
	//	//delete[] arr[index].telno;


	//	listCounter--;

	//}

}

#endif