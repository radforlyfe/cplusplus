//
//  List.cpp
//  assignment7

#include "List.h"

namespace pic10b{
    
    LinkedList::LinkedList() noexcept: first(nullptr), last(nullptr) {} //empty list with null first and last
    
    LinkedList::LinkedList(const std::initializer_list<int>& list): first(nullptr), last(nullptr){
        for(auto i : list){       //range based for loop to push the data(value) into empty LinkedList
            push_back(i);
        }
    }
    
    LinkedList::~LinkedList(){
        node *n = first;          //start at the first node
        while(n != nullptr){      //while not past-the-end
            node *temp = n->next; //temporarily store the next position
            delete n;             //delete the node on heap
            n = temp;             //move node n right
        }
    }
    
    void swap(LinkedList& one, LinkedList& another){ //directly swaps the pointers (first and last) and the sizes
        std::swap(one.first, another.first);
        std::swap(one.last, another.last);
        std::swap(one.size_, another.size_);
    }
    
    LinkedList::LinkedList(const LinkedList& other): first(nullptr), last(nullptr){ //copy elements over one by one
        for(int i : other){    //take each value from other, and push into LinkedList
            push_back(i);
        }
    }

    LinkedList::LinkedList(LinkedList&& other) noexcept: LinkedList(){
        swap(*this, other);    //take pointers to first/last and then set other's pointers to null - so its in a valid destructible state
    }
    
    LinkedList& LinkedList::operator=(const LinkedList& other) &{
        if(this != &other){                //no self-assignment
            LinkedList temp(other);        //copy construct temp with other
            swap(*this, temp);             //swap this with temp
        }
        return *this;
    }
            
    LinkedList& LinkedList::operator=(LinkedList&& other) & noexcept{
        swap(*this, other);
        return *this;
    }
    
    void LinkedList::push_back(int value){
        node *n = new node(value);         //create a new node
        if(!last){                         //if last node is null - LinkedList is empty
            first = last = n;              //both first and last point to newly added node n
        }
        else{                              //if last node is not null - LinkedList is not empty
            last->next = n;                //make last point to n
            n->prev = last;                //make n have last as previous
            last = n;                      //update last
        }
        ++size_;                           //increment size
    }
    
    void LinkedList::push_front(int value){
        node *n = new node(value);         //create a new node
        if(!first){                        //if first node is null - LinkedList is empty
            first = last = n;              //both first and last point to newly added node n
        }
        else{                              //if first node is not null - LinkedList is not empty
            first->prev = n;               //make first have n as previous
            n->next = first;               //make n point to first
            first = n;                     //update first
        }
        ++size_;                           //increment size
    }
    
    void LinkedList::pop_back(){
        if(!last){                         //if last is null - LinkedList is empty
            throw std::logic_error("pop back on an empty list");
        }
        else if(first == last){            //if just one element
            delete first;                  //free heap memory
            first = last = nullptr;        //LinkedList is empty now - first/last are null
            --size_;                       //decrement size
        }
        else{                              //if many elements
            node * newlast = last->prev;   //store the new last node
            newlast->next = nullptr;       //set new last node next pointer to null
            delete last;                   //free heap memory
            last = newlast;                //update last
            --size_;                       //decrement size
        }
    }
    
    void LinkedList::pop_front(){
        if(!first){                        //if first is null - LinkedList is empty
            throw std::logic_error("pop back on an empty list");
        }
        else if(first == last){            //if just one element
            delete first;                  //free heap memory
            first = last = nullptr;        //LinkedList is empty now- first/last are null
            --size_;                       //decrement size
        }
        else{                              //if many elements
            node * newfirst = first->next; //store the new first node
            newfirst->prev = nullptr;      //set new first node prev pointer to null
            delete first;                  //free heap memory
            first = newfirst;              //update first
            --size_;                       //decrement size
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
        if(it.curr == nullptr){                       //inserting before past-the-end
            push_back(value);
        }
        else if(it.curr == first){                    //inserting at the beginning
            push_front(value);
        }
        else{                                         //inserting in the middle
            node *n = new node(value);                //create new node
            n->next = it.curr;                        //set n's next
            n->prev = it.curr->prev;                  //set n's prev
            it.curr->prev->next = n;                  //make current prev next node into n
            it.curr->prev = n;                        //make current prev node into n
            ++size_;                                  //increment size
        }
    }
    
    void LinkedList::erase(iterator it){
        if(it.curr == first){                         //removing first
            pop_front();
        }
        else if(it.curr == last){                     //removing last
            pop_back();
        }
        else{                                         //removing in the middle
            it.curr->prev->next = it.curr->next;      //reroute next of previous
            it.curr->next->prev = it.curr->prev;      //reroute previous of next
            delete it.curr;                           //free heap memory of items being removed
            --size_;                                  //decrement size
        }
    }
    
    std::size_t LinkedList::size() const{
        return size_;
    }
    
    void LinkedList::sort(){
        for(iterator it = end(); it != begin(); --it){  //iterate from past-the-end to the second element
            iterator left = begin();  //left iterator at first element
            iterator right = begin();
            ++right;                  //right iterator at second element
            while(right != it){                         //as long as right iterator is not same as it
                if(*left > *right){                     //compare values of adjacent iterators
                    std::swap(*left, *right);           //swap the values of nodes if unsorted
                }
                ++left;               //move left iterator forward
                ++right;              //move right iterator forward
            }
        }
    }
    
    std::ostream& operator<<(std::ostream& out, const LinkedList& list){
        for (int i : list){           //for data in list
            out << i << ' ';          //print out data
        }
        out << '\n';
        return out;
    }
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    node::node(int i):val(i), prev(nullptr), next(nullptr) {} //node stores value but points to null on either side

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    iterator::iterator(node* n, const LinkedList* ll): curr(n), container(ll) {} //

    iterator& iterator::operator++(){                    //prefix ++ unary operator
        if(curr == nullptr){                             //cannot go past-the-end
            throw std::logic_error("Invalid address");
        }
        else{                                            //anywhere else, reference next node
            curr = curr->next;
        }
        return *this;
    }

    iterator iterator::operator++(int unused){           //postfix ++ binary operator
        iterator temp(*this);
        ++(*this);
        return temp;
    }

    iterator& iterator::operator--(){                    //prefix -- unary operator
        if(curr == container->first){                    //cannot go before first
            throw std::logic_error("Invalid address");
        }
        else if(curr == nullptr){                        //if past-the-end, go to last
            curr = container->last;
        }
        else{                                            //if somewhere in the middle, reference previous node
            curr = curr->prev;
        }
        return *this;
    }

    iterator iterator::operator--(int unused){           //postfix -- binary operator
        iterator temp(*this);
        --(*this);
        return temp;
    }

    int& iterator::operator*() const{                    //dereference operator: return reference to the int stored
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
    
    const_iterator& const_iterator::operator++(){           //prefix ++ unary operator
        if(curr == nullptr){                                //cannot go past the end
            throw std::logic_error("Invalid address");
        }
        else{                                               //anywhere else, reference next node
            curr = curr->next;
        }
        return *this;
    }
    
    const_iterator const_iterator::operator++(int unused){  //postfix ++ binary operator
        const_iterator temp(*this);                         //copy cuurent const_iterator
        ++(*this);                                          //call the other ++
        return temp;                                        //return copy
    }
    
    const_iterator& const_iterator::operator--(){           //prefix -- unary operator
        if(curr == container->first){                       //cannot go before first
            throw std::logic_error("Invalid address");
        }
        else if(curr == nullptr){                           //if past-the-end, go to last
            curr = container->last;
        }
        else{                                               //if somewhere in the middle, reference previous node
            curr = curr->prev;
        }
        return *this;
    }
    
    const_iterator const_iterator::operator--(int unused){  //postfix -- binary operator
        const_iterator temp(*this);
        --(*this);
        return temp;
    }
    
    int const_iterator::operator*() const{                  //dereference operator: return copy of the int stored
        return curr->val;
    }

    bool operator==(const const_iterator& lhs, const const_iterator& rhs){
        return((lhs.curr == rhs.curr) && (lhs.container == rhs.container));
    }

    bool operator!=(const const_iterator& lhs, const const_iterator& rhs){
        return !(lhs == rhs);
    }
    
    bool seqSearch(const const_iterator& it1, const const_iterator& it2, int value){
        for(const_iterator i = it1; i != it2; ++i){ //range from first iterator upto but not including the second iterator
            if(*i == value){                        //check if the value is present in the LinkedList
                return true;
            }
        }
        return false;
    }
}
