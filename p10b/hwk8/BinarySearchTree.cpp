//
//  BinarySearchTree.cpp
//  p10b_assignment8

#include "BinarySearchTree.h"
#include "Print_Tree.h"

namespace pic10b{

    Tree::Tree() noexcept: root_(nullptr), size_(0){}               //default construction: creating empty tree
    
    Tree::~Tree(){                                                  //destructor
        deleteTree(root_);
    }
    
    void Tree::deleteTree(node* n){
        if(!n){                                                     //empty tree
            return;
        }
        deleteTree(n->left_);                                       //remove the subtree on the right
        deleteTree(n->right_);                                      //remove the subtree on the right
        erase(iterator{n, this});                                   //finally call erase on the node n
    }
    
    Tree::Tree(const Tree& other): root_(nullptr), size_(0){        //copy constructor
        traverseInsert(other.root_);
    }
    
    void Tree::traverseInsert(node* n){
        if(!n){                                                     //empty tree
            return;
        }
        insert(n->value_);                                          //insert the value of current node n (from other)
        traverseInsert(n->left_);                                   //insert all the node values under n->left (=subtree on the left)
        traverseInsert(n->right_);                                  //insert all the node values under n->right (=subtree on the right)
    }
    
    Tree::Tree(Tree&& other) noexcept: Tree(){                      //move constructor
        swap(*this, other);                                         //swap pointers and size_
    }
    
    Tree& Tree::operator=(Tree rhs) &{
        std::swap(root_, rhs.root_);
        std::swap(size_, rhs.size_);
        return *this;
    }
    
    void swap(Tree& one, Tree& another){                            //swap pointers and size_
        std::swap(one.root_, another.root_);
        std::swap(one.size_, another.size_);
    }
    
    Tree::iterator Tree::find(const double value) const{
        Tree::node* current = root_;
        while(current){                                             //while node is not null
            if(value == current->value_){                           //if value is found, return iterator to the node
                return iterator(current, this);
            }
            else if(value < current->value_){                       //if value if lesser, go left and recheck
                current = current->left_;
            }
            else{                                                   //if value if greater, go right and recheck
                current = current->right_;
            }
        }
        return end();                                               //if value if not found, return the past-the-end iterator
    }
    
    void Tree::insert(double value){
        if(!root_){                                                 //if tree is empty, make root_ a new created node and increment size
            root_ = new node(value);
            ++size_;
        }
        else{                                                       //if tree not empty
            node* n = new node(value);                              //create a new node
            if(root_->insertNode(n)){                               //recursively pass it node to node until in place, only inserts the node if possible
                ++size_;                                            //increment the size only if the insertion was successful
            }
            else{
                delete n;                                           //delete the node since its a duplicated value, do not increment size
            }
        }
    }
    
    void Tree::erase(iterator it){
        if(!root_){                                                         //empty tree
            return;
        }
        if(!it.curr_->left_ && !it.curr_->right_){         //0 children
            if(it.curr_ == root_){                                          //given node is root (no parent)
                root_ = nullptr;                                            //assign root to nullptr
            }
            else{                                                           //has parent
                if(it.curr_->right_of_parent()){                            //right child of parent
                    it.curr_->parent_->right_ = nullptr;                    //set parent's right that pointed to the node to null
                }
                else if(it.curr_->left_of_parent()){                        //left child of parent
                    it.curr_->parent_->left_ = nullptr;                     //set parent's left that pointed to the node to null
                }
            }
            delete it.curr_;                                                //delete the node
            --size_;                                                        //decrement size
        }
        else{                                              //1 or 2 children
            if(!it.curr_->left_){                                           //has 1 right child
                if(it.curr_ == root_){                                      //given node is root (no parent)
                    root_ = it.curr_->right_;                               //assign new root
                }
                else{                                                       //has parent
                    node* temp = it.curr_->right_;                          //go to the child of the given node
                    temp->parent_ = it.curr_->parent_;                      //set node's child's parent to node's parent
                    if(it.curr_->right_of_parent()){                        //right child of parent
                        it.curr_->parent_->right_ = temp;                   //set parent's right that pointed to the node to node's child
                    }
                    else if(it.curr_->left_of_parent()){                    //left child of parent
                        it.curr_->parent_->left_ = temp;                    //set parent's left that pointed to the node to node's child
                    }
                }
                delete it.curr_;                                            //delete the node
                --size_;                                                    //decrement size
            }
            else if(!it.curr_->right_){                                     //has 1 left child
                if(it.curr_ == root_){                                      //given node is root (no parent)
                    root_ = it.curr_->left_;                                //assign new root
                }
                else{                                                       //has parent
                    node* temp = it.curr_->left_;                           //go to the child of the given node
                    temp->parent_ = it.curr_->parent_;                      //set node's child's parent to node's parent
                    if(it.curr_->right_of_parent()){                        //right child of parent
                        it.curr_->parent_->right_ = temp;                   //set parent's right that pointed to the node to node's child
                    }
                    else if(it.curr_->left_of_parent()){                    //left child of parent
                        it.curr_->parent_->left_ = temp;                    //set parent's left that pointed to the node to node's child
                    }
                }
                delete it.curr_;                                            //delete the node
                --size_;                                                    //decrement size
            }
            else{                                          //2 children
                node* temp = it.curr_->right_->leftmost();                  //go to the right child and as far left as possible
                it.curr_->value_ = temp->value_;                            //overwrite given node's value with right-far-left value
                erase(++it);                                                //erase temp (++it): back to base case with 0 or 1 child
                }
        }
        return;
    }
    
    Tree::iterator Tree::begin() const{
        if(!root_){                                                 //if tree is empty, return iterator to end()
            return iterator(nullptr, this);
        }
        node* n = root_;
        while(n->left_){                                            //if this node has a left child, keep going left
            n = n->left_;
        }
        return iterator(n, this);                                   //if left is null, return the iterator to the previous node
    }
    
    Tree::iterator Tree::end() const{
        return iterator(nullptr, this);                             //iterator one past the last node
    }
    
    size_t Tree::size() const{
        return size_;
    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::node::node(double value): value_(value), left_(nullptr), right_(nullptr), parent_(nullptr) {} //node stores value with left_, right_, parent as null
    
    bool Tree::node::insertNode(node* n){
        if(n->value_ < value_){                                     //if value is lesser
            if(left_){                                              //if this node has a left child, keep going left (recurse on the left child)
                return left_->insertNode(n);
            }
            else{                                                   //if left is null
                left_ = n;                                          //make n the new left child
                n->parent_ = this;                                  //make this n's parent
                return true;
            }
        }
        else if(n->value_ > value_){                                //if value if greater
            if(right_){                                             //if this node has a right child, keep going right (recurse on the right child)
                return right_->insertNode(n);
            }
            else{                                                   //if right is null
                right_ = n;                                         //make n the new right child
                n->parent_ = this;                                  //make this n's parent
                return true;
            }
        }
        else{
            return false;                                           //if value is same, nothing to add and return false
        }
    }
    
    
    Tree::node* Tree::node::leftmost(){
        if(!left_){                                                 //no left child
            return this;
        }
        else{                                                       //has left child
            return left_->leftmost();                               //recurse on the left child
        }
    }
    
    Tree::node* Tree::node::rightmost(){
        if(!right_){                                                //no right child
            return this;
        }
        else{                                                       //has right child
            return right_->rightmost();                             //recurse on the right child
        }
    }

    bool Tree::node::left_of_parent(){
        if(parent_){                                                //not the root
            if(parent_->left_ == this){                             //left child of its parent
                return true;
            }
        }                                                           //root or right child of its parent
        return false;
    }
        
    bool Tree::node::right_of_parent(){
        if(parent_){                                                //not the root
            if(parent_->right_ == this){                            //right child of its parent
                return true;
            }
        }                                                           //root or left child of its parent
        return false;
    }
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::iterator::iterator(Tree::node* n, const Tree* tree): curr_(n), container_(tree) {}

    Tree::iterator& Tree::iterator::operator++(){                                 //prefix ++ unary operator
        if(!curr_){                                                               //past-the-end
            throw std::logic_error("cannot go forward from past-the-end");
        }
        else if(curr_ == container_->root_->rightmost()){                         //last (largest) node
            curr_ = nullptr;                                                      //return past-the-end
            return *this;
        }
        else{                                                                     //in valid range, and not the last node
            if(curr_->right_){                                                    //has a right_ child
                curr_ = curr_->right_->leftmost();                                //go 'leftmost' from the right child
                return *this;
            }
            else{                                                                 //no right child
                node* n = curr_;
                while(n -> right_of_parent()){                                    //while n is right child of its parent
                    n = n->parent_;                                               //traverse up the tree
                }                                                                 //n is no longer right child : parent_.value_ > curr_.value_
                curr_ = n->parent_;                                               //curr is now the successor
                return *this;
            }
        }
    }
    
    Tree::iterator& Tree::iterator::operator--(){                                 //prefix -- unary operator
        if(curr_ == container_->root_->leftmost()){                               //first (smallest) node
            throw std::logic_error("cannot go forward from past-the-end");
        }
        else if(!curr_){                                                          //past-the-end
            curr_ = container_->root_->rightmost();                               //return last node
            return *this;
        }
        else{                                                                     //in valid range, and not the first node
            if(curr_->left_){                                                     //has a left child
                curr_ = curr_->left_->rightmost();                                //go 'rightmost' from the left child
                return *this;
            }
            else{                                                                 //no left child
                node* n = curr_;
                while(n->parent_ != nullptr && n == n->parent_->left_){           //while n is left child of its parent
                    n = n->parent_;                                               //traverse up the tree
                }                                                                 //n is no longer left child : parent_.value_ < curr_.value_
                curr_ = n->parent_;                                               //curr is now the predecessor
                return *this;
            }
        }
    }
    
    Tree::iterator Tree::iterator::operator++(int unused){                        //postfix ++ binary operator
        Tree::iterator copy(curr_, container_);                                   //copy construct this
        ++(*this);                                                                //increment this
        return copy;                                                              //return the copy
    }
    
    Tree::iterator Tree::iterator::operator--(int unused){                        //postfix -- binary operator
        Tree::iterator copy(curr_, container_);                                   //copy construct this
        --(*this);                                                                //decrement this
        return copy;                                                              //return the copy
    }
    
    double Tree::iterator::operator*() const{                                     //dereference operator: return reference to the int stored
        return curr_->value_;
    }
    
    double* Tree::iterator::operator->() const{                                   //arrow operator: return address of the current node
        return &(curr_->value_);
    }
    
    bool operator==(const Tree::iterator& lhs, const Tree::iterator& rhs){
        return ((lhs.curr_ == rhs.curr_) && (lhs.container_ == rhs.container_));  //compare the two private members of each iterators
    }
    
    bool operator!=(const Tree::iterator& lhs, const Tree::iterator& rhs){
        return !(lhs == rhs);                                                     //not of the ==operator
    }

}

