//  Sequence.cpp
//  cs32_Project2
//

#include "Sequence.h"

// Create an empty sequence (i.e., one with no items)
Sequence::Sequence(): size_(0){ // making a dummy node
    head = new Node;
    head->next = head;
    head->previous = head;
}

// Copy constructor:
Sequence::Sequence(const Sequence& other){
    head = new Node;
    Node* thisC = head;
    Node* otherC = other.head->next;
    if(otherC != nullptr){
        for( ; otherC != other.head ; otherC = otherC->next){
            thisC->next = new Node;
            thisC->next->value = otherC->value;
            thisC->next->previous = thisC;
            thisC = thisC->next;
        }
    }
    size_ = other.size();
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
        Node * thisC = head;
        int count = 0;
        while(count != pos-1){
            thisC = thisC->next;
            count++;
        }
        Node * new_node = new Node;
        new_node->next = thisC->next;
        new_node->previous = thisC;
        thisC->next = new_node;
        new_node->next->previous = new_node;
        size_++;
        return pos;
    }
    else{
        return -1;
    }
}
