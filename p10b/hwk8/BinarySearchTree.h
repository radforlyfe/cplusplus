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
        
        /**
         deleteTree member function, removes all the nodes under the node n, including n
         @param n the subtree rooted at n
         */
        void deleteTree(node* n);
        
        /**
         traverseInsert member function, assists with copying from node n (making copy-from tree's root)
         @param n the subtree rooted at n
         */
        void traverseInsert(node* n);
        
    public:
        class iterator;               //nested iterator class
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
         Copy and Move assignment operator: makes the left value same as right value
         @param rhs the assigned-from Tree
         @return the updated assigned-to Tree
         */
        Tree& operator=(Tree rhs) &;
    
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
    std::ostream& operator<<(std::ostream& out, const Tree& tree);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Tree::node{
        friend Tree;                      //Tree member functions may search through nodes
        friend iterator;                  //to be able to advance by checking node values
    private:
        double value_;                    //the data
        node *left_, *right_, *parent_;   //pointers to left and right and parent nodes
        
        /**
         Constructor for Node: creates a new node, accepts double value and initializes left and right to nullptr
         @param value the value of the node
         */
        node(double value);
        
        bool insertNode(node* n);
        
         /**
         leftmost member function, finds and returns the leftmost child (move as far left as possible)
         */
        node* leftmost();
        
        /**
         rightmost member function, finds and returns the rightmost child (move as far right as possible)
         */
        node* rightmost();
        
        /**
         left_of_parent member function, returns true iff left child of its parent
         @return true iff it is a left child of its parent
         */
        bool left_of_parent();
        
        /**
         left_of_parent member function, returns true iff right child of its parent
         @return true iff it is a right child of its parent
         */
        bool right_of_parent();
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Tree::iterator{
        friend Tree;             //Tree may modify data of iterator during operations
    private:
        node* curr_;             //currently managed node
        const Tree* container_;  //holding container - iterator should not change the tree
        /**
         Constructor for iterator: creates a iterator, initializes pointer to node and Tree
         @param n pointer to node
         @param tree pointer to Tree
         */
        iterator(node* n, const Tree* tree);
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
        double operator*() const;
        
        /**
         arrow operator
         @return address of the current node
         */
        double* operator->() const;
        
        /**
         comparison operator== : compared lexicographically
         @param lhs iterator compared
         @param rhs iterator compared
         @return true if lhs is equal to rhs
         */
        friend bool operator==(const iterator& lhs, const iterator& rhs);
        
        /**
         member function, to print the tree
         @param out ostream parameter out
         @return ostream
         */
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
