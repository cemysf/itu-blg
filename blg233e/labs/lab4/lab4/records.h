#ifndef RECORDS_H
#define RECORDS_H
#define NAME_LEN 30
#define TYPE_LEN 10
#define NUM_LEN 15

enum phoneType{HOME,MOBILE,WORK};

struct numberNode
{
	//enum phoneType type;
	char type[TYPE_LEN];
	char number[NUM_LEN];
	numberNode *next;
};

struct phoneNode{
	char name[NAME_LEN];
	numberNode *numb;
	phoneNode *next;
	phoneNode *prev;
};





#endif