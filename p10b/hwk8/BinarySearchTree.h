//
//  BinarySearchTree.h
//  p10b_assignment8

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include<iostream>

namespace pic10b{
    
    class Tree{
    private:
        class node;                  //nested node class
        node *root;                  //the root of the tree
        size_t size_;
        void deleteTree(node*);      //to recursively delete the tree
        void traverseInsert(node*);  //to help with copying
    public:
        class const_iterator;        //nested iterator class
        /**
         Default constructor: makes an empty tree with root initialized to nullptr
         */
        Tree() noexcept;
        
        /**
         Destructor
         */
        ~Tree();
        
        /**
         Copy constructor: makes a new independent copy of the other Tree
         @param other the Tree to copy from
         */
        Tree(const Tree& other);
        
        /**
         Move constructor: takes data from an rvalue of type Tree
         @param other the Tree reaching the end of its lifetime
         */
        Tree(Tree&& other) noexcept;
        
        /**
         Copy assignment operator: makes the left value same as right value
         @param rhs the assigned-from Tree
         @return the updated assigned-to Tree
         */
        Tree& operator=(const Tree& rhs) &;
        
        /**
         Move assignment operator: makes the left value same as right value by harvesting its resources
         @param rhs the assigned-from Tree
         @return the updated assigned-to Tree
         */
        Tree& operator=(Tree&& rhs) &;
        
        /**
         swap function, swaps one Tree with another
         @param one the first Tree
         @param another the second Tree
         */
        friend void swap(Tree& one, Tree& another);
        
        /**
         find function,searches over the range of the Tree for the given value
         @param value searches this value over the range of the Tree
         @return const_iterator to the node with a given value if found, else past-the-end iterator
         */
        const_iterator find(const double value) const;
        
        /**
         insert function, inserts node with value into Tree
         @param value inserted into Tree
         */
        void insert(double value);
        
        /**
         erase function, removes the pointed-to node managed by the iterator from the Tree
         @param it the iterator pointing to the node
         */
        void erase(const_iterator it);
        
        /**
         begin member function, returning an iterator to the first node
         */
        const_iterator begin() const;
        
        /**
         end member function, returning an iterator to past-the-end (one past the final node)
         */
        const_iterator end() const;
        
        /**
         size function, returns the number of elements in the Tree
         */
        size_t size() const;
    };

    void swap(Tree& one, Tree& another);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Tree::node{
        friend Tree;            //Tree member functions may search through nodes
        friend const_iterator;  //to be able to advance by checking node values
    private:
        double value_;          //the data
        node *left, *right;     //pointers to left and right
        /**
         Constructor for Node: creates a new node, accepts double value and initializes left and right to nullptr
         @param value the value of the node
         */
        node(double value);
        
        void insertNode(node*);
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Tree::const_iterator{
        friend Tree;            //Tree may modify data of iterator during operations
    private:
        node *curr;             //currently managed node
        const Tree *container;  //holding container - iterator should not change the tree
        /**
         Constructor for const_iterator: creates a const_iterator, initializes pointer to node and Tree
         @param n pointer to node
         @param t pointer to Tree
         */
        const_iterator(node *n, const Tree *t);
    public:
        /**
         prefix (unary) operator++: the pointer to current node is incremented by 1
         @return reference to const_iterator incremented by 1
         */
        const_iterator& operator++();
        
        /**
         postfix (binary) operator++: the pointer to current node is increment by 1
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
         postfix (binary) operator--: the pointer to current node is decremented by 1
         @param unused parameter
         @return copy of the const_iterator (no change)
         */
        const_iterator operator--(int unused);
        
        /**
         dereference operator
         @return copy of the int stored??????????
         */
        const double& operator*() const;
        
        /**
         arrow operator
         @return address of the current node
         */
        const double* operator->() const;
        
        /**
         comparison operator== : compared lexicographically
         @param lhs const_iterator compared
         @param rhs const_iterator compared
         @return true if lhs is equal to rhs
         */
        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs);
    };

    bool operator==(const Tree::const_iterator& lhs, const Tree::const_iterator& rhs); //Redeclared to allow for fully qualified lookup (Argument Dependent Lookup)
    
    /**
     comparison operator!= : compared lexicographically
     @param lhs const_iterator compared
     @param rhs const_iterator compared
     @return true if lhs is not equal to rhs
     */
    bool operator!=(const Tree::const_iterator& lhs, const Tree::const_iterator& rhs);
}

#endif /* BinarySearchTree_h */
