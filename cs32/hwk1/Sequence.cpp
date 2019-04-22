//
//  Sequence.cpp
//  cs32_Assignment1
//
//  Created by Radhika Nayar on 4/14/19.
//  Copyright © 2019 Radhika Nayar. All rights reserved.
//

#include "Sequence.h"

// Create an empty sequence (i.e., one with no items)
Sequence::Sequence(): m_size(0) {}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const{
    if(m_size==0){
        return true;}
    return false;
}
// OR can write in one line: return m_size == 0

// Return the number of items in the sequence.
int Sequence::size() const{
    return m_size;
}


// Insert value into the sequence so that it becomes the item at position pos.
// The original item at position pos and those that follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be inserted.
// (It might not be, if the sequence has a fixed capacity, e.g., because it's implemented using a fixed-size array.)
// Otherwise, leave the sequence unchanged and return -1.
// Notice that if pos is equal to size(), the value is inserted at the end.
int Sequence::insert(int pos, const ItemType& value){
    if(size() != DEFAULT_MAX_ITEMS){
        if(pos >=0 && pos<= size()){ 
            for(int i = size()-1; i >= pos; i--){
                m_array[i+1] = m_array[i];
            // for(int i = size(); i > pos; i--){ // does the same!!!
             //   m_array[i] = m_array[i-1];
            }
            m_array[pos] = value;
            m_size++;
            return pos;
        }
    }
    return (-1);
}


// Let p be the smallest integer such that value <= the item at position p in the sequence;
// if no such item exists (i.e., value > all items in the sequence), let p be size().
// Insert value into the sequence so that it becomes the item at position p.
// The original item at position p and those that follow it end up at positions one higher than before.
// Return p if the value was actually inserted.
// Return -1 if the value was not inserted (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value){
    if(size()==DEFAULT_MAX_ITEMS){
        return -1;
    }
    for(int p = 0; p<size(); p++){
        if(value <= m_array[p]){
            for(int j = size(); j>p; j--){ /// loop equal signs?
                m_array[j]= m_array[j-1];}
            m_array[p] = value;
            m_size++;
            return p;
        }
    }
    int p = size();
    m_array[p] = value;
    m_size++;
    return p;
}


// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos){
    if(pos>=0 && pos<size()){
        for(int i = pos; i <size()-1; i++){
            m_array[i]=m_array[i+1];
        }
        m_size--;
        return true;
    }
    return false;
}


// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value){
    int count = 0;
    for(int p = 0; p<size();++p){
        if(m_array[p]==value){
            erase(p);
            count++;
            p--;
            }
        }
    return count;
}



// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged and return false.
bool Sequence::get(int pos, ItemType& value) const{
    if(pos>=0 && pos<size()){
        value = m_array[pos];
        return true;
    }
    return false;
}


// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value){
    if(pos>=0 && pos<size()){
        m_array[pos]=value;
        return true;
    }
    return false;
}


// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const{
   // int p = -1;  /// does it have p = -1 after the loop? and not found?
    for(int p =0; p<size(); p++){
        if(m_array[p] == value){
            return p;}
    }
    int p = -1;
    return p;
}


// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other){
    int bigger_size = size();
    if(size()<other.size())
        bigger_size = other.size();
    
    for(int i = 0; i<bigger_size; i++){
        ItemType temp;
        temp = m_array[i];
        m_array[i] = other.m_array[i];
        other.m_array[i] = temp;

// Only works until the smaller size
//        ItemType otherItem;
//        get(i, temp);              // temp = m_array[i]
//        other.get(i, otherItem);   // otherItem = other.m_array[i]
//        set(i, otherItem);         // m_array[i] = otherItem
//        other.set(i, temp);        // other.m_array[i] = temp
    }
        int temp_size = m_size;
        m_size = other.m_size;
        other.m_size = temp_size;
}


// The intent of this function is that for your own testing purposes,
// you can call it to print information about the sequence; we will never call it.
void Sequence::dump() const{
    for(int i=0; i<size(); i++){
        std::cerr<< m_array[i]<< ",";
    }
    std::cerr<< std::endl;
}
