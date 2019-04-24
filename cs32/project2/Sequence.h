//
//  Sequence.h
//  cs32_Project2
//

#ifndef Sequence_H
#define Sequence_H

#include<string>
using ItemType = std::string;

class Sequence
{
public:
    
    // Create an empty sequence (i.e., one with no items)
    Sequence();
    
    // Copy constructor:
    Sequence(const Sequence& other);
    
    // Assignment operator:
    Sequence& operator=(const Sequence & rhs);
    
    // Deconstructor:
    ~Sequence();
    
    // Return true if the sequence is empty, otherwise false.
    bool empty() const;
    
    // Return the number of items in the sequence.
    int size() const;
    
    // Insert value into the sequence so that it becomes the item at
    // position pos. The original item at position pos and those that
    // follow it end up at positions one higher than they were at before.
    // Return pos if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return -1.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    int insert(int pos, const ItemType& value);
    
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item at position
    // p.  The original item at position p and those that follow it end
    // up at positions one higher than before.  Return p if the value
    // was actually inserted.  Return -1 if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).
    int insert(const ItemType& value);
    
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed that item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.
    bool erase(int pos);
    
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    int remove(const ItemType& value);
    
    // If 0 <= pos < size(), copy into value the item at position pos
    // of the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    bool get(int pos, ItemType& value) const;
    
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.
    bool set(int pos, const ItemType& value);
    
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    int find(const ItemType& value) const;
   
    // Exchange the contents of this sequence with the other one.
    void swap(Sequence& other);
    
    // The intent of this function is that for your own testing purposes,
    // you can call it to print information about the sequence; we will never call it.
    void dump() const;
    
private:
    struct Node{
        ItemType value_;
        Node* next_;
        Node* prev_;
        Node() {};
        Node(ItemType value, Node*next=nullptr, Node*previous=nullptr):value_(value), next_(next), prev_(previous) {};
    };
    Node* head;
    int size_;
    
    void createNode(Node* previousNode, const ItemType& value);
    
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // Sequence_H
