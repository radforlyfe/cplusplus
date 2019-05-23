//
//  BinarySearchTree.cpp
//  p10b_assignment8

#include "BinarySearchTree.h"

namespace pic10b{

    Tree::Tree() noexcept: root(nullptr), size_(0){}
    
    





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::node::node(double value): value_(value), left(nullptr), right(nullptr) {} //node stores value with children left and right both null

    void Tree::node::insertNode(node*){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::const_iterator::const_iterator(node* n, const Tree* t): curr(n), container(t) {}
    
    Tree::const_iterator& Tree::const_iterator::operator++(){      //prefix ++ unary operator
        if(curr == nullptr){
            throw std::logic_error("Invalid address");
        }
        else{
            
        }
        return *this;
    }

    
}
