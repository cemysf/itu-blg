#include "polinom.h"
#include <sstream>

Ifade *Polinom::turev()
{
    return new Polinom(us - 1, katsayi * us);
}

Ifade *Polinom::integral()
{
    return new Polinom(us + 1, katsayi / us);
}

std::string Polinom::ifade_icerik()
{
    std::stringstream s;
    s << "x^" << us;
    return s.str();
}
