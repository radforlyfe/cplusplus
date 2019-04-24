//  Sequence.cpp
//  cs32_Project2
//

#include "Sequence.h"
#include<iostream>

// Create an empty sequence (i.e., one with no items)
Sequence::Sequence(): size_(0){ // making a dummy node in circular doubly linked list
    // head = new Node(0,head, head)
    head = new Node;
    head->next_ = head;
    head->prev_ = head;
}

// Copy constructor:
Sequence::Sequence(const Sequence& other): Sequence(){
    Node* current = head;
    Node* otherC = other.head->next_;
    while(otherC != head){
        createNode(current,otherC->value_);
        otherC = otherC->next_;
        current = current->next_;
   }
}

// Assignment operator:
Sequence& Sequence::operator=(const Sequence & rhs){
    if (this != &rhs){
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

// Deconstructor:
Sequence::~Sequence(){
    int pos = 0;
    while(head->next_ != head){
        erase(pos);
        pos++;
    }
    delete head;
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const{
    return (size()==0);
}

// Return the number of items in the sequence.
int Sequence::size() const{
    return size_;
}

// Insert value into the sequence so that it becomes the item at
// position pos. The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
int Sequence::insert(int pos, const ItemType& value){
    if(pos >= 0 && pos <= size()){
        Node * current = head; // start at dummy node
        for(int i =0; i< pos-1; i++){
            current = current->next_;
        }
        createNode(current, value);
        return pos;
    }
    else{
        return -1;
    }
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value){
    Node * current = head->next_;
    int pos = 0;
    while(current != head){
        if(value <= current->value_){
            insert(pos, value);
            return pos;
        }
        current = current->next_;
        pos++;
    }
    return -1;
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos){
    if(pos>=0 && pos<size()){
        Node * current = head->next_;
        for(int i = 0; i < pos; i++){
            current = current->next_;
        }
        current->prev_->next_ = current->next_;
        current->next_->prev_= current->prev_;
        delete current;
        size_--;
        return true;
    }
    return false;
}

// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value){
    Node * current = head->next_;
    int pos = 0;
    int count =0;
    while(current != head){
        if(current->value_ == value){
            erase(pos);
            count++;
        }
        current = current->next_;
        pos++;
    }
    return count;
}

// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const{
    if(pos>=0 && pos<size()){
        Node * current = head->next_;
        for(int i = 0; i < pos; i++){
            current = current->next_;
        }
        value = current->value_;
        return true;
    }
    return false;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value){
    if(pos>=0 && pos<size()){
        Node * current = head->next_;
        for(int i = 0; i < pos; i++){
            current = current->next_;
        }
        current->value_ = value;
        return true;
    }
    return false;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const{
    int pos = 0;
    Node * current = head->next_;
    while(current != head){
        if(current->value_ == value){
            return pos;
        }
        current = current->next_;
        pos++;
    }
    return -1;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other){
    Node * temp = head; // swap the head pointers
    head = other.head;
    other.head = temp;
    
    int tempsize_ = size_; // swap the sizes
    size_ = other.size_;
    other.size_ = tempsize_;
}

// The intent of this function is that for your own testing purposes,
// you can call it to print information about the sequence; we will never call it.
void Sequence::dump() const{
    Node * current = head->next_;
    while(current != head){
        std::cerr << current->value_ << ", ";
        current = current->next_;
    }
    std::cerr << std::endl;
}

void Sequence::createNode(Node* previousNode, const ItemType& value){
    Node * newNode = new Node(value, previousNode->next_, previousNode);
    previousNode->next_ = newNode;
    newNode->next_->prev_ = newNode;
    size_++;
}


