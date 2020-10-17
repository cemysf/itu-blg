#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "structs.h"

using namespace std;
typedef str Game;

void printMenu();
bool selectChoice(char &s);
int suitToIndex(char &suitType);
//void topToFound();
//void topToBoard();
void topCardToList(int cListType);
void boardToBoard();
void boardToFound();

Game solitaire;

int main()
{

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
    cout <<"\t" << "1. Select from Top List to Foundation Lists" << endl;
    cout <<"\t" << "2. Select from Top List to Board Lists" << endl;
    cout <<"\t" << "3. Move on the Board Lists" << endl;
    cout <<"\t" << "4. Move from Board Lists to Foundation List" << endl;
    cout <<"\t" << "E: Exit Program" << endl;
    cout << "Enter choice: " ;
}

bool selectChoice(char &s)
{
    switch(s)
    {
        case '1':
            //topToFound();
            topCardToList(0);
            break;
        case '2':
            //topToBoard();
            topCardToList(1);
            break;
        case '3':
            boardToBoard();
            break;
        case '4':
            boardToFound();
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



//void topToFound()
//{
//    char color,suit;
//    string numb;
//    cout << "Select a card from Top List: ";
//    cin.ignore(1000, '\n');
//    cin >> color >> suit >> numb;
//
//    color=toupper(color);
//    suit=toupper(suit);
//    if(isalpha(numb[0]))
//        numb=toupper(numb[0]);
//
//    int suitNumber;
//    bool moveControl=false;
//    cardList *found = solitaire.searchList(solitaire.topList,color,suit,numb);
//    if(found!=NULL)
//    {
//        suitNumber = suitToIndex(suit);
//        moveControl = solitaire.compareCardtoList(found, solitaire.foundationList[suitNumber],0); //solitaire.compareToFound(found, solitaire.foundationList[suitNumber]);
//
//        cout << found->color << found->suit <<  found->number << " : " << moveControl << endl;
//        if(moveControl)
//        {
//            solitaire.transferTopToFound(found, suitNumber);
//            cout << "Succesfull" << endl;
//        }
//        else
//        {
//            cout << "Wrong movement" << endl;
//        }
//
//        Game.compare(found, Game.foundationList[4-((atoi(found->suit)%23)%10)])
//    }
//    else
//        cout << "Card not found.." << endl;
//
//    cin.ignore();
//    getchar();
//}
//
//void topToBoard()
//{
//    char color,suit;
//    string numb;
//    int boardIndex;
//    cout << "Select a card from Top List: ";
//    cin.ignore(1000, '\n');
//    cin >> color >> suit >> numb;
//    cout << "Select the number of destination Board List: ";
//    cin >> boardIndex;
//
//    color=toupper(color);
//    suit=toupper(suit);
//    if(isalpha(numb[0]))
//        numb=toupper(numb[0]);
//    if(!isdigit(boardIndex))
//
//    bool moveControl=false;
//    cardList *found = solitaire.searchList(solitaire.topList,color,suit,numb);
//    if(found!=NULL)
//    {
//        moveControl=solitaire.compareCardtoList(found,solitaire.boardList[boardIndex-1],1);
//
//        if(moveControl)
//        {
//
//        }
//    }
//
//
//}

// cListType==0 move to foundation list, cListType==1 move to board list
void topCardToList(int cListType)
{
    char color,suit;
    string numb;
    cout << "Select a card from Top List: ";
    cin.ignore(1000, '\n');
    cin >> color >> suit >> numb;
    int boardIndex;     //for board lists
    if(cListType==1)
    {
        cout << "Select the number of destination Board List: ";
        cin >> boardIndex;
    }

    color=toupper(color);
    suit=toupper(suit);
    if(isalpha(numb[0]))
        numb=toupper(numb[0]);
    //if(!isdigit(boardIndex))

    bool moveControl=false;
    cardList *found = solitaire.searchList(solitaire.topList,color,suit,numb);
    if(found!=NULL)
    {
        if(cListType==0)
        {
            moveControl = solitaire.compareCardtoList(found, solitaire.foundationList[solitaire.suitToIndex(suit)],0);
        }
        if(cListType==1)
        {
            moveControl=solitaire.compareCardtoList(found,solitaire.boardList[boardIndex-1],1);
        }

        if(moveControl)
        {
            if(cListType==0)
                solitaire.transferTopToFound(found, solitaire.suitToIndex(suit));
            if(cListType==1)
                solitaire.transferToptoBoard(found, boardIndex-1);
            cout << "Succesfull" << endl;
        }
        else
            cout << "Wrong movement" << endl;
    }
    else
        cout << "Card not found.." << endl;

    cin.ignore();
    getchar();
}

void boardToBoard()
{
    int srcIndex,destIndex,result;
    cout << "Select the number of the source Board List: ";
    cin.ignore(1000, '\n');
    cin >> srcIndex;
    cout << "Select the number of the destination Board List: ";
    cin >> destIndex;

    char color,suit;
    string numb;
    cout << "Select a card from Board List to determine starting point of movement: ";
    cin >> color >> suit >> numb;
    color=toupper(color);
    suit=toupper(suit);
    if(isalpha(numb[0]))
        numb=toupper(numb[0]);

    result = solitaire.moveOnBoards(srcIndex-1,destIndex-1,color,suit,numb);

    switch(result)
    {
        case -1:
            cout << "Card not found.." << endl;
            break;
        case 0:
            cout << "Wrong movement.." << endl;
            break;
        case 1:
            cout << "Succesfull" << endl;
            break;

    }
    cin.ignore();
    getchar();
}

void boardToFound()
{
    int srcIndex;
    cout << "Select a number of the source Board List: ";
    cin.ignore(1000, '\n');
    cin >> srcIndex;

    int result = solitaire.transferBoardToFound(srcIndex-1);

    switch(result)
    {
        case -1:
            cout << "Card not found.." << endl;
            break;
        case 0:
            cout << "Wrong movement.." << endl;
            break;
        case 1:
            cout << "Succesfull" << endl;
            break;

    }
    cin.ignore();
    getchar();


}
