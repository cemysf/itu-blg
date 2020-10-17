#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

typedef struct node
{   char color;
    char suit;
    int number;
    char *alignment;//[5];
    node *next;
}cardList;


typedef struct str
{
    cardList *topList;
    cardList *foundationList[4];
    cardList *boardList[7];

    void initLists();
    void closeProgram();

    void readFromFile();
    void addToList(cardList *ptr, char &color, char &suit, int &number, char &aligmnt);
    void clearLists(cardList *ptr);

}Game;


void Game::initLists()
{
    topList=NULL;
    for(int i=0;i<7;i++)
    {
        boardList[i]=NULL;
        if(i<4) foundationList[i]=NULL;
    }
}

void Game::closeProgram()
{
    clearLists(topList);
    for(int i=0;i<7;i++)
    {
        clearLists(boardList[i]);
        if(i<4) clearLists(foundationList[i]);
    }
}

void Game::readFromFile()
{

    FILE *fp = fopen("solitaire.txt","r");

    if(fp==NULL)
    {
        cout << "File error." << endl;
        exit(-1);
    }

    char line[20];
    size_t counter =0;

    char *color,*suit;
    int numb;
    char *aligmnt;//[5];

    while(fgets(line,20,fp)!=NULL)
    {
        if(strcmp(line,"******\n")==0)
            continue;

        counter ++;
        //cout << line;

        color = strtok(line," ");
        suit = strtok(NULL," ");

        char *tempnumb=strtok(NULL," ");
        switch(*tempnumb)
        {
        case 'A':
            numb=1;
            break;
        case 'K':
            numb=13;
            break;
        case 'Q':
            numb=12;
            break;
        case 'J':
            numb=11;
            break;
        default:
            numb=atoi(tempnumb);
        }

        strcpy(aligmnt,strtok(NULL," "));
        aligmnt[strlen(aligmnt)-1] = '\0';


        cout <<"c:"<< color;
        cout <<" s:"<< suit;
        cout <<" n:"<< numb;
        cout <<" al:"<< aligmnt<< endl;

    }
    fclose(fp);
    //cout << counter << endl;


}


void Game::addToList(cardList *ptr, char &color, char &suit, int &number, char &aligmnt)
{
    /* //ptr en son ekleneni gosterir
    cardList *newnode=new cardList;
    //
    (ptr==NULL) ? newnode->next=NULL : newnode->next=ptr;

    newnode->color=color;
    newnode->suit=suit;
    newnode->number=number;
    strcpy(newnode->alignment,aligmnt);
    ptr=newnode;
    */

    cardList *newnode=new cardList;

    newnode->color=color;
    newnode->suit=suit;
    newnode->number=number;
    strcpy(newnode->alignment,&aligmnt);


    if(ptr==NULL)
        ptr=newnode;
    else
    {
        cardList *traverse = ptr;

        while(traverse->next!=NULL)
            traverse=traverse->next;

        traverse->next=newnode;
    }
    newnode->next=NULL;
}

void Game::clearLists(cardList *ptr)
{
    cardList *temp;
    while(ptr!=NULL)
    {
        temp=ptr;
        ptr=ptr->next;
        delete temp;

    }
}

#endif // STRUCTS_H_INCLUDED
