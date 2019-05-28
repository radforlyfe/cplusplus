//
//  BinarySearchTree.cpp
//  p10b_assignment8

#include "BinarySearchTree.h"

namespace pic10b{

    Tree::Tree() noexcept: root_(nullptr), size_(0){}
    
    Tree::iterator Tree::find(const double value) const{
        Tree::node *curr = root_;
        while(curr != nullptr){
            if(value == curr->value_){
                return iterator(root_, this);
            }
            else if(value < curr->value_){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        return end();
    }
    
    void Tree::insert(double value){
        if(!root_){
            root_ = new node(value);
            return;
        }
        Tree::node *current = root_;
        while(current != nullptr){
            if(value == current->value_){
                return;
            }
            else if(value < current->value_){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        current = new node(value);
        return;
    }

    Tree::iterator Tree::begin() const{
        if(!root_){
            return iterator(nullptr, this);
        }
        node *n = root_;
        while(n->left != nullptr){
            n = n->left;
        }
        return iterator(n, this);
    }
    
    Tree::iterator Tree::end() const{
        return iterator(nullptr, this);
    }
    
    size_t Tree::size() const{
        return size_;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::node::node(double value): value_(value), left(nullptr), right(nullptr) {} //node stores value with children left and right both null
    
    Tree::node* Tree::node::leftmost(node *root){
        if(!root->left){
            return this;
        }
        while(root->left != nullptr){
            root = root->left;
        }
        return root;
    }
    
    Tree::node* Tree::node::rightmost(){
        if(!right){
            return this;
        }
        else{
            return right->rightmost();
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::iterator::iterator(Tree::node* n, const Tree* tree): curr(n), container(tree) {}

    Tree::iterator& Tree::iterator::operator++(){                               //prefix ++ unary operator
        if(!curr){                                                              //past-the-end
            throw std::logic_error("cannot go forward from past-the-end");
        }
        else if(curr == container->root_->rightmost()){                         //last (largest) node
            curr = nullptr;                                                     //return past-the-end
            return *this;
        }
        else{                                                                   //in valid range, and not the last node
            if(curr->right){                                                    //has a right child
                curr = curr->leftmost(curr->right);                             //go 'leftmost' from the right child
                return *this;
            }
            else{                                                               //no right child
                node *temp = curr;
                while(temp->parent != nullptr && temp != temp->parent->left){   //while temp is right child of its parent
                    temp = temp->parent;                                        //traverse up the tree
                }                                                               //temp is no longer right child of its parent: parent.value_ > curr.value_
                curr = temp->parent;
                return *this;
            }
        }
    }
    
    Tree::iterator& Tree::iterator::operator--(){                               //prefix -- unary operator
        if(curr == container->root_->leftmost(curr)){                           //first (smallest) node
            throw std::logic_error("cannot go forward from past-the-end");
        }
        else if(!curr){                                                         //past-the-end
            curr = container->root_->rightmost();                               //return last node
            return *this;
        }
        else{                                                                   //in valid range, and not the first node
            if(curr->left){                                                     //has a right child
                curr = curr->left->rightmost();                                 //go 'rightmost' from the left child
                return *this;
            }
            else{                                                               //no left child
                node *temp = curr;
                while(temp->parent != nullptr && temp == temp->parent->left){   //while temp is left child of its parent
                    temp = temp->parent;                                        //traverse up the tree
                }                                                               //temp is no longer left child of its parent: parent.value_ < curr.value_
                curr = temp->parent;
                return *this;
            }
        }
    }
    
    Tree::iterator Tree::iterator::operator++(int unused){                      //postfix ++ binary operator
        Tree::iterator copy(curr, container);
        ++(*this);
        return copy;
    }
    
    Tree::iterator Tree::iterator::operator--(int unused){                      //postfix -- binary operator
        Tree::iterator copy(curr, container);
        --(*this);
        return copy;
    }
    
    const double& Tree::iterator::operator*() const{                            //dereference operator: return reference to the int stored
        return curr->value_;
    }
    
    const double* Tree::iterator::operator->() const{                           //arrow operator: return address of the current node
        return &(curr->value_);
    }
    
    bool operator==(const Tree::iterator& lhs, const Tree::iterator& rhs){
        return ((lhs.curr == rhs.curr) && (lhs.container == rhs.container));    //compare the two private members of each iterators
    }
    
    bool operator!=(const Tree::iterator& lhs, const Tree::iterator& rhs){
        return !(lhs == rhs);
    }
    
}


