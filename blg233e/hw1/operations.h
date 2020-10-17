#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "facultyRecord_str.h"

using namespace std;


struct fileStr
{
	char *fileName;
	
	FILE *recordFile;
	
	void create();
	void add();
	void close();
	
	
};

void fileStr::create()
{
	fileName = "recordBook.txt";
	recordFile = fopen(fileName,"r+");
	if(recordFile==NULL) fopen(fileName,"w+");

	if(recordFile==NULL)
		{
			cerr << "File error. Program exits." << endl;
			exit(1);
		}
}

void fileStr::close()
{
	fclose(recordFile);
}
