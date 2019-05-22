//
//  List.cpp
//  assignment7

#include "List.h"

namespace pic10b{
    
    LinkedList::LinkedList() noexcept: first(nullptr), last(nullptr) {}
    
    LinkedList::LinkedList(std::initializer_list<int> list): first(nullptr), last(nullptr){
        for(auto i : list){
            push_back(i);
        }
    }
    
    LinkedList::~LinkedList(){
        while(first != nullptr){
            erase(begin());
        }
    }
    
    void swap(LinkedList& one, LinkedList& another){
        std::swap(one.first, another.first);
        std::swap(one.last, another.last);
        std::swap(one.size_, another.size_);
    }
    
    LinkedList::LinkedList(const LinkedList& other): first(nullptr), last(nullptr){
        for(int i : other){
            push_back(i);
        }
    }

    LinkedList::LinkedList(LinkedList&& other) noexcept: LinkedList(){
        swap(*this, other);
    }
    
    LinkedList& LinkedList::operator=(const LinkedList& other) &{
        if(this != &other){
            LinkedList temp(other);
            swap(*this, temp);
        }
        return *this;
    }
            
    LinkedList& LinkedList::operator=(LinkedList&& other) & noexcept{
        swap(*this, other);
        return *this;
    }
    
    void LinkedList::push_back(int value){
        node *n = new node(value);
        if(!last){
            first = last = n;
        }
        else{
            last->next = n;
            n->prev = last;
            last = n;
        }
        ++size_;
    }
    
    void LinkedList::push_front(int value){
        node *n = new node(value);
        if(!first){
            first = last = n;
        }
        else{
            first->prev = n;
            n->next = first;
            first = n;
        }
        ++size_;
    }
    
    void LinkedList::pop_back(){
        if(!last){
            throw std::logic_error("pop back on an empty list");
        }
        else if(first == last){
            delete first;
            first = last = nullptr;
            --size_;
        }
        else{
            node * newlast = last->prev;
            newlast->next = nullptr;
            delete last;
            last = newlast;
            --size_;
        }
    }
    
    void LinkedList::pop_front(){
        if(!first){
            throw std::logic_error("pop back on an empty list");
        }
        else if(first == last){
            delete first;
            first = last = nullptr;
            --size_;
        }
        else{
            node * newfirst = first->next;
            newfirst->prev = nullptr;
            delete first;
            first = newfirst;
            --size_;
        }
    }
    
    iterator LinkedList::begin(){
        return iterator(first, this);
    }
    iterator LinkedList::end(){
        return iterator(nullptr, this);
    }
    const_iterator LinkedList::begin() const{
        return const_iterator(first, this);
    }
    const_iterator LinkedList::end() const{
        return const_iterator(nullptr, this);
    }
    
    void LinkedList::insert(iterator it, int value){
        if(it.curr == nullptr){
            push_back(value);
        }
        else if(it.curr == first){
            push_front(value);
        }
        else{
            node *n = new node(value);
            n->next = it.curr;
            n->prev = it.curr->prev;
            it.curr->prev->next = n;
            it.curr->prev = n;
            ++size_;
        }
    }
    
    void LinkedList::erase(iterator it){
        if(it.curr == first){
            pop_front();
        }
        else if(it.curr == last){
            pop_back();
        }
        else{
            it.curr->prev->next = it.curr->next;
            it.curr->next->prev = it.curr->prev;
            delete it.curr;
            --size_;
        }
    }
    
    std::size_t LinkedList::size(){
        return size_;
    }
    
    void LinkedList::sort(){
        for(iterator it = end(); it != begin(); --it){
            iterator left = begin();
            iterator right = begin();
            ++right;
            while(right != it){
                if(*left > *right){
                    std::swap(*left, *right);
                }
                ++left;
                ++right;
            }
        }
    }
    
    std::ostream& operator<<(std::ostream& out, const LinkedList& list){
        for (int i : list){
            out << i << ' ';
        }
        out << '\n';
        return out;
    }
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    node::node(int i):val(i), prev(nullptr), next(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    iterator::iterator(node* n, const LinkedList* ll): curr(n), container(ll) {}

    iterator& iterator::operator++(){
        if(curr == nullptr){
            throw std::logic_error("Invalid address");
        }
        else{
            curr = curr->next;
        }
        return *this;
    }

    iterator iterator::operator++(int){
        iterator temp(*this);
        ++(*this);
        return temp;
    }

    iterator& iterator::operator--(){
        if(curr == container->first){
            throw std::logic_error("Invalid address");
        }
        else if(curr == nullptr){
            curr = container->last;
        }
        else{
            curr = curr->prev;
        }
        return *this;
    }

    iterator iterator::operator--(int){
        iterator temp(*this);
        --(*this);
        return temp;
    }

    int& iterator::operator*() const{
        return curr->val;
    }
    
    bool operator==(const iterator& lhs, const iterator& rhs){
        return ((lhs.curr == rhs.curr) && (lhs.container == rhs.container));
    }

    bool operator!=(const iterator& lhs, const iterator& rhs){
        return !(lhs == rhs);
    }
    
    iterator::operator const_iterator() const{ //iterator to const_iterator
        return const_iterator(curr, container);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const_iterator::const_iterator(node* n, const LinkedList* ll): curr(n), container(ll) {}
    
    const_iterator& const_iterator::operator++(){
        if(curr == nullptr){
            throw std::logic_error("Invalid address");
        }
        else{
            curr = curr->next;
        }
        return *this;
    }
    
    const_iterator const_iterator::operator++(int){
        const_iterator temp(*this);
        ++(*this);
        return temp;
    }
    
    const_iterator& const_iterator::operator--(){
        if(curr == container->first){
            throw std::logic_error("Invalid address");
        }
        else if(curr == nullptr){
            curr = container->last;
        }
        else{
            curr = curr->prev;
        }
        return *this;
    }
    
    const_iterator const_iterator::operator--(int){
        const_iterator temp(*this);
        --(*this);
        return temp;
    }
    
    int const_iterator::operator*() const{
        return curr->val;
    }

    bool operator==(const const_iterator& lhs, const const_iterator& rhs){
        return((lhs.curr == rhs.curr) && (lhs.container == rhs.container));
    }

    bool operator!=(const const_iterator& lhs, const const_iterator& rhs){
        return !(lhs == rhs);
    }
    
    bool seqSearch(const const_iterator& it1, const const_iterator& it2, int value){
        for(const_iterator i = it1; i != it2; ++i){
            if(*i == value){
                return true;
            }
        }
        return false;
    }
}
