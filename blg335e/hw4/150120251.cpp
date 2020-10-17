/// BLG335E Prj 4
/// Cem Yusuf Aydoğdu
/// 150120251
///
/// Note:
/// 1) Hashing type is determined from command line
///
///     ./150120251 <hash_type>
///
///     <hash_type>: { l | d | q }  (linear, double, quadratic)
///
///     ex: ./150120251 l
///

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

#define HASHTABLE_SIZE 2477

///
/// HashTable classes with required data types and functions
///
struct HashNode{
    int value;
    int isDeleted:1;
};

class HashTable
{
    protected:
        HashNode *table;
        int totalCollisions;
        int totalDeleted;

    public:
        HashTable()
        {
            table = new HashNode[HASHTABLE_SIZE];   //key is table[index].value, calculated hash value is index
            for(unsigned int i=0; i<HASHTABLE_SIZE; i++)
            {
                table[i].value=0;
                table[i].isDeleted=0;
            }
            totalCollisions=0;
            totalDeleted=0;
        }

        ~HashTable()
        {
            delete[] table;
        }

        int insert(const int key);
        int del(const int key) ;
        int retrieve(const int key);

        // polymorphism used for hash calculation and printing number of collisions
        virtual int calculateHashValue(const int key, const int i) {}
        virtual void printCollisions() {}

};

int HashTable::insert(const int key)
{
    unsigned int i=0;
    unsigned int hashValue = calculateHashValue(key,i);
    unsigned int numberOfTrials = 0;

    // While the corresponding place is occupied and not marked as empty, look for the next avaible location
    while(table[hashValue].value != 0 && table[hashValue].isDeleted == 0 )
    {
        i += 1;
        hashValue = calculateHashValue(key,i);

        // if number of trials exceeds size of hash table, there is no space avaible
        numberOfTrials += 1;
        if(numberOfTrials > HASHTABLE_SIZE )
            return -1;
    }

    // After finding avaible location, write the value and number of tries
    table[hashValue].value = key;
    table[hashValue].isDeleted = 0;

    // Add number of collisions in this operation, to total sum
    this->totalCollisions += i;

    // Return the index
    return hashValue;
}

int HashTable::del(const int key)
{
    int index = retrieve(key);

    // return -1 (failure) if the key is not in the table
    if(index == -1)
        return -1;

    table[index].isDeleted = 1;
    totalDeleted += 1;

    return 0;
}

int HashTable::retrieve(const int key)
{
    unsigned int i=0;
    unsigned int hashValue = calculateHashValue(key,i);
    unsigned int numberOfTrials = 0;

    while( table[hashValue].value != key && hashValue < HASHTABLE_SIZE)
    {
        i += 1;
        hashValue = calculateHashValue(key,i);

        // if number of trials exceeds size of hash table, the value is not in the table
        numberOfTrials += 1;
        if(numberOfTrials > HASHTABLE_SIZE )
            return -1;
    }
    return hashValue;
}

//
// Polymorphic hash calculation and printing functions for derived classes
//
class HashTable_LinearProb : public HashTable
{
    int calculateHashValue(const int key, const int i)
    {
        return ((key+i) % HASHTABLE_SIZE);
    }

    public:
        void printCollisions()
        {
            cout << endl << "Linear Probing: " << totalCollisions << " collusions have been occurred" << endl;
        }
};

class HashTable_DoubleHashing : public HashTable
{
    int calculateHashValue(const int key, const int i)
    {
        int hash1 = key % HASHTABLE_SIZE;
        int hash2 = 1 + (key%(HASHTABLE_SIZE - 4));
        return ((hash1 + i*hash2) % HASHTABLE_SIZE);
    }

    public:
        void printCollisions()
        {
            cout << endl << "Double Hashing: " << totalCollisions << " collusions have been occurred" << endl;
        }
};

class HashTable_QuadraticHashing : public HashTable
{
    int calculateHashValue(const int key, const int i)
    {
        int hash1 = key % HASHTABLE_SIZE;
        return ((hash1 + i + 2*i*i) % HASHTABLE_SIZE);
    }

    public:
        void printCollisions()
        {
            cout << endl << "Quadratic Hashing: " << totalCollisions << " collusions have been occurred" << endl;
        }
};



int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "Usage: ./executable <hashing_type> " << endl;
        cout << "<hash_type>: { l | d | q }  (linear, double, quadratic)" << endl;
        return -1;
    }

    HashTable *hashtable;
    // Initialize required class
    char options[] = {'l','d','q'};
    if(strncmp(argv[1], &options[0],1)==0)
    {
        cout << "Using linear probing, hash table size is ";
        hashtable = new HashTable_LinearProb;
    }
    else if(strncmp(argv[1], &options[1],1)==0)
    {
        cout << "Using double hashing, hash table size is ";
        hashtable = new HashTable_DoubleHashing;
    }
    else if(strncmp(argv[1], &options[2],1)==0)
    {
        cout << "Using quadratic hashing, hash table size is ";
        hashtable = new HashTable_QuadraticHashing;
    }
    else
    {
        cout << "(ERROR): Wrong hashing type option." << endl;
        return -2;
    }
    cout << HASHTABLE_SIZE << endl << endl;


    // Open the file and read line by line
    string filename = "dataset.txt";
    ifstream file_stream(filename.c_str(), ios::in);
    if(!file_stream.is_open ())
    {
        cout << "File error." << endl;
        return -3;
    }

    // Call required functions for each line
    const char *delimiter = ":";
    string line, operation_string, key_string;
    int retval;

    while(getline(file_stream,line))
    {
        // Split the line into two strings
        operation_string = line.substr(0, line.find(delimiter));
        key_string = line.substr(line.find(delimiter)+1, strlen(line.c_str()));

        if(operation_string.compare(string("insert"))==0)
        {
            retval = hashtable->insert(atoi(key_string.c_str()));

            if(retval == -1)
                cout << "Insertion: Key: " << key_string << " could not inserted to table (table is full)." << endl;
            else
                cout << "Insertion: Key " << key_string << " is inserted in index " << retval <<  "." << endl;

            continue;
        }

        if(operation_string.compare(string("delete"))==0)
        {
            retval = hashtable->del(atoi(key_string.c_str()));

            if(retval == -1)
                cout << "Deletion: Key: " << key_string << " could not deleted from table (key not found)." << endl;
            else
                cout << "Deletion: Key " << key_string << " is deleted from the table." << endl;

            continue;
        }

        if(operation_string.compare(string("retrieve"))==0)
        {
            retval = hashtable->retrieve(atoi(key_string.c_str()));

            if(retval == -1)
                cout << "Retrieve: Key " << key_string << " is not found in the table." << endl;
            else
                cout << "Retrieve: Key " << key_string << " is found at index " << retval << "." << endl;
        }
    }

    // Print the number of collisions and end the program
    hashtable->printCollisions();
    delete hashtable;

    return 0;
}

