/*
* @Author
* Student Name: Cem Yusuf Aydoğdu
* Student ID : 150120251
* Date: 18.09.2014
*/

#ifndef FACULTYRECORD_STR   //#include guard
#define FACULTYRECORD_STR

#define NAME_LEN 15
#define DEPT_LEN 5

struct faculty_record
{
	char fname[NAME_LEN],lname[NAME_LEN];
	int phone,office;
	char dept[DEPT_LEN];
};

#endif
