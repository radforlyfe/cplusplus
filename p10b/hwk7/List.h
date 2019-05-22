//
//  List.h
//  assignment7

#ifndef List_h
#define List_h
#include<iostream>
#include<stdexcept>

namespace pic10b{
    class node;                //declare the node
    class iterator;            //declare a normal iterator
    class const_iterator;      //declare an iterator to work on const LinkedList
    
    class LinkedList{
        friend iterator;       //iterator need to know first element
        friend const_iterator; //const_iterator need know first element
        /**
         swap function, swaps one LinkedList with another
         @param one the first LinkedList
         @param another the second LinkedList
         */
        friend void swap(LinkedList& one, LinkedList& another);
    public:
        /**
         Default constructor: makes an empty linked list with first and last initialized to nullptr
         */
        LinkedList() noexcept;
        
        /**
         Constructor that accepts a initializer list and stores these items in its LinkedList
         @param list the initializer list
         */
        LinkedList(const std::initializer_list<int>& list);
        
        /**
         Destructor
         */
        ~LinkedList();
        
        /**
         Copy constructor: makes a new independent copy of the other LinkedList
         @param other the LinkedList to copy from
         */
        LinkedList(const LinkedList& other);
        
        /**
         Move constructor: takes data from an rvalue of type LinkedList
         @param other the LinkedList reaching the end of its lifetime
         */
        LinkedList(LinkedList&& other) noexcept;
        
        /**
         Copy assignment operator: makes the left value same as right value
         @param other the assigned-from LinkedList
         @return the updated assigned-to LinkedList
         */
        LinkedList& operator=(const LinkedList& other) &;
        
        /**
         Move assignment operator: makes the left value same as right value by harvesting its resources
         @param other the assigned-from LinkedList
         @return the updated assigned-to LinkedList
         */
        LinkedList& operator=(LinkedList&& other) & noexcept;
        
        /**
         Push_back to append an int at the end
         @param value that is appended at the end
         */
        void push_back(int value);
        
        /**
         Push_front to prepend an int at the beginning
         @param value that is prepended at the beginning
         */
        void push_front(int value);
        
        /**
         pop_back to pop off the end element, throwing an exception if the list is empty
         */
        void pop_back();
        
        /**
         pop_front to pop off the first element, throwing an exception if the list is empty
         */
        void pop_front();
        
        /**
         begin member function, returning iterators to the first element
         */
        iterator begin();
        
        /**
         end member function, returning iterators to past-the-end (nullptr)
         */
        iterator end();
        
        /**
         begin member function overloaded on const, returning iterators to the first element
         */
        const_iterator begin() const;
        
        /**
         end member function overloaded on const, returning iterators to past-the-end (nullptr)
         */
        const_iterator end() const;
        
        /**
         insert function, inserts value before the point where the iterator points
         @param it the iterator points to the element
         @param value inserted before the pointed-to element
         */
        void insert(iterator it, int value);
        
        /**
         erase function, removes the pointed-to element
         @param it the iterator points to the element
         */
        void erase(iterator it);
        
        /**
         size function, returns the number of elements in the list
         */
        std::size_t size() const;
    
        /**
         sort function, sorts the elements in ascending order from beginning to end
         */
        void sort();
    private:
        node *first, *last;  //pointers to first and last node
        size_t size_;
    };
    
    /**
     operator<< function, overloaded to display all the elements of the list
     */
    std::ostream& operator<<(std::ostream& out, const LinkedList&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class node{
        friend LinkedList;     //LinkedList needs to construct nodes and know next/prev of nodes for insertion/deletion
        friend iterator;       //iterator need to know next/prev to move
        friend const_iterator; //const_iterator needs to know next/prev to move
    private:
        int val;               //the data
        node *prev, *next;     //pointers to prev and next nodes
        /**
         Constructor for Node: creates a new node, accepts int value and initializes prev and next to nullptr
         @param i value of the node
         */
        node(int i);
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class iterator{
        friend LinkedList; //LinkedList may change data of iterator during operations
    public:
        /**
         prefix (unary) operator++: the pointer to current node is incremented by 1
         @return reference to iterator incremented by 1
         */
        iterator& operator++();
        
        /**
         postfix(binary) operator++: the pointer to current node is incremented by 1
         @param unused parameter
         @return copy of the iterator (no change)
         */
        iterator operator++(int unused);
        
        /**
         prefix (unary) operator--: the pointer to current node is decremented by 1
         @return reference to iterator decremented by 1
         */
        iterator& operator--();
        
        /**
         postfix(binary) operator--: the pointer to current node is decremented by 1
         @param unused parameter
         @return copy of the iterator (no change)
         */
        iterator operator--(int unused);
        
        /**
         dereference operator for iterator
         @return reference to the int stored
         */
        int& operator*() const;
        
        /**
         comparison operator== : compared lexicographically
         @param lhs iterator compared
         @param rhs iterator compared
         @return true if lhs is equal to rhs
         */
        friend bool operator==(const iterator& lhs, const iterator& rhs);
        
        /**
         conversion operator that converts iterator to const_iterator
         @return const_iterator converted from iterator
         */
        operator const_iterator() const;
    private:
        node *curr;                  //currently managed node
        const LinkedList *container; //the iterator should not change the LinkedList
        /**
         Constructor for iterator: creates a iterator, initializes pointer to node and LinkedList
         @param n pointer to node
         @param ll pointer to LinkedList
         */
        iterator(node* n, const LinkedList* ll);
    };
    
    bool operator==(const iterator&, const iterator&); //Redeclared to allow for fully qualified lookup (Argument Dependent Lookup)
    
    /**
     comparison operator!= : compared lexicographically
     @param lhs iterator compared
     @param rhs iterator compared
     @return true if lhs is not equal to rhs
     */
    bool operator!=(const iterator& lhs, const iterator& rhs);
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class const_iterator{
        friend LinkedList; //LinkedList may change data of iterator during operations
        friend iterator;   //iterator may change data of const_iterator during operations
    public:
        /**
         prefix (unary) operator++: the pointer to current node is incremented by 1
         @return reference to const_iterator incremented by 1
         */
        const_iterator& operator++();
        
        /**
         postfix(binary) operator++: the pointer to current node is incremented by 1
         @param unused parameter
         @return copy of the const_iterator (no change)
         */
        const_iterator operator++(int unused);
        
        /**
         prefix (unary) operator--: the pointer to current node is decremented by 1
         @return reference to const_iterator decremented by 1
         */
        const_iterator& operator--();
        
        /**
         postfix(binary) operator--: the pointer to current node is decremented by 1
         @param unused parameter
         @return copy of the const_iterator (no change)
         */
        const_iterator operator--(int unused);
        
        /**
         dereference operator for const_iterator
         @return copy of the int stored
         */
        int operator*() const;
        
        /**
         comparison operator== : compared lexicographically
         @param lhs const_iterator compared
         @param rhs const_iterator compared
         @return true if lhs is equal to rhs
         */
        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs);
    private:
        node *curr;                  //currently managed node
        const LinkedList *container; //the iterator should not change the list
        
        /**
         Constructor for const_iterator: creates a const_iterator, initializes pointer to node and LinkedList
         @param n pointer to node
         @param ll pointer to LinkedList
         */
        const_iterator(node* n, const LinkedList* ll);
    };
    
    bool operator==(const const_iterator&, const const_iterator&); //Redeclared to allow for fully qualified lookup (Argument Dependent Lookup)
    
    /**
     comparison operator!= : compared lexicographically
     @param lhs const_iterator compared
     @param rhs const_iterator compared
     @return true if lhs is not equal to rhs
     */
    bool operator!=(const const_iterator& lhs, const const_iterator& rhs);
    
    /**
     seqSearch function, searches over the range provided by the iterators from first iterator upto but not including the second iterator
     @param it1 the first iterator
     @param it2 the second iterator
     @param value searches this value over the range of LinkedList
     */
    bool seqSearch(const const_iterator& it1, const const_iterator& it2, const int value);
    
}
#endif /* List_h */
