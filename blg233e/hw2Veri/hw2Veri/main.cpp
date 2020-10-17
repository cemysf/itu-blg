#include <iostream>
#include <cstring>
using namespace std;

typedef struct node
{
    string nucleoBase;
    node *next;

    //node *initialize(string str);

}NucleicAcid;

NucleicAcid *initialize(string str)
{
    NucleicAcid *head=NULL;
    NucleicAcid *prev=NULL;
    //NucleicAcid *newnode = new node;

    for(size_t i=0;i<str.size();i++)
    {

        NucleicAcid *newnode=new NucleicAcid;
        if(i==0)
        {
            head=newnode;
            prev=newnode;
        }
        else prev->next=newnode;

        newnode->nucleoBase=str[i];
        newnode->next=NULL;

    }

    return head;
}

void deleteNucleicAcid(NucleicAcid *ptr)
{
    NucleicAcid *next = ptr->next;

    while(next!=NULL)
    {
        delete ptr;
        ptr = next;
        next=next->next;
    }

}


int main()
{
    NucleicAcid *rna1=initialize("ATGCAT");

//    string str= "asdasda";
//    for(size_t i=0;i<str.length();i++)
//    {
//        cout << str[i] << endl;
//
//    }

    //cout << rna1->nucleoBase ;

    deleteNucleicAcid(rna1);

}

