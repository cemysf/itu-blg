/*
* @Author
* Student Name: Cem Yusuf Aydoðdu
* Student ID : 150120251
* Date: 04.05.2015
*/

#ifndef TRIP_H_INCLUDED
#define TRIP_H_INCLUDED
#include <iostream>
#include <string>

#define MAX_DISCOUNT 50

using namespace std;

// Parent class for flight and cruise
class Carrier{
    protected:
        string path;
        float cost;
    public:
        Carrier() { }
        Carrier(string path_val, float cost_val) { path = path_val; cost = cost_val; }

        float getCost() { return cost; }
        void setCost(float newCost) { cost = newCost; }

        string getPath() { return path; }
        void setPath(string newPath) { path = newPath; }
};


template <class Type>
class Trip{
    int counter,discount;
    Type **ptr_arr;

    public:

            /// constructors
        Trip() { ptr_arr=NULL; discount=0; }
        Trip(Type &t);
        Trip(Type *t, int number);

            /// member functions
        void add(Type &t);
        void setDiscount(const int &newDiscount);

            /// operator overloads
        friend ostream& operator<<(ostream &out, Trip<Type> &t)
        {
            out << "***********************" << endl;
            out << "Trip transfer count:" << t.counter << endl;

            for(int i=0;i<t.counter;i++)
            {
                cout << i+1 << ":";
                (t.ptr_arr[i])->print();
            }
            out << "***********************" << endl;

            float totalCost=0;
            for(int i=0;i<t.counter;i++)
                totalCost += (t.ptr_arr[i])->getCost();

            out << "Trip total cost:" << totalCost << endl;
            if(t.discount != 0)
            {
                out << "Discount:%" << t.discount << endl;
                out << "Discount amount:-" << (totalCost * t.discount)/100  << endl;
                out << "Discounted cost:" << totalCost - (totalCost * t.discount)/100  << endl;
            }
            out << "***********************" << endl;

            return out;
        }

        Type & operator[](const int index)
        {
            if(index>=counter) throw string("Index out of bounds!");
            else return *ptr_arr[index];
        }

        void operator+=(Trip &t)
        {
            Type **newArr = new Type*[counter + t.counter];
            for(int i=0;i<(counter + t.counter) ;i++)
            {
                if(i<counter)
                    newArr[i] = ptr_arr[i];
                else
                    newArr[i] =  t.ptr_arr[i-counter];

            }

            Type **temp = ptr_arr;
            delete[] temp;
            ptr_arr = newArr;

            counter += t.counter;
        }

};

template <class Type>
Trip<Type>::Trip(Type &t)
{
    discount = 0;
    counter = 1;
    ptr_arr = new Type*;
    ptr_arr[0] = &t;
}

template <class Type>
Trip<Type>::Trip(Type *t, int number)
{
    discount = 0;
    counter = number;
    ptr_arr = new Type*[number];

    for(int i=0;i<number;i++)
    {
        ptr_arr[i] = &t[i];
    }
}

template <class Type>
void Trip<Type>::add(Type &t)
{
    //allocate new array with one more size, copy current contents
    Type **newArr = new Type*[counter+1];
    for(int i=0;i<counter;i++)
    {
        newArr[i] = ptr_arr[i];
    }
    newArr[counter] = &t;

    //delete old array and assign new array
    Type **temp = ptr_arr;
    delete[] temp;
    ptr_arr = newArr;

    counter += 1;
}


template <class Type>
void Trip<Type>::setDiscount(const int &newDiscount)
{
    if(newDiscount >= MAX_DISCOUNT) throw string("Discount out of range!");
    else discount = newDiscount;
}

#endif // TRIP_H_INCLUDED
