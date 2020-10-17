#include "denklem.h"
#include <iostream>
#include "polinom.h"
Denklem Denklem::turev()
{
    vector<Ifade*> ifd;
    for(vector<Ifade*>::iterator it=ifadeler.begin(); it!= ifadeler.end(); it++)
    {
        ifd.push_back((*it)->turev());
    }
    return Denklem(ifd);
}

Denklem Denklem::integral(int c)
{
    vector<Ifade*> ifd;
    for(vector<Ifade*>::iterator it=ifadeler.begin(); it!= ifadeler.end(); it++)
    {
        ifd.push_back((*it)->integral());
    }
    ifd.push_back(new Polinom(0, c));
    return Denklem(ifd);
}

void Denklem::bastir()
{
    for(vector<Ifade*>::iterator it=ifadeler.begin(); it!= ifadeler.end(); it++)
    {
        (*it)->bastir();
    }
    std::cout << std::endl;
}
