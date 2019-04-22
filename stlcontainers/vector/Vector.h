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
        
// Constructors:
        
        // Default constructor:
        Vector(): size_(0), capacity_(0){
            reserve(INITIAL_CAPACITY);
        }
    
        Vector(size_type count, const T& value): size_(0), capacity_(0){
            reserve(GROWTH_FACTOR * count); // sets capacity_ to twice of count
            for(size_type index = 0; index < count; ++index){
                data_[index] = value;
            }
            size_ = count; // sets vector size to count
        }
  
        explicit Vector(size_type count) : Vector(count, "") {}
    
        Vector(std::initializer_list<T> init): size_(0), capacity_(0){
            size_type count = init.size();
            reserve(count);
            for(auto &element: init){
                push_back(element);
            }
            size_ = count;
        }
        
        // Copy constructor:
        Vector(const Vector& other): size_(0), capacity_(0){
            reserve(other.capacity()); // sets capacity_ to other.capacity
            copy_elements(other.data_.get(), data_.get(), other.size());
            size_ = other.size(); // copies vector size to other's size
        }
       
        // Move constructor:
        Vector( Vector&& other): Vector(){ // invoke the default constructor
            std::swap(data_, other.data_); // then swap their pointers
            std::swap(size_, other.size_); // then swap their sizes
            std::swap(capacity_, other.capacity_); // then swap their capacities
        }
        
// Operator=:
        
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
        
        // Returns an iterator to the first element of the container. If the container is empty, the returned iterator will be equal to end().
        iterator begin() noexcept{
            if(!empty()){
                return data_.get();}
            else{
                return end();
            }
        }
        
        const_iterator begin() const noexcept{
            if(!empty()){
                return data_.get();}
            else{
                return end();
            }
        }
        
        // Returns an iterator to the element following the last element of the container.
        // This element acts as a placeholder; attempting to access it results in undefined behavior.
        iterator end() noexcept{
            return (data_.get() + size());
        }
        
        const_iterator end() const noexcept{
            return (data_.get() + size());
        }
        
// Capacity:
        
        // Empty:
        bool empty() const noexcept { return (size()==0); }
        
        // Size:
        size_type size() const { return size_; }
        
        // Capacity:
        size_type capacity() const { return capacity_; }
        
        //Reserve member function:
        void reserve(size_type new_cap){
            if(new_cap <= capacity_){ // does not proceed further if new capacity is less than vector capcity
                return;
            }
            auto new_data = std::make_unique<value_type[]>(new_cap); // new pointer new_data
            copy_elements(data_.get(), new_data.get(), size_);
            data_.reset(new_data.release()); // delete previous memory
            capacity_ = new_cap - 1; // capacity_ is the new capacity
        }
        
// Modifiers:
        
        // Clear: Erases all elements from the container. After this call, size() returns zero.
        void clear() noexcept{
            size_=0;
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
        
        // DeleteAt member function: accepts an index value that removes the element at the given index and shifts all elements backwards.
        void deleteAt(size_type pos){
            if(pos>=0 && pos<size()){
                for(size_type index = pos; index< size()-1; ++index){ // copies one element ahead to element behind
                    data_[index] = data_[index+1];
                }
                size_--;
            }
        }
        
        // Push back member function: Adds an element to the end of the vector if the capacity allows.
        void push_back(const T& value){
            if(size_ == capacity_){
                reserve(GROWTH_FACTOR * capacity_); // sets to twice capacity
            }
            data_[size_] = value; // sets last element plus one to value
            size_++;
        }
        
        void push_back(T&& value){
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
        
// Element access:
        
        // At member function: Returns a reference to the element at specified location pos, with bounds checking.
        // If pos is not within the range of the container, an exception of type std::out_of_range is thrown.
        reference at( size_type pos ) {
            if(pos>=0 && pos<size()){
                return data_[pos];
            }
            else{
                throw std::out_of_range {"Vector::operator[]"};
            }
        }
        
        const_reference at( size_type pos ) const{
            if(pos>=0 && pos<size()){
                return data_[pos];
            }
            else{
                throw std::out_of_range {"Vector::operator[]"};
            }
        }
        
        // Returns a reference to the element at specified location pos. No bounds checking is performed.
        reference operator[] (size_type pos){
            return data_[pos];
        }
       
        const_reference operator[] (size_type pos) const{
            return data_[pos];
        }
        
        // Returns a reference to the first element in the container. Calling front on an empty container is undefined.
        reference front(){
            if(!empty()){
                return *data_;
            }
        }
        
        const_reference front() const{
            if(!empty()){
                return *data_;
            }
        }
        
        // Returns reference to the last element in the container. Calling back on an empty container is undefined.
        reference back(){
            if(!empty()){
                return *(data_ + size() - 1);
            }
        }
        
        const_reference back() const{
            if(!empty()){
                return *(data_ + size() - 1);
            }
        }
        
    private:
      
        size_type size_; // size of the vector
        size_type capacity_; // capacity of the vector
        std::unique_ptr<value_type[]> data_;
        
        void copy_elements(value_type* from, value_type* to, size_type count){
            for(size_type index = 0; index < count; ++index){
                to[index] = from[index];
            }
        }
        
    };
}

#endif /* Vector_H */
