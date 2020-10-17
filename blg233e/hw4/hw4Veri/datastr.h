#ifndef DATASTR_H_INCLUDED
#define DATASTR_H_INCLUDED

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

struct node
{
    string number,name,surname,dept;
    double gpa;
    node *next;
};

struct str
{
    node *head_stack, *head_tempstack;

    void initLists();
    void closeLists();

    bool readFromFile();
    bool writeToFile();

    // in order to change the value of head pointer, sending address of the head, therefore double pointer must be used
    void push(node **stackptr, node *student);
    node pop(node **stackptr);

    void arrange();     // sorting the list
    void print(node *head); //print to screen
};

void str::initLists()
{
    head_stack=NULL;
    head_tempstack=NULL;
}

void str::closeLists()
{
    while(head_stack!=NULL)
    {
        pop(&head_stack);
    }
    while(head_tempstack!=NULL)
    {
        pop(&head_tempstack);
    }
}

bool str::readFromFile()
{
    ifstream fp ("records.txt", ifstream::in);
    if(!fp.is_open())
    {
        cout << "File error while reading. Program will exit.." << endl;
        return false;
    }

    node *tempNode = new node;
    char line[50];
    fp.getline(line,50);
    while( !fp.eof() )
    {
        tempNode->number = strtok(line," ");
        tempNode->name = strtok(NULL," ");
        tempNode->name.append(" ");
        tempNode->name.append(strtok(NULL," "));
        tempNode->gpa = strtod(strtok(NULL," "),NULL);
        tempNode->dept = strtok(NULL, " ");
        push(&head_stack, tempNode);
        fp.getline(line,50);
    }
    fp.close();
    delete tempNode;
    return true;
}

bool str::writeToFile()
{
    ofstream fp ("sortedRecords.txt", ifstream::out);
    if(!fp.is_open())
    {
        cout << endl << "File error while writing. Program will exit.." << endl;
        return false;
    }

    node temp;
    while(head_tempstack!=NULL)
    {
        temp = pop(&head_tempstack);
        fp << temp.number << " " <<  temp.name << " " << temp.gpa << " " << temp.dept << endl;
    }
    fp.close();
    return true;
}

void str::push(node **stackptr, node *student)
{
    node *newnode = new node;
    newnode->next=*stackptr; //head of the given list
    *stackptr = newnode;

    newnode->dept = student->dept;
    newnode->gpa = student->gpa;
    newnode->name = student->name;
    newnode->number = student->number;
}

node str::pop(node **stackptr)
{
    node tempNode;
    tempNode.dept = (*stackptr)->dept;
    tempNode.gpa= (*stackptr)->gpa;
    tempNode.name= (*stackptr)->name;
    tempNode.number = (*stackptr)->number;

    node *nextptr = (*stackptr)->next;
    delete *stackptr;
    *stackptr = nextptr;

    return tempNode;
}

// arranged list will be at temporary stack
void str::arrange()
{
    node top_stack,top_tempstack;

    if(head_tempstack==NULL)                      // transfer first element to temporary stack without condition
    {
        top_stack = pop(&head_stack);             // pop the original stack
        push(&head_tempstack, &top_stack);       // push to temp stack
    }

    while(head_stack!=NULL)                      // execute until the original stack is empty
    {
        if( (head_stack->gpa <= head_tempstack->gpa) )  // if top of the original stack is lower than or equal to the top element of temp stack..
        {
            top_stack = pop(&head_stack);       // pop the original stack to a temp variable
            while(top_stack.gpa <= head_tempstack->gpa) // until the temp variable is greater than top of temp stack, transfer from temp stack to original stack
            {
                // check the equal gpa status
                if(top_stack.gpa == head_tempstack->gpa && strtoll(top_stack.number.c_str(),NULL,10) > strtoll(head_tempstack->number.c_str(),NULL,10))
                    break;

                top_tempstack = pop(&head_tempstack);
                push(&head_stack, &top_tempstack);
                if(head_tempstack==NULL) break;
            }
            push(&head_tempstack,&top_stack);   // push the temp variable from above, to temp stack

        }
        // if top of the original stack is higher than the top element of temp stack, just transfer it to temp stack
        top_stack=pop(&head_stack);
        push(&head_tempstack,&top_stack);
    }

}

void str::print(node *head)
{
    node *temp = head;
    while(temp!=NULL)
    {
        cout <<  temp->number << " " << temp->name << " " << temp->gpa << " " << temp->dept << endl;
        temp = temp->next;
    }

}

#endif // DATASTR_H_INCLUDED
