//  Complex.cpp
//  Assignment5

#include "Complex.h"

Complex::Complex(std::string str){
    size_t minus_i = str.find("+i");
    while(minus_i != std::string::npos){
        str.replace(minus_i, 2, "-1i");
        minus_i = str.find("-i");
    }
    size_t plus_i = str.find("+i");
    while(plus_i != std::string::npos){
        str.replace(plus_i, 2, "+1i");
        plus_i = str.find("+i");
    }
    std::istringstream ss(str);
    double _real = 0, _imag = 0, _temp =0;
    while(!ss.eof()){
        ss >> _temp;
        if(ss.peek() == '+' || ss.peek() == '-'){
            _real += _temp;
            ss.get();
        }
        else if(ss.peek() == 'i'){
            _imag += _temp;
            ss.get();
        }
    }
    real_ = _real;
    imag_ = _imag;
}

Complex::operator std::string() const{
    std::ostringstream oss;
    if(imag_ > 0)
        oss << real_ << '+' << imag_ << 'i';
    else
        oss << real_ << imag_ << 'i';
    std::string s = oss.str();
    return s;
}
        
const double& Complex::operator[](std::string str) const{
    if(str == "real")
        return real_;
    if(str == "imag")
        return imag_;
    else
        throw std::out_of_range("invalid index: " + str);
}

double& Complex::operator[](std::string str){
    if(str == "real")
        return real_;
    if(str == "imag")
        return imag_;
    else
        throw std::out_of_range("invalid index: " + str);
}
    
std::ostream& operator<<(std::ostream& out, const Complex& c){
    if(c["real"] == 0 && c["imag"] == 0){
        out << " ";
    }
    else if(c["real"] == 0 && c["imag"] > 0){
        out << c["imag"] << "i";
    }
    else if(c["real"] == 0 && c["imag"] < 0){
        out << c["imag"] << "i";
    }
    else if (c["imag"] == 0){
        out << c["real"];
    }
    else if (c["imag"] == 1){
        out << c["real"] << "+i";
    }
    else if (c["imag"] == -1){
        out << c["real"] << "-i";
    }
    else if(c["imag"] > 0){
        out << c["real"] << "+" << c["imag"] << "i";
    }
    else if (c["imag"] < 0){
        out << c["real"] << c["imag"] << "i";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Complex& c){
    in >> c["real"] >> c["imag"];
    if(in.fail())
        throw std::runtime_error("bad inputs for reading");
    return in;
}
