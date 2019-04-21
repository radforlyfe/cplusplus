/**
 @file Vector.h
 */

#ifndef Vector_H
#define Vector_H

#include <memory>
#include<string>





namespace STLContainer{
   
    template<typename T>
  
    class Vector{
        
        constexpr static size_t INITIAL_CAPACITY = 1;
        constexpr static size_t GROWTH_FACTOR = 2;
        
    public:
        
        // Type Definitions:
        using size_type = size_t; // alias
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reference = value_type&;
        using const_reference = const value_type&;
        
        Vector(): size_(0), capacity_(0){
            reserve(INITIAL_CAPACITY);
        }
    
        Vector(size_type count, const T& value): size_(0), capacity_(0){
            reserve(GROWTH_FACTOR * count); // sets capacity_ to twice of count
            for(size_type index = 0; index < count; ++index){ // initializes all string variables to value
                data_[index] = value;
            }
            size_ = count; // sets vector size to count
        }
  
        
        Vector(size_type count) : Vector(count, "") {}
    
        
        // Copy constructor:
        Vector(const Vector& other): size_(0), capacity_(0){
            reserve(other.capacity()); // sets capacity_ to other.capacity
            for(size_t index = 0; index < other.size(); ++index){ // copies each element of data_ equal to the elements of other.data_
                data_[index] = other.data_[index];
            }
            size_ = other.size(); // copies vector size to other's size
        }
       
        // Move constructor:
        Vector( Vector&& other): Vector(){ // invoke the default constructor
            std::swap(data_, other.data_); // then swap their pointers
            std::swap(size_, other.size_); // then swap their sizes
            std::swap(capacity_, other.capacity_); // then swap their capacities
        }
       
        
        // Copy assignment:
        Vector& operator=(const Vector& other){
            Vector output(other);
            std::swap(data_, output.data_); // self-assignment
            size_ = other.size();
            capacity_ = other.capacity();
            return *this;
        }
        
        
        // Move assignment:
        Vector& operator=(Vector&& other){
            std::swap(data_, other.data_); // then swap their pointers
            std::swap(size_, other.size_); // then swap their sizes
            std::swap(capacity_, other.capacity_); // then swap their capacities
            return *this;
        }
        
       
        
        // Iterators:
        
//        iterator begin() noexcept;
//
//        const_iterator begin() const noexcept;
//
//        const_iterator cbegin() const noexcept;
        
        
        // Empty:
        bool empty() const noexcept{
            return (size()==0);
        }
        
        // Clear: Erases all elements from the container. After this call, size() returns zero.
        void clear() noexcept{
            size_=0;
        }
        
        // Size member function
        size_type size() const{
            return size_; // return size
        }
        
        // Capacity member function
        size_type capacity() const{
            return capacity_; // returns capacity
        }
        
        //Reserve member function:
        void reserve(size_type new_cap){
            if(new_cap <= capacity_){ // does not proceed further if new capacity is less than vector capcity
                return;
            }
            auto new_data = std::make_unique<value_type[]>(new_cap); // new pointer new_data
            // copy each element from data_ to new_data
            for(size_type index = 0; index < size_; ++index){ // copies all elements in vector to new_data vector with new capacity
                new_data[index] = data_[index];
            }
            data_.reset(new_data.release()); // delete previous memory
            //data_ = new_data; // data_ now points to the new memory location
            capacity_ = new_cap; // capacity_ is the new capacity
        }
        
        
        
        // Push back member function: Adds an element to the end of the vector if the capacity allows.
        void push_back(const T& value){
            if(size_ == capacity_){
                reserve(GROWTH_FACTOR * capacity_); // sets to twice capacity
            }
            data_[size_] = value; // sets last element plus one to value
            size_++;
        }
        
        // Pop Back member function: removes the last element of the vector by updating the size of the vector.
        void pop_back(){
            if(size()!=0){
                size_--; // deletes one element as long as size is not zero
            }
        }
        
        // DeleteAt member function: accepts an index value that removes the element at the given index and shifts all elements backwards.
        void deleteAt(size_type pos){
            if(pos>=0 && pos<size()){
                for(size_type index = pos; index< size()-1; ++index){ // copies one element ahead to element behind
                    data_[index] = data_[index+1];
                }
                size_--;
            }
        }
        
        // InsertAt member function:
        void insertAt(size_type pos, T value){
            if(pos<0 && pos>size()){
                return;
            }
            if(size_ == capacity_){
                reserve(GROWTH_FACTOR * capacity_);
            }
            for(size_type index = size(); index > pos; --index){ // moves all element one ahead
                data_[index] = data_[index-1];
            }
            data_[pos]= value; // sets value to pos index
        }
        
        
        // At member function: Accepts an index value that returns the element at the given index by reference or reference to const.
        T& at( size_type pos ) {
            return data_[pos]; // gives value at pos
        }
        
        // At member function: Accepts an index value that returns the element at the given index by reference or reference to const.
        const T& at( size_type pos ) const{
            return data_[pos]; // gives value at pos
        }
        
        
       
        
    private:
      
        size_type size_; // size of the vector
        size_type capacity_; // capacity of the vector
        std::unique_ptr<value_type[]> data_;
        
        
    };
}

#endif /* Vector_H */
