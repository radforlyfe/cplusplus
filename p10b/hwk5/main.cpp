//  main.cpp
//  Assignment5

#include<iostream>
#include<string>
#include "Complex.h"

int main() {
    Complex u(2,3);
    Complex v(1,1);
    std::cout << v["real"]<< " " << v["imag"] << std::endl;
    v += u;
    std::cout << v["real"]<< " " << v["imag"] << std::endl;
    Complex c = u + v;
    std::cout << c["real"] << " " << c["imag"] << std::endl;
    Complex d = c - v;
    std::cout << d["real"] << " " << d["imag"] << std::endl;
    Complex b = ~v;
    std::cout << b["real"]<< " " << b["imag"] << std::endl;
}
