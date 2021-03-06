//
//  main.cpp STLContainer
//


#include <iostream>
#include<string>
#include "Vector.h"


STLContainer::Vector<std::string> foo() {
    return STLContainer::Vector<std::string>(2);
}

int main() {

    STLContainer::Vector<std::string> vs;
    std::cout << "vs stats: " << vs.size() << " " << vs.capacity() << '\n';
    vs.push_back("hello");
    std::cout << "vs stores: " << vs.at(0) << '\n';
    
    auto foo_out = foo();
    
    STLContainer::Vector<int> nums {1,2,3};
    for(const auto& num : nums){
        std::cout<< num << " ";}
    
    STLContainer::Vector<std::string> vs1 {"11", "22", "33"};
    std::cout << "vs1 stats: " << vs1.size() << " " << vs1.capacity() << '\n';
    vs1.push_back("hello");
    std::cout << "vs1 stores: " << vs1.at(0) << '\n';

    STLContainer::Vector<std::string> vs2(std::move(foo_out));
    std::cout << "vs2 stats: " << vs2.size() << " " << vs2.capacity() << '\n';
    
    std::cout << "vs2 stores: ";
    for (std::size_t i = 0, total_size = vs2.size(); i < total_size; ++i) {
        std::cout << vs2.at(i) << ",";
    }
    std::cout << '\n';
    
    STLContainer::Vector<std::string> vs3(4, "beta");
    vs3.pop_back();
    vs3.push_back("delta");
    vs3.push_back("epsilon");
    vs3.at(1) = "gamma";
    vs3.insertAt(0, "alpha");
    vs3.push_back("zeta");
    vs3.push_back("theta");
    vs3.insertAt(vs3.size() - 1, "eta");
    vs3.deleteAt(3);
    std::cout << "vs3 stats: " << vs3.size() << " " << vs3.capacity() << '\n';
    std::cout << "vs3 stores: ";
    for (std::size_t i = 0, total_size = vs3.size(); i < total_size; ++i) {
        std::cout << vs3.at(i) << ",";
    }
    std::cout << '\n';
    vs2 = vs3;
    std::cout << "vs2 stats: " << vs2.size() << " " << vs2.capacity() << '\n';
    std::cout << "vs2 stores: ";
    for (std::size_t i = 0, total_size = vs2.size(); i < total_size; ++i) {
        std::cout << vs2.at(i) << ",";
    }
    std::cout << '\n';
    const auto vs4 = std::move(vs);
    std::cout << "vs4 stats: " << vs4.size() << " " << vs4.capacity() << '\n';
    std::cout << "vs4 stores: ";
    for (std::size_t i = 0, total_size = vs4.size(); i < total_size; ++i) {
        std::cout << vs4.at(i) << ",";
    }
    
    std::cout << '\n';
    std::cin.get();
    return 0;
}
