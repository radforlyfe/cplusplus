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
