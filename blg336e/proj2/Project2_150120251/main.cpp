///
/// Blg336E Analysis of Algorithms 2 - Project 2
/// Cem Yusuf Aydoğdu
/// 150120251
///
#include "sequencealignment.h"
using namespace std;

int main()
{
    SequenceAlignment s;

    s.readFastaData("human-hemoglobin-sequence.fasta");
    s.readFastaData("mouse-hemoglobin-sequence.fasta");

    s.readSubstitutionMatrix("BLOSUM62.txt");

    s.alignSequences();

    return 0;
}
