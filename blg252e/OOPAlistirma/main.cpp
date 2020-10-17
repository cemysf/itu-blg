#include <iostream>
#include "denklem.h"
#include "polinom.h"
using namespace std;

int main()
{
    vector<Ifade*> ifd;
    ifd.push_back(new Polinom(2, 3));
    ifd.push_back(new Polinom(4,1));
    ifd.push_back(new Polinom(0, 2));
    Denklem d(ifd);
    d.bastir();
    d.turev().bastir();
    return 0;
}

