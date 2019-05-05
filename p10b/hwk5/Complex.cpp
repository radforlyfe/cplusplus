//  Complex.cpp
//  Assignment5

#include "Complex.h"
namespace { // to declare the "real" and "imag" as constexpr
    constexpr char REAL[] = "real";
    constexpr char IMAG[] = "imag";
}

// Constructor that accepts a string input - parses the string into a Complex number
Complex::Complex(const std::string& string_){
    auto str = string_;
    if(str.empty()){                                             // throw logic error exception for empty string
        throw std::logic_error("bad input string: " + string_);
    }
    if(str.front() == 'i'){                                      // string starting with i : replace with 1i
        str.replace(0, 1, "1i");
    }
    size_t minus_i = str.find("-i");
    while(minus_i != std::string::npos){                         // find -i in string : replace with -1i
        str.replace(minus_i, 2, "-1i");
        minus_i = str.find("-i");
    }
    size_t plus_i = str.find("+i");
    while(plus_i != std::string::npos){                          // find +i in string : replace with +1i
        str.replace(plus_i, 2, "+1i");
        plus_i = str.find("+i");
    }
    size_t char_i = str.find("i");
    while(char_i != std::string::npos){                          // find i in string : replace with $ symbol
        str.replace(char_i, 1, "$");
        char_i = str.find("i");
    }
    std::istringstream ss(str);                                  // make input string stream from str
    double _real = 0.0, _imag = 0.0, _temp = 0.0;
    while(ss.peek() != -1){                                      // loop until peek != -1 (end)
        ss >> _temp;                                             // read from the stream into _temp
        if(ss.fail()){                                           // throw exception if string cannot be parsed
            throw std::logic_error("bad input string: " + string_);
        }
        if(ss.peek() == '+' || ss.peek() == '-' || ss.peek() == EOF){  // if next char is +/-/end, add to real
            _real += _temp;
        }
        else if(ss.peek() == '$'){                                     // if next char is $(i), add to imag
            _imag += _temp;
            ss.get();                                                  // moves to the next character
        }
    }
    real_ = _real;                                                    // set real component
    imag_ = _imag;                                                    // set imag component
}

// Conversion operator from Complex to String
Complex::operator std::string() const{
    std::ostringstream oss;                                        // makes an output string stream
    oss << *this;                                                  // calls the << operator
    return oss.str();                                              // returns the string storing content of stream
}

// Subscript operator overloaded on const:
const double& Complex::operator[](std::string str) const{
    if(str == REAL)                                                // if str is "real" return real component
        return real_;
    if(str == IMAG)                                                // if str is "imag" return imaginary component
        return imag_;
    else
        throw std::out_of_range("invalid index: " + str);          // throw out_of_range exception otherwise
}

double& Complex::operator[](std::string str){
    if(str == REAL)                                                // if str is "real" assign real component
        return real_;
    if(str == IMAG)                                                // if str is "real" assign real component
        return imag_;
    else
        throw std::out_of_range("invalid index: " + str);          // throw out_of_range exception otherwise
}

// operator<< to print the complex number with an output stream
std::ostream& operator<<(std::ostream& out, const Complex& c){
    if(c[REAL] != 0 || c[IMAG] == 0){                             // always prints real unless real=0 and imag!=0
        out << c[REAL];
    }
    if(c[REAL] != 0 && c[IMAG] > 0){                              // print + operator for real!=0 and imag>0
        out << '+';
    }
    if(c[IMAG] == 1){                                             // print i instead of 1i
        out << "i";
    }
    else if (c[IMAG] == -1){                                      // print -i instead of -1i
        out << "-i";
    }
    else if(c[IMAG] != 0){                                        // print imag i for all other cases when imag!=0
        out << c[IMAG] << "i";
    }
    return out;
}

// operator>> to read in two double values, separated by white space
std::istream& operator>>(std::istream& in, Complex& c){
    in >> c[REAL] >> c[IMAG];                                     // set real and imaginary components using istream
    if(in.fail())
        throw std::runtime_error("bad inputs for reading");       // throw exception if fail to read
    return in;
}
