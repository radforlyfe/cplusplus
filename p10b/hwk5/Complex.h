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
    /**
     constexpr constructor which behaves like a default constructor, through the use of default arguments:
        constructs a complex number from real and imaginary parts
     @param real : the real component of complex number
     @param imaginary : the imaginary component of complex number
     */
    constexpr Complex(double real=0, double imaginary=0);
    
    /**
     constructor that accepts a string input that can parse a string into a complex number
     @param str : string that can be parsed into complex number
     */
    Complex(const std::string& str);
    
    /**
     binary operator+= to add two complex numbers, changing the lhs
     @param other : rhs which is added to the *this (lhs)
     @return updated Complex number
     */
    constexpr Complex& operator+=(const Complex& other);
    
    /**
     binary operator-= to subtract two complex numbers, changing the lhs
     @param other : rhs which is subtracted to the *this (lhs)
     @return updated Complex number
     */
    constexpr Complex& operator-=(const Complex& other);
    
    /**
     binary operator*= to multiply two complex numbers, changing the lhs
     @param other : rhs which is multiplied to the *this (lhs)
     @return updated Complex number
     */
    constexpr Complex& operator*=(const Complex& other);
    
    /**
     binary operator/= to divide two complex numbers, changing the lhs
     @param other : rhs which divides the *this (lhs)
     @return updated Complex number
     */
    constexpr Complex& operator/=(const Complex& other);
    
    /**
     unary operator+ to return a copy of the complex number.
     @return copy of the Complex number
     */
    constexpr Complex operator+() const;
    
    /**
     unary operator- to return a complex number with negated real and imaginary parts
     @return copy of the negated Complex number (negated real and negated imaginary)
     */
    constexpr Complex operator-() const;
    
    /**
     unary operator~ to return the conjugate of the complex number
     @return copy of the conjugated Complex number (negated imaginary)
     */
    constexpr Complex operator~() const;
    
    /**
     prefix (unary) operator++: real part is incremented by 1
     @return real part incremented by 1
     */
    constexpr Complex& operator++();
    
    /**
     postfix (binary) operator++: real part is incremented by 1
     @param unused : unused parameter
     @return copy of the Complex number (no change)
     */
    constexpr Complex operator++(int unused); //postfix
    
    /**
     prefix (unary) operator--: real part is decremented by 1
     @return real part decremented by 1
     */
    constexpr Complex& operator--();
    
    /**
     postfix (binary) operator--: real part is decremented by 1
     @param unused : unused parameter
     @return copy of the Complex number (no change)
     */
    constexpr Complex operator--(int unused);
    
    /**
     subscript operator overloaded on const: takes either “real” or “imag” as arguments and returns the real or imaginary parts of the Complex number respectively
     @param str : string if "real" or "imag" gives the value of real or imaginary component
     @return const double& : reads the real or imaginary parts of the Complex number
     */
    const double& operator[](std::string str) const;
    
    /**
     subscript operator: takes either “real” or “imag” as arguments and returns the real or imaginary parts of the Complex number respectively
     @param str : string if "real" or "imag" assigns the value to real or imaginary component
     @return double& : assigns the real or imaginary parts of the Complex number
     */
    double& operator[](std::string str);
    
    /**
     call operator taking no arguments setting the complex number to 0
     */
    constexpr void operator()();
    
    /**
     conversion operator from Complex to std::string
     @return string converted from Complex
    */
    operator std::string() const;

    /**
     comparison operators operator< : compared lexicographically - since non-member function declared as friend
     @param lhs Complex number compared
     @param rhs Complex number compared
     @return true if lhs is less than rhs
     */
    friend constexpr bool operator<(const Complex& lhs, const Complex& rhs);
    
private:
    double real_;
    double imag_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Non-member functions declarations:

/**
 binary operator+ to add two complex numbers, returning sum
 @param lhs : Complex number passed as copy of lhs
 @param rhs : Complex number passed as reference to const
 @return updated lhs Complex number which is the sum of lhs and rhs
 */
constexpr Complex operator+(Complex lhs, const Complex& rhs);

/**
 binary operator- to subtract two complex numbers, returning difference
 @param lhs : Complex number passed as copy of lhs
 @param rhs : Complex number passed as reference to const
 @return updated lhs Complex number which is the difference of lhs and rhs
 */
constexpr Complex operator-(Complex lhs, const Complex& rhs);

/**
 binary operator* to multiply two complex numbers, returning product
 @param lhs : Complex number passed as copy of lhs
 @param rhs : Complex number passed as reference to const
 @return updated lhs Complex number which is the product of lhs and rhs
 */
constexpr Complex operator*(Complex lhs, const Complex& rhs);

/**
 binary operator/ to divide two complex numbers, returning quotient
 @param lhs : Complex number passed as copy of lhs
 @param rhs : Complex number passed as reference to const
 @return updated lhs Complex number which is the quotient of lhs and rhs
 */
constexpr Complex operator/(Complex lhs, const Complex& rhs);

/**
 operator<< to print/ display the Complex number with an output stream
 @param out : output stream
 @param c : Complex number passed as reference to const
 @return print out of the Complex number with an output stream
 */
std::ostream& operator<<(std::ostream& out, const Complex& c);

/**
 operator>> to read in two double values, separated by white space
 @param in : input stream
 @param c : Complex number passed as reference to const
 @return print out of the Complex number with an output stream
 */
std::istream& operator>>(std::istream& in, Complex& c);

/** user-defined literal expression: so that code expression will be converted into complex number
 @param c : long double
 @return Complex number
 */
constexpr Complex operator""_i(long double c);

/**
 comparison operators operator>= : compared lexicographically
 @param lhs Complex number compared
 @param rhs Complex number compared
 @return true if lhs is greater than or equal to rhs
 */
constexpr bool operator>=(const Complex& lhs, const Complex& rhs);

/**
 comparison operators operator== : compared lexicographically
 @param lhs Complex number compared
 @param rhs Complex number compared
 @return true if lhs is equal to rhs
 */
constexpr bool operator==(const Complex& lhs, const Complex& rhs);

/**
 comparison operators operator!= : compared lexicographically
 @param lhs Complex number compared
 @param rhs Complex number compared
 @return true if lhs is not equal to rhs
 */
constexpr bool operator!=(const Complex& lhs, const Complex& rhs);

/**
 comparison operators operator> : compared lexicographically
 @param lhs Complex number compared
 @param rhs Complex number compared
 @return true if lhs is greater than rhs
 */
constexpr bool operator>(const Complex& lhs, const Complex& rhs);

/**
 comparison operators operator<= : compared lexicographically
 @param lhs Complex number compared
 @param rhs Complex number compared
 @return true if lhs is less than or equal to rhs
 */
constexpr bool operator<=(const Complex& lhs, const Complex& rhs);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INLINE Complex class member function definitions:

// must initialize in the initializer list
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
    return *this;
}

constexpr Complex Complex::operator+() const{             // unary operator+
    return Complex(real_, imag_);
}
constexpr Complex Complex::operator-() const{             // unary operator-
    return Complex(-real_, -imag_);
}
constexpr Complex Complex::operator~() const{            // unary operator~
    return Complex(real_, -imag_);
}
constexpr Complex& Complex::operator++(){                // prefix ++ unary operator
    ++real_;
    return *this;
}
constexpr Complex Complex::operator++(int unused){       // postfix ++ binary operator
    Complex temp(*this);
    ++(*this);
    return temp;
}
constexpr Complex& Complex::operator--(){                // prefix -- unary operator
    --real_;
    return *this;
}
constexpr Complex Complex::operator--(int unused){       // prefix -- binary operator
    Complex temp(*this);
    --(*this);
    return temp;
}

constexpr void Complex::operator()(){                    // call operator
    real_ = 0;
    imag_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    return Complex(0, c);                                           // calling Complex constructor with real=0
}
constexpr bool operator<(const Complex& lhs, const Complex& rhs){   // non-member function operator< as friend
    if (lhs.real_ < rhs.real_)                                      // comparison for real components
        return true;
    if(lhs.real_ == rhs.real_ && lhs.imag_ < rhs.imag_)             // comparison for imag if reals are equal
        return true;
    return false;
}
constexpr bool operator>=(const Complex& lhs, const Complex& rhs){
    if(!(lhs < rhs))                                               // !(a<b) == (a>=b)
        return true;
    return false;
}
constexpr bool operator==(const Complex& lhs, const Complex& rhs){
    if(!(lhs < rhs) && !(rhs < lhs))                              // !(a<b) && !(b<a) == (a==b)
        return true;
    return false;
}
constexpr bool operator!=(const Complex& lhs, const Complex& rhs){
    if(!(lhs == rhs))                                             // !(a=b) == (a!=b)
        return true;
    return false;
}
constexpr bool operator>(const Complex& lhs, const Complex& rhs){
    if(!(lhs < rhs) && lhs != rhs)                                // !(a<b) && (a!=b) == (a>b)
        return true;
    return false;
}
constexpr bool operator<=(const Complex& lhs, const Complex& rhs){
    if(!(lhs > rhs))                                              // !(a>b) == (a<=b)
        return true;
    return false;
}

#endif /* Complex_H */
