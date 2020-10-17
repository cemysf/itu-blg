/*
* @Author
* Student Name: Cem Yusuf Aydoğdu
* Student ID : 150120251
* Date: 18.09.2014
*/

#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <cstdio>
#include "operations.h"
#include <cstring>

using namespace std;

RecordBook book;

void printMenu();
bool selectChoice(char choice);

//functions
void removeRecord();
void searchRecord(char &option);
void addRecord();
void updateRecord();

int main()
{
    book.create();

    char input;
    bool endPrg=false;
    while(!endPrg)
    {
        printMenu();
        cin >> input;
        endPrg=selectChoice(input);
    }
    book.close();
    return 0;
}

void printMenu()
{
    system("clear");    //cls for windows
    cout << endl << endl;
    cout << "Record Book" << endl;
    cout << "Choose an option" << endl;

    cout <<"R : Remove Record" << endl;
    cout <<"S : Search by Department" << endl;
    cout <<"F : Search by First Name" << endl;
    cout <<"A : Add a New Record" << endl;
    cout <<"P : Print all Records" << endl;
    cout <<"U : Update a Record" << endl;
    cout <<"E : Exit the Program" << endl;

    cout << endl;
    cout << "Enter your option : ";
}


bool selectChoice(char choice)
{
    bool endChoice = false;

    choice=toupper(choice);
    switch(choice)
    {
        case 'R':
            removeRecord();
            break;

        case 'S':
            searchRecord(choice);
            break;

        case 'F':
            searchRecord(choice);
            break;

        case 'A':
            addRecord();
            break;

        case 'P':
            searchRecord(choice);
            break;

        case 'U':
            updateRecord();
            break;

        case 'E':
            cout << "Exit Succesfully" << endl;
            endChoice=true;
            break;

        default:
            cout << "Invalid choice, try again" << endl;
            cin.ignore();
            cin >> choice;
            endChoice=selectChoice(choice);
            break;
    }

    return endChoice;

}

void removeRecord()
{
    int index;
    cout << "Enter the index of person you want to delete (-1 to exit): ";
    cin >> index;
    if(index==-1) return;

    faculty_record readFromFile= book.readRecord(book.recordFile,index);
    if(readFromFile.office==-999 && readFromFile.phone==-999)
    {
        cout << "Wrong index. Try again." << endl;
        cin.ignore();
        getchar();
        return;
    }

    cout << endl << "First, Last Name : " <<readFromFile.fname << " / " << readFromFile.lname << endl;
    cout << "Phone, Office : " << readFromFile.phone << " / " << readFromFile.office << endl;
    cout << "Department: " << readFromFile.dept << endl;


    book.remove_rec(index);

    cout << endl << "Record deleted" << endl;

    cin.ignore();
    getchar();
}


void searchRecord(char &option)
{
    book.search_file(option);
    getchar();
}

void addRecord()
{
    faculty_record newRecord;

    cout << "Enter the informations: " << endl;

    cout << "First Name: " << endl;
    cin.ignore(1000, '\n');
    cin.getline(newRecord.fname,NAME_LEN);

    cout << "Last Name: " << endl;
    cin.getline(newRecord.lname,NAME_LEN);

    cout << "Phone: " << endl;
    cin>> setw(15) >> newRecord.phone;

    cout << "Office: " << endl;
    cin>> setw(15) >> newRecord.office;

    cout << "Department: " << endl;
    cin.ignore(1000, '\n');
    cin.getline(newRecord.dept,DEPT_LEN);

    book.add(&newRecord);

    cout << "New record added" << endl;
	getchar();
	return;

}

void updateRecord()
{
    int index;
    cout << "Enter the index of person you want to update (-1 to exit): " << endl;
    cin >> index;
    if(index==-1) return;

    faculty_record readFromFile = book.readRecord(book.recordFile,index);
    if(readFromFile.office==-999 && readFromFile.phone==-999)
    {
        cout << "Wrong index. Try again." << endl;
        getchar();
        return;
    }
    else
    {
        cout <<endl<< "Old Informations" << endl;
        cout << "First, Last Name : " <<readFromFile.fname << " / " << readFromFile.lname << endl;
        cout << "Phone, Office : " << readFromFile.phone << " / " << readFromFile.office << endl;
        cout << "Department: " << readFromFile.dept << endl;
        cout << "Enter new informations : " << endl << endl;

        char name[NAME_LEN],dept[DEPT_LEN];
        int phone;

        cout << "First Name ('n' to leave unchanged): ";
        cin.ignore(1000, '\n');
        strcpy(name,readFromFile.fname);

        cin.getline(readFromFile.fname,NAME_LEN);

        if(strcmp(readFromFile.fname, "n")==0)
        {
            stpcpy(readFromFile.fname,name);
            cout << "\tRemains unchanged" <<endl;
        }

        cout << "Last Name ('n' to leave unchanged): ";
        strcpy(name,readFromFile.lname);

        cin.getline(readFromFile.lname,NAME_LEN);

        if(strcmp(readFromFile.lname, "n")==0)
        {
            stpcpy(readFromFile.lname,name);
            cout << "\tRemains unchanged" <<endl;
        }

        cout << "Phone ('-1' to leave unchanged): ";
        phone = readFromFile.phone;

        cin>> setw(15) >> readFromFile.phone;

        if(readFromFile.phone==-1)
        {
            readFromFile.phone=phone;
            cout << "\tRemains unchanged" <<endl;
        }


        cout << "Office ('-1' to leave unchanged): ";
        phone = readFromFile.office;

        cin>> setw(15) >> readFromFile.office;

        if(readFromFile.office==-1)
        {
            readFromFile.office=phone;
            cout << "\tRemains unchanged" <<endl;
        }


        cout << "Department ('n' to leave unchanged): ";
        strcpy(dept,readFromFile.dept);
        cin.ignore(1000,'\n');
        cin.getline(readFromFile.dept,DEPT_LEN);

        if(strcmp(readFromFile.dept, "n")==0)
        {
            stpcpy(readFromFile.dept,dept);
            cout << "\tRemains unchanged" <<endl;
        }

        cout << endl << "New Informations" << endl;
        cout << "First, Last Name : " <<readFromFile.fname << " / " << readFromFile.lname << endl;
        cout << "Phone, Office : " << readFromFile.phone << " / " << readFromFile.office << endl;
        cout << "Department: " << readFromFile.dept << endl;

        book.update(index,&readFromFile);
        cout << "Record updated" << endl;

        getchar();
        return;

    }




}
