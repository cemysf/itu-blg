///
/// Blg336E Analysis of Algorithms 2 - Project 2
/// Cem Yusuf Aydoğdu
/// 150120251
///
#ifndef SEQUENCEALIGNMENT_H
#define SEQUENCEALIGNMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <map>
#include <cmath>
#include <limits>

using namespace std;

typedef struct
{
    string info;
    string seq;
}Fasta;



typedef pair<char,char> key;

typedef struct
{
    map<key, int> valueMap;
    vector<char> chars;


    // Returns a score
    int getValue(char key1, char key2)
    {
        // Search the key in map
        map<key, int>::const_iterator it;
        it = valueMap.find(make_pair(key1,key2));
        if(it == valueMap.end())
        {
            // If not found, reverse keys and try again
            it = valueMap.find(make_pair(key2,key1));

            // If the value is still not found, it does not exist
            if(it == valueMap.end())
                return numeric_limits<int>::min();
        }
        return it->second;
    }

}SubstitutionMatrix;


class SequenceAlignment
{
    Fasta *sequences[2];                // Comparing only two fasta sequences
    int **scoreMatrix;                  // For dynamic programming
    SubstitutionMatrix *subsMatrix;     // Reading from BLOSUM62 file

public:
    SequenceAlignment();
    ~SequenceAlignment();
    void readFastaData(string filename);
    void readSubstitutionMatrix(string filename);

    // Needleman-Wunsch algorithm to align sequences
    void alignSequences();
};

#endif // SEQUENCEALIGNMENT_H
