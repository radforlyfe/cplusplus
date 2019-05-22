//
//  List.h
//  assignment7

#ifndef List_h
#define List_h
#include<iostream>
#include<stdexcept>

namespace pic10b{
    class node;
    class iterator;
    class const_iterator;
    
    class LinkedList{
        friend iterator;
        friend const_iterator;
        friend void swap(LinkedList&, LinkedList&);
    public:
        LinkedList() noexcept;
        LinkedList(const std::initializer_list<int>& list);
        ~LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList(LinkedList&& other) noexcept;
        LinkedList& operator=(const LinkedList& other) &;
        LinkedList& operator=(LinkedList&& other) & noexcept;
        void push_back(int);
        void push_front(int);
        void pop_back();
        void pop_front();
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        void insert(iterator, int value);
        void erase(iterator);
        std::size_t size() const;
        void swap_adj_elt(iterator& left, iterator& right);
        void sort();
    private:
        node *first, *last;
        size_t size_;
    };
    
    std::ostream& operator<<(std::ostream& out, const LinkedList&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class node{
        friend LinkedList;
        friend iterator;
        friend const_iterator;
    private:
        int val;
        node *prev, *next;
        node(int i);
    };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class iterator{
        friend LinkedList;
    public:
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        int& operator*() const;
        friend bool operator==(const iterator&, const iterator&);
        operator const_iterator() const;
    private:
        node *curr;
        const LinkedList *container;
        iterator(node*, const LinkedList*);
    };
    
    bool operator==(const iterator&, const iterator&);
    bool operator!=(const iterator&, const iterator&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class const_iterator{
        friend LinkedList;
        friend iterator;
    public:
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        int operator*() const;
        friend bool operator==(const const_iterator&, const const_iterator&);
    private:
        node *curr;
        const LinkedList *container;
        const_iterator(node*, const LinkedList*);
    };
    
    bool operator==(const const_iterator&, const const_iterator&);
    bool operator!=(const const_iterator&, const const_iterator&);
    bool seqSearch(const const_iterator&, const const_iterator&, const int);
    
}
#endif /* List_h */
