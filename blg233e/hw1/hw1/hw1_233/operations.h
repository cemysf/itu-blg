/*
* @Author
* Student Name: Cem Yusuf Aydoğdu
* Student ID : 150120251
* Date: 18.09.2014
*/

///  file struct and file operations are in this header

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "facultyRecord_str.h"

#define OFFSET 10

using namespace std;

typedef struct fileStr
{
	char *fileName;
	FILE *recordFile;
	FILE *tempfile;

	void create();
	void add(faculty_record *newRecord);
	void search_file(char &option);
    void printRecords();
    faculty_record readRecord(FILE *f, int index);
    void update(unsigned int index, faculty_record *newRecord);
    void remove_rec(int index);

	void close();


}RecordBook;


void fileStr::create()
{
	fileName = "recordBook.txt";
	recordFile = fopen(fileName,"r+");
	if(recordFile==NULL) fopen(fileName,"w+");

	if(recordFile==NULL)
		{
			cerr << "File error. Please try again." << endl;
			exit(1);
		}
}

void fileStr::add(faculty_record *newRecord)
{
    fseek(recordFile,0,SEEK_END);
    fwrite(newRecord,sizeof(faculty_record),1,recordFile);


}


// multifunctional search (department, name, all)
void fileStr::search_file(char &option)
{
    faculty_record temp;
    char *text;              //to determine department or name
    char query[NAME_LEN];    //query word

    if(option!='P')          // no need to get query for printing all
    {
        cout << "Enter query: " << endl;
        cin.ignore(1000,'\n');
        cin.getline(query,NAME_LEN);
    }

    cout<< "First Name\t" << setw(OFFSET)
        << "Last Name\t"  << setw(OFFSET)
        << "Phone\t"  << setw(OFFSET)
        << "Office\t" << setw(OFFSET)
        << "Department\t"<< endl;

    fseek(recordFile,0,SEEK_SET);

    unsigned int counter=0;
    bool found = false;     //print "none found" if no match

    while(!feof(recordFile))
    {
        counter++;
        fread(&temp, sizeof(faculty_record),1,recordFile);
        if(feof(recordFile)) break;

        if(option=='S')    //by department
        {
            if (strlen(query) > DEPT_LEN)
            {
                cout << "Length must be below then "<< DEPT_LEN <<". Try again"<< endl;
                getchar();
                return;
            }
            else text=temp.dept;

        }
        else if(option=='F')   //by first name
        {
            text=temp.fname;
        }


        if((option != 'P') && strncasecmp(text,query,strlen(query)) != 0)
            continue;

        found = true;
        cout << counter << "." ;
        cout << setw(OFFSET) <<temp.fname << "\t";
        cout << setw(OFFSET) <<temp.lname << "\t";
        cout << setw(OFFSET) <<temp.phone<< "\t";
        cout << setw(OFFSET) <<temp.office << "\t";
        cout << setw(OFFSET) <<temp.dept<< "\t"<<endl;

    }

    if(!found) cout<< "None found"<<endl;
    getchar();
}

//to read a single record
faculty_record fileStr::readRecord(FILE *f, int index)
{
    faculty_record read;

    /*  control values for out of index
    *   if the index is out of range, fread does not work
    *   and these arbitrary values will remain unchanged    */
    read.office=-999;
    read.phone=-999;


    if (fseek(f, sizeof(faculty_record)*(index - 1), SEEK_SET) == 0)
    {
        fread(&read, sizeof(faculty_record),1,f);

    }

    return read;
}

void fileStr::update(unsigned int index, faculty_record *newRecord)
{
    if (fseek(recordFile, sizeof(faculty_record)*(index - 1), SEEK_SET) == 0)
		fwrite(newRecord, sizeof(faculty_record), 1, recordFile);
    getchar();
}

void fileStr::remove_rec(int index)
{
	char *tempfname = "temp_recordbook.txt";
	tempfile = fopen(tempfname, "w+");

    if(tempfile==NULL)
    {
        cout << "File error. Delete unsuccessful" << endl;
        return;
    }
	faculty_record temp;
    int counter=1;

    fseek(recordFile,0,SEEK_SET);
    fseek(tempfile,0,SEEK_SET);

    while(!feof(recordFile))    //transfer all data to temp except deleted one
    {
        temp = readRecord(recordFile,counter);
        if(feof(recordFile)) break;


        if(counter==index)
        {
            counter++;
            continue;
        }

        fwrite(&temp,sizeof(faculty_record),1,tempfile);
        counter++;
    }

    //  arrange write mode for recordFile
    fclose(recordFile);
    recordFile = fopen(fileName,"w");

    fseek(tempfile,0,SEEK_SET);
    fseek(recordFile,0,SEEK_SET);

    counter=1;
    while(!feof(tempfile))  //transfer all data from temp to original file
    {
        temp=readRecord(tempfile, counter);
        counter++;

        if(temp.office==-999 && temp.phone==-999) break;

        fwrite(&temp,sizeof(faculty_record),1,recordFile);



    }
    fclose(tempfile);

    //  arrange file mode again
    close();
    create();

    return;
}


void fileStr::close()
{
	fclose(recordFile);
}

#endif
