/*
* @Author
* Student Name: Cem Yusuf Aydogdu
* Student ID : 150120251
* Date: 13.10.2014
*/

/// Variable names like linkedList or initRna, are
/// assigned according to the given code snippet,
/// in order to control program faster.

#include <iostream>
#include <cstring>
#include <cstdarg>
#define NUMBER_OF_RNAS 5

using namespace std;

typedef struct node
{
    string nucleoBase;
    node *next;
}linkedList;

linkedList *initRna(const string str);
void printRnas(const linkedList *ptr, ...);
void printDna(const linkedList *ptr);

//for the function coupleDna
string controlRnas(linkedList *ptr1, linkedList *ptr2);
linkedList *coupleDna(linkedList *ptr,...);
void deletelinkedLists(int n, linkedList *ptr, ...);

int main()
{
    linkedList *rna1 = initRna("ATGATGATGC");
    linkedList *rna2 = initRna("TCGCGCTAGC");
    linkedList *rna3 = initRna("CGTCGTAAAC");
    linkedList *rna4 = initRna("TATTTACGAA");
    linkedList *rna5 = initRna("TACTACTACG");

    printRnas(rna1, rna2, rna3, rna4, rna5);

    linkedList *dna = coupleDna(rna1, rna2, rna3, rna4, rna5);
    printDna(dna);

    if(dna!=NULL)
        deletelinkedLists(NUMBER_OF_RNAS +1,rna1, rna2, rna3, rna4, rna5,dna);
    else
        deletelinkedLists(NUMBER_OF_RNAS,rna1, rna2, rna3, rna4, rna5);

}

linkedList *initRna(const string str)
{
    linkedList *head=NULL;
    linkedList *prev=NULL;

    for(size_t i=0;i<str.size();i++)
    {
        linkedList *newnode=new linkedList;
        if(i==0)
        {
            head=newnode;
            prev=newnode;
        }
        else
        {
            prev->next=newnode;
            prev=newnode;
        }
        newnode->nucleoBase=str[i];
        newnode->next=NULL;
    }

    return head;
}

string controlRnas(linkedList *ptr1, linkedList *ptr2)
{
    string str1,str2,str_out="";

    while(ptr1!=NULL)
    {
        str1=ptr1->nucleoBase;
        str2=ptr2->nucleoBase;

        //if two bases dont match, stop checking and return null string
        if (!((str1=="A" && str2=="T") || (str1=="T" && str2=="A") || (str1=="G" && str2=="C") || (str1=="C" && str2=="G")))
        {
            return "";
        }
        else
        {
            str_out = str_out + str1 + str2;
        }
        ptr1=ptr1->next;
        ptr2=ptr2->next;
    }
    //cout << "out: " << str_out << endl;
    return str_out;
}

linkedList *coupleDna(linkedList *ptr,...)
{
    //va_list to pointer array
    va_list argList;
    va_start(argList,ptr);
    linkedList *rnaList[NUMBER_OF_RNAS];
    for(int n=0;n<NUMBER_OF_RNAS;n++)
    {
        rnaList[n]=ptr;
        ptr=va_arg(argList, linkedList *);
    }
    va_end(argList);

    string dna_str = "";
    int i,j;

    //control rnas; if match found, stop the control
    for(i=0;i<NUMBER_OF_RNAS-1;i++)
    {
        for(j=i+1;j<NUMBER_OF_RNAS;j++)
        {
            dna_str=controlRnas(rnaList[i],rnaList[j]);

            //only two of them can match
            if(dna_str!="") break;
        }
        if(dna_str!="") break;
    }

    //initialize new dna
    linkedList *dna_ptr=NULL;
    linkedList *prev=NULL;

    if(dna_str=="")
        cout << "No match found." << endl;
    else
    {
        //cout <<"match: "<< i+1 << j+1 << endl;

        for(size_t k=0; k < dna_str.size(); k+=2)
        {
            linkedList *newnode=new linkedList;
            if(k==0)
            {
                dna_ptr=newnode;
                prev=newnode;
            }
            else
            {
                prev->next=newnode;
                prev=newnode;
            }

            newnode->nucleoBase=dna_str.substr(k,2);
            newnode->next=NULL;
        }
    }

    return dna_ptr;
}

void printRnas(const linkedList *ptr, ...)
{
    va_list argList;
    va_start(argList,ptr);

    int ctr=0;

    while(ctr < NUMBER_OF_RNAS)
    {
        cout << ++ctr << ": ";
        while(ptr != NULL)
        {
            cout << ptr->nucleoBase << " " ;
            ptr=ptr->next;
        }
        ptr=va_arg(argList,const linkedList *);
        cout << endl;
    }

    va_end(argList);
}

void printDna(const linkedList *ptr)
{
    cout << endl;
    while(ptr != NULL)
    {
        cout << ptr->nucleoBase << " " ;
        ptr=ptr->next;
    }
    cout << endl;
}

//n: number of pointers to this function
void deletelinkedLists(int n, linkedList *ptr, ...)
{
    va_list argList;
    va_start(argList,ptr);
    int counter=0;

    while(counter<n)
    {
        linkedList *next = ptr->next;
        while(ptr!=NULL)
        {
            delete ptr;
            ptr = next;
            if(next!=NULL) next=next->next;
        }

        counter++;
        ptr=va_arg(argList,linkedList *);
    }

    va_end(argList);
}
