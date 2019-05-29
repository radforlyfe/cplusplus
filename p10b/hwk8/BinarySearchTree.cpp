//
//  BinarySearchTree.cpp
//  p10b_assignment8

#include "BinarySearchTree.h"
#include "Print_Tree.h"

namespace pic10b{

    Tree::Tree() noexcept: root_(nullptr), size_(0){}               //default construction: creating empty tree
    
    Tree::~Tree(){
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
        insert(n->value_);                                          //no need to make a new node?????????
        traverseInsert(n->left_);
        traverseInsert(n->right_);
    }
    
    Tree::Tree(Tree&& other) noexcept: Tree(){                      //move constructor
        swap(*this, other);
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
        if(!root_){                                                 //if tree is empty, insert a node and increment size
            root_ = new node(value);
            ++size_;
            return;
        }
        node* current = root_;
        while(current){                                             //while node is not null
            if(value == current->value_){                           //if value is duplicate, do not insert
                return;
            }
            else if(value < current->value_){                       //if value is lesser
                if(current->left_){                                 //if left is not null, keep going left
                    current = current->left_;}
                else{                                               //if left is null, assign it a new node, insert and increment size
                    current->left_ = new node(value);
                    current->left_->parent_ = current;
                    ++size_;
                }
            }
            else{                                                   //if value if greater
                if(current->right_){                                //if right is not null, keep going right
                    current = current->right_;
                }
                else{                                               //if right is null, assign it a new node, insert and increment size
                    current->right_ = new node(value);
                    current->right_->parent_ = current;
                    ++size_;
                }
            }
        }
    }
    
    void Tree::erase(iterator it){
        if(!root_){                                                         //empty tree
            return;
        }
        if(!it.curr_->left_ && !it.curr_->right_){                      //0 children
            if(!it.curr_->parent_){                                     //given node is root (no parent)
                delete it.curr_;                                            //delete node
                root_ = nullptr;                                            //assign root to nullptr
                --size_;                                                    //decrement size
            }
            else{                                                       //has parent
                if(it.curr_->right_of_parent()){                        //right child of parent
                    it.curr_->parent_->right_ = nullptr;                    //set parent's right that pointed to the node to null
                }
                else if(it.curr_->left_of_parent()){                    //left child of parent
                    it.curr_->parent_->left_ = nullptr;                     //set parent's left that pointed to the node to null
                }
                delete it.curr_;                                            //delete the node
                --size_;                                                    //decrement size
            }
        }
        else{                                                           //1 or 2 children
            if(!it.curr_->left_){                                       //has 1 right child
                if(!it.curr_->parent_){                                     //given node is root (no parent)
                    delete it.curr_;                                        //delete node
                    root_ = it.curr_->right_;                               //assign new root
                    --size_;                                                //decrement size_
                }
                else{                                                   //has parent
                    node* temp = it.curr_->right_;                          //go to the child of the given node
                    temp->parent_ = it.curr_->parent_;                      //set node's child's parent to node's parent
                    if(it.curr_->right_of_parent()){                    //right child of parent
                        it.curr_->parent_->right_ = temp;                   //set parent's right that pointed to the node to node's child
                    }
                    else if(it.curr_->left_of_parent()){                //left child of parent
                        it.curr_->parent_->left_ = temp;                    //set parent's left that pointed to the node to node's child
                    }
                    delete it.curr_;                                        //delete the node
                    --size_;                                                //decrement size
                }
            }
            else if(!it.curr_->right_){                                  //has 1 left child
                if(!it.curr_->parent_){                                     //given node is root (no parent)
                    delete it.curr_;                                        //delete node
                    root_ = it.curr_->left_;                                //assign new root
                    --size_;                                                //decrement size_
                }
                else{                                                   //has parent
                    node* temp = it.curr_->left_;                           //go to the child of the given node
                    temp->parent_ = it.curr_->parent_;                      //set node's child's parent to node's parent
                    if(it.curr_->right_of_parent()){                    //right child of parent
                        it.curr_->parent_->right_ = temp;                   //set parent's right that pointed to the node to node's child
                    }
                    else if(it.curr_->left_of_parent()){                //left child of parent
                        it.curr_->parent_->left_ = temp;                    //set parent's left that pointed to the node to node's child
                    }
                    delete it.curr_;                                        //delete the node
                    --size_;                                                //decrement size
                }
            }
            else{                                                       //2 children
                node* temp = it.curr_->right_->leftmost();                  //go to the right child and as far left as possible
                it.curr_->value_ = temp->value_;                            //overwrite given node's value with right-far-left value
                erase(it);                                                  //erase temp - back to base case with 0 or 1 child
                }
        }
        return;
    }
    
    Tree::iterator Tree::begin() const{
        if(!root_){                                                 //if tree is empty, return iterator to end()
            return iterator(nullptr, this);
        }
        node *n = root_;
        while(n->left_){                                            //if left is not null, keep going left
            n = n->left_;
        }
        return iterator(n, this);                                   //if left is null, return the previous node iterator
    }
    
    Tree::iterator Tree::end() const{
        return iterator(nullptr, this);                             //iterator one past the last node
    }
    
    size_t Tree::size() const{
        return size_;
    }

//    std::ostream& operator<<(std::ostream& out, const Tree& tree){
//        for(auto i : tree){
//            out << i << ' ';
//        }
//        out << '\n';
//        return out;
//    }
        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tree::node::node(double value): value_(value), left_(nullptr), right_(nullptr) {} //node stores value with children left_ and right_ both null
    
    Tree::node* Tree::node::leftmost(){
        if(!left_){                                                     //no left child
            return this;
        }
        else{                                                           //has left child
            return left_->leftmost();                                   //recursive call
        }
    }
    
    Tree::node* Tree::node::rightmost(){
        if(!right_){                                                    //no right child
            return this;
        }
        else{                                                           //recursive call
            return right_->rightmost();
        }
    }

    bool Tree::node::left_of_parent(){
        if(parent_){                                                    //not the root
            if(parent_->left_ == this){                                 //left child of its parent
                return true;
            }
        }                                                              //root or right child of its parent
        return false;
    }
        
    bool Tree::node::right_of_parent(){
        if(parent_){                                                    //not the root
            if(parent_->right_ == this){                                //right child of its parent
                return true;
            }
        }                                                               //root or left child of its parent
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
                curr_ = curr_->right_->leftmost();                                //go 'left_most' from the right_ child
                return *this;
            }
            else{                                                                 //no right_ child
                node* temp = curr_;
                while(temp->parent_ != nullptr && temp != temp->parent_->left_){  //while temp is right_ child of its parent_
                    temp = temp->parent_;                                         //traverse up the tree
                }                                                                 //temp is no longer right_ child : parent_.value_ > curr_.value_
                curr_ = temp->parent_;
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
            if(curr_->left_){                                                     //has a right_ child
                curr_ = curr_->left_->rightmost();                                //go 'right_most' from the left_ child
                return *this;
            }
            else{                                                                 //no left_ child
                node *temp = curr_;
                while(temp->parent_ != nullptr && temp == temp->parent_->left_){  //while temp is left_ child of its parent_
                    temp = temp->parent_;                                         //traverse up the tree
                }                                                                 //temp is no longer left_ child : parent_.value_ < curr_.value_
                curr_ = temp->parent_;
                return *this;
            }
        }
    }
    
    Tree::iterator Tree::iterator::operator++(int unused){                        //postfix ++ binary operator
        Tree::iterator copy(curr_, container_);
        ++(*this);
        return copy;
    }
    
    Tree::iterator Tree::iterator::operator--(int unused){                        //postfix -- binary operator
        Tree::iterator copy(curr_, container_);
        --(*this);
        return copy;
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
        return !(lhs == rhs);
    }

}

