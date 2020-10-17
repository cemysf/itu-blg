#ifndef DENKLEM_H
#define DENKLEM_H
#include <vector>
#include "ifade.h"
using namespace std;

class Denklem
{
    vector<Ifade*> ifadeler;
public:
    Denklem(vector<Ifade*> ifd) : ifadeler(ifd) {}
    Denklem turev();
    Denklem integral(int c);
    void bastir();
};

#endif // DENKLEM_H
