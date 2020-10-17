#Include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;
void Dizi::ekle(Tel_Kayit *ykptr){
	strcpy(k[kayitsayisi].ad, ykptr->ad);
	strcpy(k[kayitsayisi].telno, ykptr->telno);
	kayitsayisi++;
}
void Dizi::olustur(){
	kayitsayisi = 0;
}
int Dizi::ara(char aranacak[]){
	int sayac = 0;
	bool tumu = false;
	int bulunan, flag = 0;
	if (strcmp(aranacak, "*") == 0)
		tumu = true;
	for (int i = 0; i<kayitsayisi; i++){
		if (strcmp(k[i].ad, aranacak) == 0)
		{
			cout << i + 1 << ". " << k[i].ad << endl;
			bulunan = i;
			flag = 1;
		}
	}
	return flag;
}
void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr){
	strcpy(k[kayitno - 1].ad, ykptr->ad);
	strcpy(k[kayitno - 1].telno, ykptr->telno);
}
void Dizi::sil(int kayitno){
	Tel_Kayit temp;
	strcpy(temp.ad, "");
	strcpy(temp.telno, "");
	int indisno;
	indisno = kayitno - 1;
	k[indisno] = temp;
}
void Dizi::listele(){
	for (int i = 0; i<kayitsayisi; i++)
		cout << i + 1 << ". " << k[i].ad << " \t" << k[i].telno << endl;
}


void Dizi::readFromFile()
{
	dosyaadi = "phonebook.txt";
	teldefteri = fopen(dosyaadi, "r");
	bool newfile = false;

	if (teldefteri != NULL)
	{
		cout << "file readed" << endl;
	}
	else if (teldefteri==NULL)
	{
		fopen(dosyaadi, "w");
		if (teldefteri==NULL)
		{
			cout << "file error" << endl;
		}
		else
		{
			cout << "A new file is created" << endl;
			newfile = true;
		}
		
		
	}
	
	if (newfile == false)
	{

		fseek(teldefteri, 0, SEEK_SET);
		Tel_Kayit temp;
		//memset(&temp, 0, sizeof(temp));
		int numb;
		while (!feof(teldefteri))
		{

			numb=fread(&temp, sizeof(Tel_Kayit), 1, teldefteri);
			if (feof(teldefteri)) break;
			if(numb==1)	ekle(&temp);
		}
	}
	fclose(teldefteri);
}

void Dizi::writeToFile()
{
	teldefteri = fopen(dosyaadi, "w");

	fseek(teldefteri, 0, SEEK_SET);
	Tel_Kayit temp;
	for (int i = 0; i < kayitsayisi; i++)
	{
		temp = k[i];
		if(strcmp(temp.ad,"")==0 && strcmp(temp.telno, "")==0) continue;
		fwrite(&temp, sizeof(Tel_Kayit), 1, teldefteri);
	}

	fclose(teldefteri);


}


