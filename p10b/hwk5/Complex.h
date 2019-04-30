//
//  Complex.h
//  Assignment5

#ifndef Complex_H
#define Complex_H
#include<iostream>
#include<string>
#include<sstream>
#include<stdexcept>

class Complex
{
public:
    constexpr Complex(double real=0, double imaginary=0): real_(real), imag_(imaginary){}
    
    Complex(std::string str);
    
    constexpr Complex& operator+=(const Complex& other){
        real_ += other.real_;
        imag_ += other.imag_;
        return *this;
    }
    
    constexpr Complex& operator-=(const Complex& other){
        real_ -= other.real_;
        imag_ -= other.imag_;
        return *this;
    }
    
    constexpr Complex& operator*=(const Complex& other){
        real_ *= other.real_;
        imag_ *= other.imag_;
        return *this;
    }
    
    constexpr Complex& operator/=(const Complex& other){
        real_ /= other.real_;
        imag_ /= other.imag_;
        return *this;
    }
    
    constexpr Complex operator+() const{
        return Complex(real_, imag_);
    }
    
    constexpr Complex operator-() const{
        return Complex(-real_, -imag_);
    }
    
    constexpr Complex operator~() const{
        return Complex(real_, -imag_);
    }
    
    const double& operator[](std::string str) const;
    
    double& operator[](std::string str);
    
private:
    double real_;
    double imag_;
};

// Non-member functions:
Complex operator+(Complex lhs, const Complex& rhs);
Complex operator-(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, const Complex& rhs);
Complex operator/(Complex lhs, const Complex& rhs);


//std::ostream& operator<<(std::ostream out, const Complex& c){
//    if(c["real"] == 0 && c["imag"] > 0){
//        out << c["imag"] << "i";
//    }
//    if(c["real"] == 0 && c["imag"] < 0){
//         out << "-" << c["imag"] << "i";
//    }
//    else if (c["imag"] == 1){
//        out << c["real"] << "+i";
//    }
//    else if (c["imag"] == -1){
//        out << c["real"] << "-i";
//    }
//    if(c["imag"] > 0){
//        out << c["real"] << "+" << c["imag"] << "i";
//    }
//    else if (c["imag"] < 0){
//        out << c["real"] << "-" << c["imag"] << "i";
//    }
//    else if (c["imag"] == 0){
//        out << c["real"];
//    }
//    return out;
//}

constexpr bool operator<(const Complex& left, const Complex& right);
constexpr bool operator>(const Complex& left, const Complex& right);
constexpr bool operator==(const Complex& left, const Complex& right);
constexpr bool operator!=(const Complex& left, const Complex& right);
constexpr bool operator<=(const Complex& left, const Complex& right);
constexpr bool operator>=(const Complex& left, const Complex& right);

#endif /* Complex_H */
