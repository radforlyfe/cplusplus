
/**
 @file VectorString.cpp
 */

#include "VectorString.h"

namespace pic10b{ // open up the namespace
    
    // Default Constructor: size is 0, capacity is 1 (initial_capacity), ptr points to dynamic array of string of one element
    VectorString::VectorString(): vec_size(0), vec_capacity(0){
        reserve(INITIAL_CAPACITY);
    }
    
    
    // Constructor2: accepts size (count) and input string (value).
    // Allocates a dynamic array with size as count, capacity as twice count and initializes all string variables to value.
    VectorString::VectorString(size_type count, const std::string& value): vec_size(0), vec_capacity(0){
        reserve(GROWTH_FACTOR * count); // sets vec_capacity to twice of count
        for(size_type index = 0; index < count; ++index){ // initializes all string variables to value
            data_[index] = value;
        }
        vec_size = count; // sets vector size to count
    }
    
    
    // Constructor3: accepts size (count).
    // Allocates a dynamic array with size as count, capacity as twice count and initializes all string variables to empty string.
    VectorString::VectorString(size_type count) : VectorString(count, "") {} // calls constructor2 with parameter count and " "
    
    
    // Copy constructor:
    VectorString::VectorString(const VectorString& other): vec_size(0), vec_capacity(0){
        reserve(other.capacity()); // sets vec_capacity to other.capacity
        for(size_t index = 0; index < other.size(); ++index){ // copies each element of data_ equal to the elements of other.data_
            data_[index] = other.data_[index];
        }
        vec_size = other.size(); // copies vector size to other's size
    }
    
    
    // Move constructor:
    VectorString::VectorString( VectorString&& other): VectorString(){ // invoke the default constructor
        std::swap(data_, other.data_); // then swap their pointers
        std::swap(vec_size, other.vec_size); // then swap their sizes
        std::swap(vec_capacity, other.vec_capacity); // then swap their capacities
    }
    
    
    // Copy assignment:
    VectorString& VectorString::operator=(const VectorString& other){
        VectorString output(other);
        std::swap(data_, output.data_); // self-assignment
        vec_size = other.size();
        vec_capacity = other.capacity();
        return *this;
    }
    
    
    // Move assignment:
    VectorString& VectorString::operator=(VectorString&& other){
        std::swap(data_, other.data_); // then swap their pointers
        std::swap(vec_size, other.vec_size); // then swap their sizes
        std::swap(vec_capacity, other.vec_capacity); // then swap their capacities
        return *this;
    }
    
    
    // Reserve member function: Increase the capacity of the vector to a value that is greater or equal to new_cap.
    // If new_cap is greater than the current capacity(), new storage is allocated, otherwise the method does nothing.
    // Does not change the size of the vector.
    void VectorString::reserve(size_type new_cap){
        if(new_cap <= vec_capacity){ // does not proceed further if new capacity is less than vector capcity
            return;
        }
        auto new_data = std::make_unique<std::string[]>(new_cap); // new pointer new_data
        // copy each element from data_ to new_data
        for(size_type index = 0; index < vec_size; ++index){ // copies all elements in vector to new_data vector with new capacity
            new_data[index] = data_[index];
        }
        data_.reset(new_data.release()); // delete previous memory
        //data_ = new_data; // data_ now points to the new memory location
        vec_capacity = new_cap; // vec_capacity is the new capacity
    }
    
    bool VectorString::empty() const{
        return (size()==0);
    }
    
    // Size member function: returns the size of the vector.
    size_type VectorString::size() const{
        return vec_size;
    }
    
    // Capacity member function: returns the capacity of the vector.
    size_type VectorString::capacity() const{
        return vec_capacity;
    }
    
    // Push back member function: accepts a string.
    // Adds an element to the end of the vector if the capacity allows.
    // Otherwise creates a new dynamic array of twice the former capacity - moving all the elements over and adding the new element.
    void VectorString::push_back(const std::string& value){
        if(vec_size == vec_capacity){
            reserve(GROWTH_FACTOR * vec_capacity); // sets to twice capacity
        }
        data_[vec_size] = value; // sets last element plus one to value
        vec_size++;
    }
    
    // Pop Back member function: removes the last element of the vector by updating the size of the vector.
    void VectorString::pop_back(){
        if(size()!=0){
            vec_size--; // deletes one element as long as size is not zero
        }
    }
    
    // DeleteAt member function: accepts an index value that removes the element at the given index and shifts all elements backwards.
    void VectorString::deleteAt(size_type pos){
        if(pos>=0 && pos<size()){
            for(size_type index = pos; index< size()-1; ++index){ // copies one element ahead to element behind
                data_[index] = data_[index+1];
            }
            vec_size--;
        }
    }
    
    // InsertAt member function:
    void VectorString::insertAt(size_type pos, std::string value){
        if(pos<0 && pos>size()){
            return;
        }
        if(vec_size == vec_capacity){
            reserve(GROWTH_FACTOR * vec_capacity);
        }
        for(size_type index = size(); index > pos; --index){ // moves all element one ahead
            data_[index] = data_[index-1];
        }
        data_[pos]= value; // sets value to pos index
        vec_size++;
    }
    
    
    // At member function: Accepts an index value that returns the element at the given index by reference or reference to const.
    std::string& VectorString::at( size_type pos ) {
        return data_[pos]; // gives value at pos
    }
    
    // At member function: Accepts an index value that returns the element at the given index by reference or reference to const.
    const std::string& VectorString::at( size_type pos ) const{
        return data_[pos]; // gives value at pos
    }
}
