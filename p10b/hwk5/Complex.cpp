//  Complex.cpp
//  Assignment5

#include "Complex.h"

const double& Complex::operator[](std::string str) const{
    if(str == "real")
        return real_;
    if(str == "imag")
        return imag_;
    else
        throw std::out_of_range("invalid index: XXX ");
}

double& Complex::operator[](std::string str){
    if(str == "real")
        return real_;
    if(str == "imag")
        return imag_;
    else
        throw std::out_of_range("invalid index: XXX ");
}

Complex operator+(Complex lhs, const Complex& rhs)
{
    lhs["real"] += rhs["real"];
    lhs["imag"] += rhs["imag"];
    return lhs;
}

Complex operator-(Complex lhs, const Complex& rhs)
{
    lhs["real"] -= rhs["real"];
    lhs["imag"] -= rhs["imag"];
    return lhs;
}

Complex operator*(Complex lhs, const Complex& rhs)
{
    lhs["real"] *= rhs["real"];
    lhs["imag"] *= rhs["imag"];
    return lhs;
}

Complex operator/(Complex lhs, const Complex& rhs)
{
    lhs["real"] /= rhs["real"];
    lhs["imag"] /= rhs["imag"];
    return lhs;
}
