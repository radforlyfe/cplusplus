//
//  BinarySearchTree.cpp
//  p10b_assignment8

#include "BinarySearchTree.h"

namespace pic10b{

    Tree::Tree() noexcept: root(nullptr), size_(0){}
    
    Tree::iterator Tree::find(const double value) const{
        Tree::node *curr = root;
        if(curr == nullptr){
            return end();
        }
        for(;;){
            if(value == curr->value_){
                return iterator(root, this);
            }
            else if(value < curr->value_){
                if(curr->left != nullptr){
                    curr = curr->left;
                }
                else{
                    return end();
                }
            }
            else if(value > curr->value_){
                if(curr->right != nullptr){
                    curr = curr->right;
                }
                else{
                    return end();
                }
            }
        }
    }
    
    void Tree::insert(double value){
        if(root == nullptr){
            root = new node(value);
            return;
        }
        Tree::node *curr = root;
        for(;;){
            if(value == curr->value_){
                return;
            }
            if(value < curr->value_){
                if(curr->left != nullptr){
                    curr = curr->left;
                }
                else{
                    curr->left = new node(value);
                    return;
                }
            }
            if(value > curr->value_){
                if(curr->right != nullptr){
                    curr = curr->right;
                }
                else{
                    curr->right = new node(value);
                    return;
                }
            }
        }
    }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::node::node(double value): value_(value), left(nullptr), right(nullptr) {} //node stores value with children left and right both null

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::iterator::iterator(Tree::node* n, const Tree* t): curr(n), container(t) {}
