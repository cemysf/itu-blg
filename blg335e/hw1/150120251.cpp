#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
using namespace std;

class dataArray
{
    int *array;
    const int size;

    public:
        dataArray(int &_size) : size(_size) { array = new int[size]; }
        ~dataArray() { delete[] array; }
        const int getSize() { return size; }
        int getElement(int index) { return array[index]; }
        void setElement(int index, int element) { array[index] = element; }
        void swap(int index1, int index2);
};

void dataArray::swap(int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}


void bubbleSort(dataArray *array);
void mergeSort(dataArray *array, int p, int r);
void merge(dataArray *array, int p, int q, int r);

int main(int argc, char **argv)
{
    if(argc!=3)
    {
        cout << "Invalid command line args.." << endl;
        return -1;
    }

    ifstream file_in("data.txt", ios::in);
    if(!file_in.is_open ())
    {
        cout << "File error" << endl;
        return -1;
    }

    int size = atoi(argv[2]), i, temp;
    dataArray array(size);
    for(i=0; i<size; i++)
    {
        file_in >> temp;
        array.setElement(i, temp);
    }
    file_in.close();
    cout << "Read " << i << " numbers from input file." << endl << endl;


    const char *b="b", *m="m";
    if( strcmp(argv[1], b) == 0)       //b
    {
        cout << "Bubble Sort" << endl;
        bubbleSort (&array);

    }
    else if ( strcmp(argv[1], m) == 0)    //m
    {
        cout << "Merge Sort" << endl;

        clock_t time = clock();

        mergeSort(&array, 0, size-1);

        time = clock() - time;
        cout << time << " ticks, " << ((float)time)/CLOCKS_PER_SEC << " seconds" << endl << endl;

    }
    else
    {
        cout << "Invalid sorting option" << endl;
        return -1;
    }

    ofstream file_out("sorted.txt", ofstream::out);
    for(i=0; i< array.getSize(); i++)
    {
        file_out << array.getElement(i) << endl;
    }
    cout << "File output completed for " << i << " numbers" << endl;
    file_out.close();

    return 0;
}


void bubbleSort(dataArray *array)
{
    clock_t time = clock();

    int i,j;
    for(i=0; i < array->getSize(); i++)
    {
        for(j=array->getSize()-1; j>= i+1; j--)
        {
            if(array->getElement(j) < array->getElement(j-1))
            {
                array->swap(j, j-1);
            }
        }
    }

    time = clock() - time;
    cout << time << " ticks, " << ((float)time)/CLOCKS_PER_SEC << " seconds" << endl << endl;
}


void mergeSort (dataArray *array, int p, int r)
{
    int q;
    if (p < r)
    {
        q = (int)floor((p+r)/2);
        mergeSort (array, p, q);
        mergeSort (array, q+1, r);
        merge(array, p, q, r);
    }
}

void merge(dataArray *array, int p, int q, int r)
{
    int n1=q-p+1, n2=r-q;
    int Left[n1+1], Right[n2+1];

    int i,j,k;
    for(i=0; i<n1; i++)
    {
        Left[i] = array->getElement(p+i);
    }

    for(j=0; j<n2; j++)
    {
        Right[j] = array->getElement(q+j+1);
    }

    Left[n1] = numeric_limits<int>::max();
    Right[n2] = numeric_limits<int>::max();

    i=0;
    j=0;
    for(k=p; k< r; k++)
    {
        if( Left[i] <= Right[j])
        {
            array->setElement(k, Left[i]);
            i++;
        }
        else
        {
            array->setElement(k, Right[j]);
            j++;
        }
    }

    // append remaining elemens from Left and Right (if any exists)
    while(i< n1)
    {
        array->setElement(k, Left[i]);
        i++;
        k++;
    }

    while(j< n2)
    {
        array->setElement(k, Right[j]);
        j++;
        k++;
    }

}


