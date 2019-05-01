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
    constexpr Complex(double real=0, double imaginary=0);
    Complex(std::string str);
    constexpr Complex& operator+=(const Complex& other);
    constexpr Complex& operator-=(const Complex& other);
    constexpr Complex& operator*=(const Complex& other);
    constexpr Complex& operator/=(const Complex& other);
    constexpr Complex operator+() const;
    constexpr Complex operator-() const;
    constexpr Complex operator~() const;
    const double& operator[](std::string str) const; 
    double& operator[](std::string str);
    
    
//    friend constexpr bool Complex::operator<(const Complex& lhs, const Complex& rhs){
//        if (real_ < rhs.real_)
//            return true;
//        if(real_ == rhs.real_ && imag_ < rhs.imag_)
//            return true;
//        return false;
//    }
//    constexpr bool operator>(const Complex& lhs, const Complex& rhs);
//    constexpr bool operator==(const Complex& lhs, const Complex& rhs);
//    constexpr bool operator!=(const Complex& lhs, const Complex& rhs);
//    constexpr bool operator<=(const Complex& lhs, const Complex& rhs);
//    constexpr bool operator>=(const Complex& lhs, const Complex& rhs);
    
private:
    double real_;
    double imag_;
};

// Non-member functions declarations:
constexpr Complex operator+(Complex lhs, const Complex& rhs);
constexpr Complex operator-(Complex lhs, const Complex& rhs);
constexpr Complex operator*(Complex lhs, const Complex& rhs);
constexpr Complex operator/(Complex lhs, const Complex& rhs);
std::ostream& operator<<(std::ostream& out, const Complex& c);
std::istream& operator>>(std::istream& in, const Complex& c);
constexpr Complex operator""_i(long double c); // user-defined literal expression


// Complex class Member function definitions:
constexpr Complex::Complex(double real, double imaginary): real_(real), imag_(imaginary){}

constexpr Complex& Complex::operator+=(const Complex& other){
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
}

constexpr Complex& Complex::operator-=(const Complex& other){
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
}

constexpr Complex& Complex::operator*=(const Complex& other){
    Complex temp;
    temp.real_ = (real_ * other.real_) - (imag_ * other.imag_);
    imag_ = (imag_ * other.real_) + (real_ * other.imag_);
    real_ = temp.real_;
    return *this;
}

constexpr Complex& Complex::operator/=(const Complex& other){
    Complex temp;
    double deno = (other.real_*other.real_) + (other.imag_*other.imag_);
    double real_num = (real_ * other.real_) + (imag_ * other.imag_);
    double imag_num = (imag_ * other.real_) - (real_ * other.imag_);
    temp.real_ = real_num / deno;
    imag_ = imag_num / deno;
    real_ = temp.real_;
    //imag_ = (imag_ * other.real_) - (real_ * other.imag_) /  ((other.real_*other.real_) + (other.imag_*other.imag_)); ??
    return *this;
}

constexpr Complex Complex::operator+() const{
    return Complex(real_, imag_);
}
constexpr Complex Complex::operator-() const{
    return Complex(-real_, -imag_);
}
constexpr Complex Complex::operator~() const{
    return Complex(real_, -imag_);
}


// Non-member functions definitions:
constexpr Complex operator+(Complex lhs, const Complex& rhs){
    return lhs += rhs;
}
constexpr Complex operator-(Complex lhs, const Complex& rhs){
    return lhs -= rhs;
}
constexpr Complex operator*(Complex lhs, const Complex& rhs){
    return lhs *= rhs;
}
constexpr Complex operator/(Complex lhs, const Complex& rhs){
    return lhs /= rhs;
}
constexpr Complex operator""_i(long double c){
    return Complex(0, c);
}
#endif /* Complex_H */
