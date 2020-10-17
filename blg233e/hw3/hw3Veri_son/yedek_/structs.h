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
    string number;
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
    void addToList(cardList **ptr, char &color, char &suit, string &number, int &aligmnt);
    cardList *searchList(cardList *ptr, char &color, char &suit, string &number);

    bool compareCardtoList(cardList *card, cardList *cList,int listType);
    void transferTopToFound(cardList *card, /*cardList *sourceList,*/ int index_FoundList);// cardList *destList);
    void transferToptoBoard(cardList *card, int index_BoardList);
    int moveOnBoards(int src_list, int dest_list, char &color, char &suit, string &number);
    int transferBoardToFound(int src_list);

    int cardToNumber(string &ch); // A,K,Q,J to number
    string numberToCard(int numb); // 1,13,12,11 to A,K,Q,J
    int suitToIndex(char &suitType);

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
    int aligmnt;
    string numb;

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
        numb = strtok(NULL," ");
        //holding A,K,Q,J as number
//        numb = cardToNumber(strtok(NULL," "));

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

//adding a card from text file
//sending head address of the list, which is a pointer, so ** must be used
void str::addToList(cardList **ptr, char &color, char &suit, string &number, int &aligmnt)
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
    //strcpy(newnode->number,number);
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

// will return NULL if not found or empty list
cardList *str::searchList(cardList *ptr,char &color, char &suit, string &number)
{
    cardList *temp=ptr;
    while(temp!=NULL)
    {
        if (temp->color==color && temp->suit==suit && number.compare(temp->number)==0)
            break;
        else
            temp=temp->next;
    }
    return temp;
}

// when trying to send a card to foundation lists
// listType: 0 for comparing to foundation lists, 1 for comparing to board lists
bool str::compareCardtoList(cardList *card, cardList *cList, int listType)
{
    if(card->alignment==0)      //cannot move if not visible
        return false;

    cardList *traverse = cList;

    //if the list is empty
    if(traverse==NULL)
    {
        // topmost element must be A for foundation list and K for board list

        if(listType==0 && card->number=="A")
        {
            return true;
        }

        else if(listType==1 && card->number=="K")
        {
            return true;
        }
        else return false;

    }
    else
    {
        while(traverse->next!=NULL)     //add to the end of the list
            traverse=traverse->next;

        if(listType == 0 ) //comparing to  foundation lists
        {
            // comparing colors-suits are already done in main.cpp

            if(cardToNumber(card->number) - cardToNumber(traverse->number) == 1)
                return true;
        }
        if(listType == 1 ) //comparing to  board lists
        {
            if(cardToNumber(traverse->number) - cardToNumber(card->number)== 1 && traverse->color != card->color)
                return true;
        }
    }
    return false;
}

// transfers given card in top list, to a foundation list
void str::transferTopToFound(cardList *card, int index_FoundList)
{
    cardList *dest_last=foundationList[index_FoundList]; //destList;    // for the last node of the destination list
    cardList *prev=topList;      // for the previous node of the card in the source list

    if(card==topList)            // if the chosen card is the first card in list, carry list pointer to next node
    {
        topList=topList->next;
        //dest_last->next=card;
    }
    else
    {
        while(prev->next!=card)
            prev = prev->next;

        prev->next=card->next;
    }

    if(dest_last==NULL)
        foundationList[index_FoundList]=card;
    else
    {
        while(dest_last->next!=NULL)
            dest_last = dest_last->next;

        dest_last->next=card;
    }

    card->next=NULL;
}

void str::transferToptoBoard(cardList *card, int index_BoardList)
{
    cardList *dest_last=boardList[index_BoardList]; //destList;    // for the last node of the destination list
    cardList *prev=topList;      // for the previous node of the card in the source list

    if(card==topList)            // if the chosen card is the first card in list, carry list pointer to next node
    {
        topList=topList->next;
        //dest_last->next=card;
    }
    else
    {
        while(prev->next!=card)
            prev = prev->next;

        prev->next=card->next;
    }

    if(dest_last==NULL)
        boardList[index_BoardList]=card;
    else
    {
        while(dest_last->next!=NULL)
            dest_last = dest_last->next;

        dest_last->next=card;
    }

    card->next=NULL;
}

int str::moveOnBoards(int src_list, int dest_list, char &color, char &suit, string &number)
{
    cardList *srcPrev = boardList[src_list];
    cardList *destNode = boardList[dest_list];
    cardList *srcNode = NULL;
    bool moveControl=false;

    if(srcPrev==NULL) return -1;    // if no card exist in given source

    // if the first element in the source is given
    if(srcPrev->alignment==1 && srcPrev->color==color && srcPrev->suit==suit && srcPrev->number==number)
    {
        moveControl = compareCardtoList(srcPrev,boardList[dest_list],1);
        if(moveControl)
        {
            //srcNode=boardList[src_list];
            boardList[src_list] = NULL; //boardList[src_list]->next;
            //srcPrev=srcPrev->next;

            if(destNode==NULL) // if dest list is empty
            {
                boardList[dest_list] = srcPrev;
            }
            else
            {
                while(destNode->next!=NULL)
                    destNode=destNode->next;

                destNode->next = srcPrev;
            }
            return 1;   // movement succesfull
        }
        else return 0;  // wrong movement
    }
    else
    {
        while(srcPrev->next!=NULL)
        {
            srcNode=srcPrev->next;
            if(srcNode->alignment==1 && srcNode->color==color && srcNode->suit==suit && srcNode->number==number)
            {
                moveControl = compareCardtoList(srcNode,boardList[dest_list],1);
                if(moveControl)
                {
                    //destNode->next=srcNode;
                    //srcPrev->next=NULL;
                    if(destNode==NULL)
                    {
                        boardList[dest_list]=srcNode;
                    }
                    else
                    {
                        while(destNode->next!=NULL)
                            destNode=destNode->next;

                        destNode->next = srcNode;
                    }
                    srcPrev->next=NULL;
                    srcPrev->alignment=1;
                    return 1;
                }
                else return 0;
            }

            srcPrev=srcPrev->next;
        }

    }

    return -1;  // card not found
}

int str::transferBoardToFound(int src_list)
{
    cardList *srcPrev = boardList[src_list];
    cardList *destNode=NULL;
    cardList *srcNode=NULL;

    bool moveControl=false;

    if(srcPrev==NULL) return -1;

    int suitIndex;
    if(srcPrev->next==NULL && srcPrev->alignment==1)
    {
        //srcNode=srcPrev;
        suitIndex = suitToIndex(srcPrev->suit);
        moveControl = compareCardtoList(srcPrev,foundationList[suitIndex],0);
        if(moveControl)
        {
            boardList[src_list]=NULL;
            destNode=foundationList[suitIndex];

            if(destNode==NULL)
            {
                foundationList[suitIndex] = srcPrev;
            }
            else
            {
                while(destNode->next!=NULL)
                    destNode=destNode->next;

                destNode->next = srcPrev;
            }
            return 1;   // movement succesfull

        }
        else return 0;  // wrong movement
    }
    else
    {
        while(srcPrev->next!=NULL)
        {
            srcNode=srcPrev->next;
            if(srcNode->next==NULL)   // if it is last card in the list
            {
                suitIndex = suitToIndex(srcNode->suit);
                moveControl = compareCardtoList(srcNode,foundationList[suitIndex],0);
                if(moveControl)
                {
                    destNode=foundationList[suitIndex];
                    if(destNode==NULL)
                    {
                        foundationList[suitIndex] = srcNode;
                    }
                    else
                    {
                        while(destNode->next!=NULL)
                            destNode=destNode->next;

                        destNode->next = srcNode;
                    }
                    srcPrev->next=NULL;
                    srcPrev->alignment=1;
                    return 1;
                }
                else return 0;
            }
            srcPrev=srcPrev->next;
        }
    }

    return 0;  // card not found

}


//int str::moveOnBoards(int src_list, int dest_list, char &color, char &suit, string &number)
//{
//    cardList *srcPrev = boardList[src_list];
//    cardList *destNode = boardList[dest_list];
//    cardList *srcNode = NULL;
//    bool moveControl=false;
//
//    if(srcPrev==NULL) return -1;    // if no card exist in given source
//
//    // if the first element in the source is given
//    if(srcPrev->alignment==1 && srcPrev->color==color && srcPrev->suit==suit && srcPrev->number==number)
//    {
//        moveControl = compareCardtoList(srcPrev,boardList[dest_list],1);
//        if(moveControl)
//        {
//            srcNode=boardList[src_list];
//            boardList[src_list] = NULL; //boardList[src_list]->next;
//            //srcPrev=srcPrev->next;
//
//            if(destNode==NULL) // if dest list is empty
//            {
//                boardList[dest_list] = srcNode;
//                boardList[src_list] = NULL;
//            }
//            else
//            {
//                while(destNode->next!=NULL)
//                    destNode=destNode->next;
//
//                destNode->next = srcNode;
//            }
//            return 1;
//        }
//        else return 0;
//    }
//    else
//    {
//        while(srcPrev->next!=NULL)
//        {
//            srcNode=srcPrev->next;
//            if(srcNode->alignment==1 && srcNode->color==color && srcNode->suit==suit && srcNode->number==number)
//            {
//                moveControl = compareCardtoList(srcNode,boardList[dest_list],1);
//                if(moveControl)
//                {
//                    //destNode->next=srcNode;
//                    //srcPrev->next=NULL;
//                    if(destNode==NULL)
//                    {
//                        boardList[dest_list]=srcNode;
//                        boardList[src_list]=NULL;
//                    }
//                    else
//                    {
//                        while(destNode->next!=NULL)
//                            destNode=destNode->next;
//
//                        destNode->next = srcNode;
//                        srcPrev->next=NULL;
//                    }
//                    return 1;
//                }
//                else return 0;
//
//
//            }
//
//            srcPrev=srcPrev->next;
//
//
//        }
//
//    }
//
//
//    return -1;
//}

int str::cardToNumber(string &ch)
{
    int numb;
    if(ch=="A")
        numb=1;
    else if(ch=="K")
        numb=13;
    else if(ch=="Q")
        numb=12;
    else if(ch=="J")
        numb=11;
    else
        numb=atoi(ch.c_str());
//    switch(atoi(ch.c_str()))
//    {
//    case "A":
//        numb=1;
//        break;
//    case 'K':
//        numb=13;
//        break;
//    case 'Q':
//        numb=12;
//        break;
//    case 'J':
//        numb=11;
//        break;
//    default:
//        numb=atoi(ch.c_str());
//    }
    return numb;
}

string str::numberToCard(int numb)
{
    string ch;
    switch(numb)
    {
    case 1:
        ch="A";
        break;
    case 13:
        ch="K";
        break;
    case 12:
        ch="Q";
        break;
    case 11:
        ch="J";
        break;
    case 10:
        ch="10";
        break;
    default:
        ch = numb+'0';
    }
    return ch;
}

int str::suitToIndex(char &suitType)
{
    switch(suitType)
    {
        case 'S':
            return 0;
        case 'H':
            return 1;
        case 'D':
            return 2;
        case 'C':
            return 3;
    }
    return -1;
}


void str::printGame()
{
    cout << "Top List:" << endl << endl;

    cardList *ptr=topList;
    while(ptr!=NULL)
    {
        // all cards are visible in the toplist
        cout << ptr->color << ","<< ptr->suit << "," << ptr->number << " | ";//numberToCard(ptr->number) << " | ";
        ptr=ptr->next;
    }

    cout << endl << endl  << "Board Lists:" << endl << endl;
    //initialize pointer array to traverse in board lists
    cardList *temp[7];
    for(int i=0;i<7;i++)
    {
        cout << i+1 << ". list" << "\t";
        temp[i]=boardList[i];
    }
    cout << endl;

    int nullCount;  // keep the number of nulls in a row

    for(int j=0;j<13;j++)   // 13: max possible number of cards in a list (max rows)
    {
        nullCount=0;
        for(int i=0;i<7;i++)
        {
            if(temp[i]==NULL)
            {
                cout << "" << "\t";
                nullCount++;
            }
            else
                if(temp[i]->alignment==0)
                    cout << "X" << "\t";
                else
                    cout << temp[i]->color << ","<< temp[i]->suit << "," <<  temp[i]->number << "\t";//numberToCard(temp[i]->number) << "\t";

            if(temp[i]!=NULL) temp[i]=temp[i]->next;
        }
        if(nullCount==7) break;    // if all entries are zero in a row, stop printing list
        cout << endl;
    }

    cout << endl  << "Foundation Lists:" << endl << endl;
    const char *foundNameLst[4]= {"Spades","Hearts","Diamonds","Clubs"};
    cardList *tempFound[4];
    for(int i=0;i<4;i++)
    {
        cout << foundNameLst[i] << "   \t" ;
        tempFound[i]=foundationList[i];
    }
    cout << endl;

    int i;
    for(i=0;i<13;i++)
    {
        nullCount=0;
        for(int j=0;j<4;j++)
        {
            if(tempFound[j]==NULL)
            {
                cout <<"        \t";
                nullCount++;
            }
            else
                cout << tempFound[j]->color << ","<< tempFound[j]->suit << "," <<  tempFound[j]->number << "   \t";
            if(tempFound[j]!=NULL) tempFound[j]=tempFound[j]->next;
        }
        if(nullCount==4) break; // if a row is all null, break printing
        cout << endl;
    }

    // if no break occurs while printing foundation lists, it means all cards are collected
    if(i==12)
    {
        cout << endl << "--- You Win!! ---"<< endl;
        cin.ignore();
        getchar();
        return;
    }

    cout << endl << endl;
}

void str::clearLists(cardList *ptr)
{
    cardList *temp=ptr;
    while(temp!=NULL)
    {
        temp=ptr;
        if(temp==NULL) break;
        ptr=ptr->next;
        delete temp;
    }
}
#endif // STRUCTS_H_INCLUDED
