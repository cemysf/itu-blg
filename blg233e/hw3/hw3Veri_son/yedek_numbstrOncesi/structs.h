#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>

using namespace std;

typedef struct node
{   char color;
    char suit;
    int number;
    int alignment; //0 for down, 1 for up
    node *next;
}cardList;


struct str
{
    cardList *topList;
    cardList *foundationList[4];
    cardList *boardList[7];

    void initLists();
    void closeProgram();

    void readFromFile();
    void addToList(cardList **ptr, char &color, char &suit, int &number, int &aligmnt);
    //void printList(cardList *ptr);

    int cardToNumber(char *ch); // A,K,Q,J to number
    string numberToCard(int numb); // 1,13,12,11 to A,K,Q,J
    void printGame();

    void clearLists(cardList *ptr);

};

void str::initLists()
{
    topList=NULL;
    for(int i=0;i<7;i++)
    {
        boardList[i]=NULL;
        if(i<4) foundationList[i]=NULL;
    }
}

void str::closeProgram()
{
    clearLists(topList);
    for(int i=0;i<7;i++)
    {
        clearLists(boardList[i]);
        if(i<4) clearLists(foundationList[i]);
    }
}

void str::readFromFile()
{

    FILE *fp = fopen("solitaire.txt","r");

    if(fp==NULL)
    {
        cout << "File error." << endl;
        exit(-1);
    }

    char line[20];

    //to determine top or board lists
    int starCounter =-1;

    char *color,*suit;
    int numb,aligmnt;

    while(fgets(line,20,fp)!=NULL)
    {
        //if line contains stars, read next line (also determines list)
        if(strstr(line,"******")!=NULL) //(strcmp(line,"******\n")==0)
        {
            starCounter++;
            continue;
        }

        color = strtok(line," ");
        suit = strtok(NULL," ");

        //holding A,K,Q,J as number
        numb = cardToNumber(strtok(NULL," "));

//        char *temp=strtok(NULL," ");
//        //holding A,K,Q,J as number
//        switch(*temp)
//        {
//        case 'A':
//            numb=1;
//            break;
//        case 'K':
//            numb=13;
//            break;
//        case 'Q':
//            numb=12;
//            break;
//        case 'J':
//            numb=11;
//            break;
//        default:
//            numb=atoi(temp);
//        }

        //if down, set align to 0
        aligmnt=1;
        //temp=strtok(NULL," ");
        if(strstr(strtok(NULL," "),"Down")!=NULL)
            aligmnt=0;

//        aligmnt = strtok(NULL," ");
//        //terminating alignment string
//        aligmnt[strlen(aligmnt)-2] = '\0';  /* use [strlen(aligmnt)-1] for windows (\n in windows, \r\n in linux) */

/*        cout <<"c:"<< color;
        cout <<" s:"<< suit;
        cout <<" n:"<< numb;
        cout <<" al:"<< aligmnt<< endl;
*/
        if(starCounter==-1)
        {
            cout << "";
            addToList(&topList,*color,*suit,numb,aligmnt);
        }
        else
            addToList(&boardList[starCounter],*color,*suit,numb,aligmnt);
    }
    fclose(fp);
}

//sending head address of the list, which is a pointer, so ** must be used
void str::addToList(cardList **ptr, char &color, char &suit, int &number, int &aligmnt)
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
    newnode->alignment=aligmnt; //strcpy(newnode->alignment,&aligmnt);


    if(*ptr==NULL)
    {
        *ptr=newnode;
    }
    else
    {
        cardList *traverse = *ptr;

        while(traverse->next!=NULL)
            traverse=traverse->next;

        traverse->next=newnode;
    }
    newnode->next=NULL;
}
//
//void str::printList(cardList *ptr)
//{
//    cout << "----------" << endl;
//    while(ptr!=NULL)
//    {
//        cout <<"asd c:"<< ptr->color << " s:"<< ptr->suit << " n:"<< ptr->number<< " al:" << ptr->alignment<< endl;
//        ptr=ptr->next;
//    }
//
//}

int str::cardToNumber(char *ch)
{
    int numb;
    switch(*ch)
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
        numb=atoi(ch);
    }
    return numb;
}

string str::numberToCard(int numb)
{
    string ch;
    switch(numb)
    {
    case 1:
        ch='A';
        break;
    case 13:
        ch='K';
        break;
    case 12:
        ch='Q';
        break;
    case 11:
        ch='J';
        break;
    case 10:
        ch="10";
        break;
    default:
        ch=numb+'0';
    }
    return ch;
}

void str::printGame()
{
    cout << "Top List:" << endl << endl;

    cardList *ptr=topList;
    while(ptr!=NULL)
    {
        // all cards are visible in the toplist
        cout << ptr->color << ","<< ptr->suit << "," << numberToCard(ptr->number) << " | ";
        ptr=ptr->next;
    }

    cout << endl << endl  << "Board Lists:" << endl << endl;
    //initialize pointer array to traverse
    cardList *temp[7];
    for(int i=0;i<7;i++)
    {
        cout << i+1 << ". list" << "\t";
        temp[i]=boardList[i];
    }
    cout << endl;

    for(int j=0;j<7;j++)
    {
        for(int i=0;i<7;i++)
        {
            if(temp[i]==NULL)
                cout << "" << "\t";
            else
                if(temp[i]->alignment==0)
                    cout << "X" << "\t";
                else
                    cout << temp[i]->color << ","<< temp[i]->suit << "," << numberToCard(temp[i]->number) << "\t";

            if(temp[i]!=NULL) temp[i]=temp[i]->next;
        }
        cout << endl;
    }

    cout << endl << endl  << "Foundation Lists:" << endl << endl;
    const char *foundLst[4]= {"Spades","Hearts","Diamonds","Clubs"};
    for(int i=0;i<4;i++)
        cout << foundLst[i] << "\t" ;
    cout << endl;

/*    for(int i=0;i<7;i++)
    {
        cout << setw(i*10) << i+1 << ". list" << endl;
        ptr=boardList[i];
        while(ptr!=NULL)
        {
            if(ptr->alignment==0)
                cout << setw(i*10) << "X" << endl;
            else
                cout << ptr->color << ","<< ptr->suit << "," << ptr->number<< endl;
            ptr=ptr->next;
        }
    }
*/
}

void str::clearLists(cardList *ptr)
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
