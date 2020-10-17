#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "structs.h"

using namespace std;
typedef str Game;

void printMenu();
bool selectChoice(char &s);

void topToFound();

int main()
{
    Game solitaire;
    solitaire.initLists();
    solitaire.readFromFile();

    bool end=false;
    char ch;
    while(!end)
    {
        //solitaire.printList(solitaire.topList);
        system("clear");
        solitaire.printGame();
        printMenu();
        cin >> ch;
        end=selectChoice(ch);
    }

    solitaire.closeProgram();

    return 0;
}


void printMenu()
{
    //system("clear");
    cout << "Choose an operation:" << endl;
    cout << endl <<"\t" << "1. Select from Top List to Foundation Lists" << endl;
    cout <<"\t" << "2. Select from Top List to Board Lists" << endl;
    cout <<"\t" << "3. Move on the Board Lists" << endl;
    cout <<"\t" << "4. Move from Board Lists to Foundation List" << endl;
    cout << endl <<"\t" << "E: Exit Program" << endl;
    cout << endl << "Enter choice: " ;
}

bool selectChoice(char &s)
{
    switch(s)
    {
        case '1':
            topToFound();
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case 'E': case 'e':
            cout << "Program terminates.." << endl;
            return true;
        default:
            cout << "Invalid input" << endl;
            getchar();
    }
    return false;
}

void topToFound()
{
    string c,s,n;
    cout << "Select a card from Top List: ";

}
