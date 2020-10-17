///
/// Blg336E Analysis of Algorithms 2 - Project 2
/// Cem Yusuf Aydoğdu
/// 150120251
///
#include "sequencealignment.h"
using namespace std;

SequenceAlignment::SequenceAlignment()
{
    sequences[0] = NULL;
    sequences[1] = NULL;
    subsMatrix = NULL;
    scoreMatrix = NULL;
}

SequenceAlignment::~SequenceAlignment()
{
    if(scoreMatrix != NULL)
    {
        for(int i=0; i<sequences[1]->seq.length()+1; i++)
        {
            delete scoreMatrix[i];
        }
        delete scoreMatrix;
    }

    if(sequences[0] != NULL)
    {
        delete sequences[0];
    }
    if(sequences[1] != NULL)
    {
        delete sequences[1];
    }
    if(subsMatrix != NULL)
        delete subsMatrix;
}


void SequenceAlignment::readFastaData(string filename)
{
    ifstream file(filename.c_str(), ios::in);
    if(!file.is_open())
    {
        cout << "File error: cannot open " << filename << endl;
        return;
    }

    Fasta *data = new Fasta;


    string line;
    char commentChar = '>';

    // Read the sequence
    while(getline(file,line))
    {
        // Read first line as info, if it starts with '>'
        if(strncmp(&line.c_str()[0],&commentChar,1) == 0)
        {
            data->info = line;
            continue;
        }
        data->seq += line;
    }

    if(sequences[0]==NULL)
        sequences[0] = data;
    else
        sequences[1] = data;
}


void SequenceAlignment::readSubstitutionMatrix(string filename)
{
    ifstream file(filename.c_str(), ios::in);
    if(!file.is_open())
    {
        cout << "File error: cannot open " << filename << endl;
        return;
    }

    subsMatrix = new SubstitutionMatrix;

    string line;
    // First, get characters in matrix to a vector
    const char commentChar = '#';
    while(getline(file,line))
    {
        // Pass comments
        if(strncmp(&line.c_str()[0], &commentChar,1) == 0)
            continue;
        else
        {
            // First line after comments contains chars (A,R,N...)
            string temp;
            stringstream ss(line);
            while(ss >> temp)
            {
                subsMatrix->chars.push_back(temp.c_str()[0]);
            }

            break;
        }
    }


    int offset = 0;
    int line_counter = 0;
    int diagonal_skipCount = 0;
    int value;
    while(getline(file,line))
    {
        string temp;
        stringstream ss(line);

        // Skip the first value (it is char)
        ss >> temp;

        // Skip values before diagonal in order to decrease redundancy
        for(int i=0; i<diagonal_skipCount; i++)
        {
            ss >> temp;
        }
        offset=line_counter;

        // Parse each line, get values
        while(ss >> temp)
        {
            // Map values
            char key1 = subsMatrix->chars[line_counter];
            char key2 = subsMatrix->chars[offset];
            value = atoi(temp.c_str());

            subsMatrix->valueMap.insert(make_pair(make_pair(key1, key2), value));

            offset++;
        }

        diagonal_skipCount++;
        line_counter++;
    }
}

void SequenceAlignment::alignSequences()
{
    // Adding gap to start of each sequences for algorithm
    string str1("*");
    str1 += sequences[0]->seq;

    string str2("*");
    str2 += sequences[1]->seq;

    // Initialize scoring matrix
    // First sequence as columns, second as rows
    scoreMatrix = new int*[str2.length()];
    for(int i=0; i<str2.length(); i++)
        scoreMatrix[i] = new int[str1.length()];

    for(int i=0; i<str2.length(); i++)
    {
        for(int j=0; j<str1.length(); j++)
        {
            scoreMatrix[i][j] = 0;
        }
    }

    // Initialize first row, first column
    scoreMatrix[0][0] = subsMatrix->getValue('*','*');
    scoreMatrix[0][1] = subsMatrix->getValue(str1[1],'*');
    scoreMatrix[1][0] = subsMatrix->getValue(str2[1],'*');

    for(int i=2; i<str1.length(); i++)
        scoreMatrix[0][i] = scoreMatrix[0][i-1] + subsMatrix->getValue(str1[i],'*');

    for(int i=2; i<str2.length(); i++)
        scoreMatrix[i][0] = scoreMatrix[i-1][0] + subsMatrix->getValue(str2[i],'*');


    // Calculate scores
    int max_score;
    int upperLeft, left, up;
    for(int i=1; i<str2.length(); i++)
    {
        for(int j=1; j<str1.length(); j++)
        {
            max_score = 0;

            // From upper left, score of upper left cell + match/mismatch score of current cell
            if(strncmp(&str1[j],&str2[i],1)==0)
                max_score = upperLeft = scoreMatrix[i-1][j-1] + subsMatrix->getValue(str1[j], str2[i]);

            // From left, score of left cell + gap penalty
            left = scoreMatrix[i][j-1] + subsMatrix->getValue(str2[i], '*');
            if(left > max_score)
                max_score = left;

            // From up, score of up cell + gap penalty
            up = scoreMatrix[i-1][j] + subsMatrix->getValue(str1[j], '*');
            if(up > max_score)
                max_score = up;

            scoreMatrix[i][j] = max_score;

        }
    }


    // Delete the '*' char in front of both sequences
    str1 = str1.substr(1, str1.length());
    str2 = str2.substr(1, str1.length());

    // Backtrack
    string seq1, seq2;
    int j=str1.length(), i=str2.length(), upperLeft_val, totalScore = 0;
    while(i>0 && j>0)
    {

        // If the current score is from upper left cell
        upperLeft_val = subsMatrix->getValue(str1[j-1], str2[i-1]);
        if(i>0 && j>0 && (scoreMatrix[i][j] == scoreMatrix[i-1][j-1] + upperLeft_val))
        {
            totalScore += scoreMatrix[i][j];
            seq1 = str1[j-1] + seq1;
            seq2 = str2[i-1] + seq2;
            i--;
            j--;
        }
        // If the current score is from left cell (means there is a gap)
        else if(j>0 && (scoreMatrix [i][j] == scoreMatrix[i][j-1] + subsMatrix->getValue(str2[i-1], '*')))
        {
            totalScore += scoreMatrix[i][j];
            seq1 = str1[j-1] + seq1;
            seq2 = "-" + seq2;
            j--;
        }
        // If the current score is from upper cell (means there is a gap)
        else
        {
            totalScore += scoreMatrix[i][j];
            seq1 = "-" + seq1;
            seq2 = str2[i-1] + seq2;
            i--;
        }
    }

    // Calculate alignment metrics
    int final_len = seq1.length();
    int identity = 0, similarity = 0, gap = 0;
    string temp;
    for(int i=seq1.length()-1; i>=0; i--)
    {
        // Exact matches
        if(strncmp(&seq1[i],&seq2[i],1)==0)
        {
            temp = "|" + temp;
            identity++;
        }

        // Not matching but score in BLOSUM file > 0
        else if(subsMatrix->getValue(seq1[i], seq2[i]) > 0)
        {
            temp = ":" + temp;
            similarity++;
        }

        // If there is a gap
        else if(subsMatrix->getValue(seq1[i], seq2[i]) ==  numeric_limits<int>::min())
        {
            gap++;
            temp = "." +temp;
        }
        // If scoring between two characters below zero
        else
        {
            temp = "." + temp;
        }
    }
    similarity += identity;



    // Print the output to the screen

    int printSize = 50;

    cout << string(printSize+35, '#') << endl;
    cout << "#" << endl;
    cout << "# Length:\t" << final_len << " (with gaps)" << endl;
    cout << "# Identity:\t" << identity << "/" << final_len << " (" << float(float(identity)/float(final_len)) << "%) (\"|\")" << endl;
    cout << "# Similarity:\t" << similarity << "/" << final_len << " (" << float(float(similarity)/float(final_len)) << "%) (\"|\" and \":\")" << endl;
    cout << "# Gaps:\t\t" << gap << "/" << final_len << " (" << float(float(gap)/float(final_len)) << "%)" << endl;
    cout << "# Score:\t" << totalScore << endl;
    cout << "#" << endl;
    cout << "#" << endl;
    cout << "#" << string(printSize+35, '#') << endl;
    cout << endl;

    int start=1, end;
    if(printSize>final_len)
        end = final_len;
    else
        end = printSize;
    for(int i = 0; i< ceil(float(float(final_len)/float(printSize))); i++)
    {

        cout << "human\t\t " << start << "\t" << seq1.substr(start-1,end-start+1) << "\t" << end << endl;
        cout << "     \t\t " << "\t" << temp.substr(start-1,end-start+1) << endl;
        cout << "mouse\t\t " << start << "\t" << seq2.substr(start-1,end-start+1) << "\t" << end << endl;
        cout << endl;

        start = end+1;

        if(end + printSize > final_len)
            end = final_len;
        else
            end += printSize;
    }
    cout << endl;
    cout << string(printSize+35, '#') << endl;

}
