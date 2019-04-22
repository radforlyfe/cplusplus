/**
 @file VectorString.h
 */

#ifndef VectorString_H
#define VectorString_H

#include <memory>
#include<string>


namespace pic10b{ // declaring namespace pic10b
    
    using size_type = size_t; // alias
    
    /**
     This class mimics the behaviour of a std::string
     */
    class VectorString{
        
        constexpr static size_t INITIAL_CAPACITY = 1;
        constexpr static size_t GROWTH_FACTOR = 2;
        
    public:
        
        /**
        Default Constructor: size is 0, capacity is 1 (initial_capacity), ptr points to dynamic array of string of one element
         */
        VectorString();
        
        /**
        Constructor2: Allocates a dynamic array with size as count, capacity as twice count and initializes all string variables to value.
        @param count size of the vector
        @param value string value
        */
        VectorString(size_type count, const std::string& value);
        
        /** Constructor3: Allocates a dynamic array with size as count, capacity as twice count and initializes all string variables to empty string.
        @param count size of the vector
        */
        VectorString(size_type count);
       
        /**
        Copy constructor: makes a new independent copy of the other VectorString
        @param other the VectorString to copy from
        */
        VectorString(const VectorString& other);
        
        /**
        Move constructor: takes data from an rvalue of type VectorString
        @param other the VectorString reaching the end of its lifetime
        */
        VectorString(VectorString&& other);
        
        /**
        Copy assignment operator, makes left value same as right value
        @param other the assigned-from VectorString
        @return the updated assigned-to VectorString
        */
        VectorString& operator=(const VectorString& other);
        
        /**
        Move assignment operator, makes left value same as right value by harvesting its resources
        @param other the assigned-from VectorString
        @return the updated assigned-to VectorString
        */
        VectorString& operator=(VectorString&& other);
        
        /**
        Checks if the container has no elements, i.e. whether begin() == end()
        @return true if the container is empty, false otherwise
        */
        bool empty() const;
        
        /**
        Size member function, returns the size of the vector
        @return size of the vector
        */
        size_type size() const;
        
        /**
        Capacity member function, returns the capacity of the vector
        @return capacity of the vector
        */
        size_type capacity() const;
        
        /**
         Reserve member function, increases the capacity of the vector to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(), new storage is allocated, otherwise the method does nothing.
        @param new_cap new capacity inputted
        */
        void reserve(size_type new_cap);
        
        /**
         Push Back member function, adds an element to the end of the vector if the capacity allows. Otherwise creates a new dynamic array of twice the former capacity - moving all the elements over and adding the new element.
        @param value is the string value
        */
        void push_back(const std::string& value);
    
        /**
        Pop Back member function, removes the last element of the vector by updating the size of the vector
        */
        void pop_back();
        
        /**
        DeleteAt member function: accepts an index value that removes the element at the given index and shifts all elements backwards.
        @param pos is the position at which the string value should be deleted
         */
        void deleteAt (size_type pos);
        
        /**
        InsertAt member function, adds an element to the pos of the vector if the capacity allows. Otherwise creates a new dynamic array of twice the former capacity - moving all the elements over and adding the new element at pos
        @param pos is the position at which the value string should be inserted
        @param value is the string value
        */
        void insertAt (size_type pos, std::string value);
        
        /**
        At member function: return by reference, the value at the position index
        @param pos is the position at which the value of string is returned
        @return value of the string at position pos
        */
        std::string& at(size_type pos);
        
        /**
        At member function overloaded on const: return by reference to const, the value at the position index
        @param pos is the position at which the value of string is returned
        @return value of the string at position pos
        */
        const std::string& at(size_type pos) const;
       
    private:
      
        size_type vec_size; // size of the vector
        size_type vec_capacity; // capacity of the vector
        std::unique_ptr<std::string[]> data_; // pointer to the dynamic array of string vector, defaulted to nullptr
        
    };
}

#endif /* VectorString_H */
