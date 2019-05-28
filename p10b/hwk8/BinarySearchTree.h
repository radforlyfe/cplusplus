//
//  BinarySearchTree.h
//  p10b_assignment8

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include<iostream>

namespace pic10b{
    
    class Tree{
    private:
        class node;                   //nested node class
        node *root_;                  //the root of the tree
        size_t size_;
        void deleteTree(node*);       //to recursively delete the tree
        void traverseInsert(node*);   //to help with copying
    public:
        class iterator;               //nested iterator class
        /**
         Default constructor: makes an empty tree with root initialized to nullptr
         */
        Tree() noexcept;
        
//        /**
//         Destructor
//         */
//        ~Tree();
//        
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
         @return iterator to the node with a given value if found, else past-the-end iterator
         */
        iterator find(const double value) const;
        
        /**
         insert function, inserts node with value into Tree
         @param value inserted into Tree
         */
        void insert(double value);
        
        /**
         erase function, removes the pointed-to node managed by the iterator from the Tree
         @param it the iterator pointing to the node
         */
        void erase(iterator it);
        
        /**
         begin member function, returning an iterator to the first node
         */
        iterator begin() const;
        
        /**
         end member function, returning an iterator to past-the-end (one past the final node)
         */
        iterator end() const;
        
        /**
         size function, returns the number of elements in the Tree
         */
        size_t size() const;
    };
    
    void swap(Tree& one, Tree& another);                               //redeclared at namespace level - to allow for fully qualified lookup (ADL)
    std::ostream& operator<<(std::ostream out, const Tree& tree);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Tree::node{
        friend Tree;                      //Tree member functions may search through nodes
        friend iterator;                  //to be able to advance by checking node values
    private:
        double value_;                    //the data
        node *left, *right, *parent;      //pointers to left and right and parent nodes
        /**
         Constructor for Node: creates a new node, accepts double value and initializes left and right to nullptr
         @param value the value of the node
         */
        node(double value);
        node* leftmost(node *root);
        node* rightmost();
        
        bool insertNode(node*);
        
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Tree::iterator{
        friend Tree;            //Tree may modify data of iterator during operations
    private:
        node *curr;             //currently managed node
        const Tree *container;  //holding container - iterator should not change the tree
        /**
         Constructor for iterator: creates a iterator, initializes pointer to node and Tree
         @param n pointer to node
         @param tree pointer to Tree
         */
        iterator(node *n, const Tree *tree);
    public:
        /**
         prefix (unary) operator++: the pointer to current node is incremented by 1
         @return reference to iterator incremented by 1
         */
        iterator& operator++();
        
        /**
         postfix (binary) operator++: the pointer to current node is increment by 1
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
         postfix (binary) operator--: the pointer to current node is decremented by 1
         @param unused parameter
         @return copy of the iterator (no change)
         */
        iterator operator--(int unused);
        
        /**
         dereference operator
         @return returns the double is stored
         */
        const double& operator*() const;
        
        /**
         arrow operator
         @return address of the current node
         */
        const double* operator->() const;
        
        /**
         comparison operator== : compared lexicographically
         @param lhs iterator compared
         @param rhs iterator compared
         @return true if lhs is equal to rhs
         */
        friend bool operator==(const iterator& lhs, const iterator& rhs);
        
        std::ostream& output_it(std::ostream& out) const;
    };

    bool operator==(const Tree::iterator& lhs, const Tree::iterator& rhs);   //redeclared at namespace - to allow for fully qualified lookup (ADL)
    
    /**
     comparison operator!= : compared lexicographically
     @param lhs iterator compared
     @param rhs iterator compared
     @return true if lhs is not equal to rhs
     */
    bool operator!=(const Tree::iterator& lhs, const Tree::iterator& rhs);
}

#endif /* BinarySearchTree_h */
