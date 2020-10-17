#ifndef POLINOM_H
#define POLINOM_H
#include "ifade.h"
class Polinom : public Ifade
{
    int us;
public:
    Polinom(int _us, double _katsayi) : Ifade(_katsayi), us(_us) {}
    Ifade* turev();
    Ifade* integral();
    std::string ifade_icerik();
};

#endif // POLINOM_H
