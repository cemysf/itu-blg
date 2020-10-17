#ifndef IFADE_H
#define IFADE_H

#include <string>

class Ifade     //abstract class
{
protected:
    double katsayi;
    virtual std::string ifade_icerik()=0;
    Ifade(double _katsayi) : katsayi(_katsayi) { }
public:
    virtual Ifade* turev() =0;
    virtual Ifade* integral() =0;
    void bastir();
};

#endif // IFADE_H
