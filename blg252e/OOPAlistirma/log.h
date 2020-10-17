#ifndef LOG_H
#define LOG_H
#include "ifade.h"

class Log : public Ifade
{
    int taban, sayi;
public:
    Log(double _katsayi, int _taban, int_sayi): Ifade(_katsayi), taban(_taban), sayi(_sayi) {}
    Ifade* turev();
    Ifade* integral();
};

#endif // LOG_H
