#include "fileoperations.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
void Dosya::ekle(Tel_Kayit *ykptr){
	fseek(teldefteri, 0, SEEK_END);
	fwrite(ykptr, sizeof(Tel_Kayit), 1, teldefteri);
}
void Dosya::olustur(){
	Dosya->dosyaadi = "teldefteri.txt";
	teldefteri = fopen(dosyaadi, "r+");
	if (!teldefteri){
		if (!(teldefteri = fopen(dosyaadi, "w+"))){
			cerr << "File can not be opened" << endl;
			exit(1);
		}
	}
}
void Dosya::kapat(){
	fclose(teldefteri);
}
int Dosya::ara(char aranacak[]){
	Tel_Kayit k;
	int sayac = 0;
	bool tumu = false;
	int bulunan = 0;
	if (strcmp(aranacak, "*") == 0)
		tumu = true;
	fseek(teldefteri, 0, SEEK_SET);
	while (!feof(teldefteri)){
		sayac++;
		fread(&k, sizeof (Tel_Kayit), 1, teldefteri);
		if (feof(teldefteri)) break;
		if (!tumu && strnicmp(k.ad, aranacak, strlen(aranacak)) != 0)
			continue;
		cout << sayac << "." << k.ad << " " << k.telno << endl;
		bulunan++;
	}
	return bulunan;
}
void Dosya::guncelle(int kayitno, Tel_Kayit *ykptr){
	if (fseek(teldefteri, sizeof(Tel_Kayit)*(kayitno - 1), SEEK_SET) == 0)
		fwrite(ykptr, sizeof(Tel_Kayit), 1, teldefteri);
}
void Dosya::sil(int kayitno){
	Tel_Kayit boskayit = { "", "" };
	if (fseek(teldefteri, sizeof(Tel_Kayit)*(kayitno - 1), SEEK_SET) == 0)
		fwrite(&boskayit, sizeof(Tel_Kayit), 1, teldefteri);
}
void Dosya::bakim()
{
	char *tempfname = "tempphonebook.txt";
	tempteldef = fopen(tempfname, "w");

	Tel_Kayit kyt;
	
	while (!feof(teldefteri))
	{
		fread(&kyt, sizeof(Tel_Kayit), 1, teldefteri);
		
		if (strcmp(kyt.ad,"")==0) continue;
		else
		{			
			fseek(tempteldef, 0, SEEK_END);
			fwrite(&kyt, sizeof(Tel_Kayit), 1, tempteldef);
		}

	}
	teldefteri = tempteldef;

	fclose(tempteldef);

}
