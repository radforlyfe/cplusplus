//  Complex.cpp
//  Assignment5

#include "Complex.h"

const double& Complex::operator[](std::string str) const{
    if(str == "real")
        return real_;
    if(str == "imag")
        return imag_;
    else
        throw std::out_of_range("invalid index: XXX "); // fix XXXXXXXXXX --- 
}

double& Complex::operator[](std::string str){
    if(str == "real")
        return real_;
    if(str == "imag")
        return imag_;
    else
        throw std::out_of_range("invalid index: XXXX"); // fix XXX
}

std::ostream& operator<<(std::ostream& out, const Complex& c){
    if(c["real"] == 0 && c["imag"] > 0){
        out << c["imag"] << "i";
    }
    if(c["real"] == 0 && c["imag"] < 0){
        out << c["imag"] << "i";
    }
    if (c["imag"] == 0){
        out << c["real"];
    }
    if (c["real"] != 0 && c["imag"] == 1){
        out << c["real"] << "+i";
    }
    if (c["real"] != 0 && c["imag"] == -1){
        out << c["real"] << "-i";
    }
    if(c["real"] != 0 && c["imag"] > 0 && c["imag"] != 1){
        out << c["real"] << "+" << c["imag"] << "i";
    }
    else if (c["real"] != 0 && c["imag"] < 0 && c["imag"] != -1){
        out << c["real"] << c["imag"] << "i";
    }
    return out;
}

//std::istream& operator>>(std::istream& in, const Complex& c){
//    in >> c["real"] >> c["imag"];
//    if(in.fail())
//        throw std::runtime_error("bad inputs for reading");
//    return in;
//}
