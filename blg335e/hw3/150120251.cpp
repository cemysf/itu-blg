///
/// BLG335E - Project 3
/// Cem Yusuf Aydoğdu
/// 150120251
///

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

class dataArray
{
    int *array;
    const unsigned int size;

    public:
        // constructor - destructor
        dataArray(int _size) : size(_size) { array = new int[size]; }
        ~dataArray() { delete[] array; }

        // getters, setters, manipulators
        const unsigned int getSize() { return size; }
        int getElement(int index) { return array[index]; }
        void setElement(int index, int element) { array[index] = element; }
        void swap(int index1, int index2);

        // sorting algorithms
        void quickSort(int first, int last);
        void countingSort();
        void radixSort();

        // tools for sorting algorithms
        int partition(int first, int last);     // for quick sort
        int getDigit(int number, int digit);     //for radix sort

        // write to file for testing
        void writeToFile(string f_name);
};

void dataArray::swap(int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void dataArray::quickSort(int first, int last)
{
    int boundary;

    if(first<last)
    {
        boundary = partition(first,last);
        quickSort(first, boundary-1);
        quickSort((boundary+1),last);
    }
}

int dataArray::partition(int first, int last)
{
    int pivot = getElement(last);
    int boundary = first;

    for(int i=first; i<last; i++)
    {
        if(getElement(i) < pivot)
        {
            swap(i, boundary);
            boundary += 1;
        }
    }
    swap(boundary,last);
    return boundary;
}

void dataArray::countingSort()
{
    unsigned int i, n = getSize();
    int *temp = new int[n];

    // find largest element
    int max=0;
    for(i=0;i<n;i++)
    {
        if(array[i]>max)
            max=array[i];
    }

    // initialize histogram with zeroes
    int *counts = new int[max+1];
    for(int i=0;i<max+1;i++)
    {
        counts[i]=0;
    }

    // histogram calculation
    for(i=0;i<n;i++)
    {
        counts[array[i]] += 1;
    }

    // cumulative sum
    for(int i=1;i<max+1;i++)
    {
        counts[i] += counts[i-1];
    }

    // sorting
    for(i=0;i<n;i++)
    {
        counts[array[i]] -= 1;
        temp[counts[array[i]]]  = array[i];
    }

    // copy
    memcpy(array,temp, n*sizeof(int));

    delete[] temp;
    delete[] counts;
}

void dataArray::radixSort()
{
    int n=getSize(), i;
    int *temp = new int[n];

    // find largest element
    int max=0;
    for(i=0;i<n;i++)
    {
        if(array[i]>max)
            max=array[i];
    }

    // find number of binary digits
    int shift=max, digit=0;
    while( shift>0 )
    {
        shift = shift >> 1;     // right shift until 0
        digit++;
    }

    for(int d=0; d<digit; d++)
    {
        // initialize histogram with zeroes
        unsigned long long counts[] = {0,0};       //histogram only counts 0s and 1s

        // histogram calculation
        for(i=0;i<n;i++)
        {
            counts[ getDigit(array[i],d) ] += 1;
        }

        // cumulative sum
        counts[1] += counts[0];

        // sorting
        for(i=n-1; i>=0; i--)
        {
            counts[ getDigit(array[i],d) ] -= 1;
            temp[counts[ getDigit(array[i],d)]]  = array[i];
        }

        // copy sorted numbers
        memcpy(array,temp, n*sizeof(int));
    }

    delete[] temp;
}


// get the value of a digit, from the number
int dataArray::getDigit(int number, int digit)
{
    int mask = 1;

    // shift the mask bit to correct position
    while(--digit >= 0)
        mask = mask << 1;  // left shift mask

    if((number & mask) == 0)    // if the corresponding bit is 0, return 0
        return 0;
    else
        return 1;
}

void dataArray::writeToFile(string f_name)
{
    ofstream file_out(f_name.c_str(), ofstream::out);
    for(unsigned int i=0; i<size; i++)
    {
        file_out << array[i] << endl;
    }
    file_out.close();

}

int main(int argc, char **argv)
{
    if(argc!=3)
    {
        cout << "(ERROR) usage: ./<student_ID> <algorithm_type> <input_file>" << endl;
        return -1;
    }

    //read file
    string filename = "data/";
    filename += argv[2];

    ifstream file_in(filename.c_str(), ios::in);
    if(!file_in.is_open ())
    {
        cout << "File error: cannot open " << filename <<endl;
        return -2;
    }

    // determine the size
    int size=0;
    string line;
    while(getline(file_in,line))
        size++;

    // rewind the file
    file_in.clear();
    file_in.seekg(0, ios::beg);


    // read numbers
    int temp;
    dataArray array(size);
    for(int i=0;i<size;i++)
    {
        file_in >> temp;
        array.setElement(i,temp);
    }

    file_in.close();

    clock_t time;
    switch(*argv[1]){
        case 'q':case 'Q':
            cout << "Quick Sort for " << argv[2] <<endl;
            time = clock();
            array.quickSort(0, array.getSize()-1);
            time = clock() - time;
            break;
        case 'c':case 'C':
            cout << "Counting Sort for " << argv[2] <<endl;
            time = clock();
            array.countingSort();
            time = clock() - time;
            break;
        case 'r':case 'R':
            cout << "Radix Sort for " << argv[2] <<endl;
            time = clock();
            array.radixSort();
            time = clock() - time;
            break;

        default:
            cout << "(ERROR) wrong algorithm" << endl;
            return -3;
    }

    // write to file for testing
    // output filename: SORTED_<sorting_alg>_<input_filename>.txt
/*
    string output_fname = "SORTED_";
    output_fname += argv[1];
    output_fname += "_";
    output_fname += argv[2];
    array.writeToFile(output_fname);
*/

    //write to screen for testing
//    for(int i=0; i<array.getSize(); i++)
//        cout << array.getElement(i) << endl;

    cout << time << " ticks, " << ((float)time)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}
