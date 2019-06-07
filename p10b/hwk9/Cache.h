//
//  Cache.h
//  assignment9

#ifndef Cache_h
#define Cache_h
#include<iostream>
#include<deque>
#include<exception>

namespace pic10b{
    template<typename T, size_t N, typename ord = std::less<T>>
    class cache{
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T&;
        using iterator = typename std::deque<value_type>::iterator;
        using const_iterator = typename std::deque<value_type>::const_iterator;
        
        /**
        cache default constructor, that accepts a value of type ord and sets the member comparison
         @param comp type ord that is default std::less<T>
         */
        constexpr cache(const ord& comp = ord()): data_(0), comparison_(comp), capacity_(N), low_(), high_() {}
        
        /**
         insert member function, overloaded on lvalue input, adds item to deque possibly at cost of removing the oldest stored object
         @param value lvalue input of type lvalue referece to const T
         */
        void insert(const T& value){
            insert(std::move(value));                                  //calls insert overloaded on rvalue input
        }
        
        /**
         insert member function, overloaded on rvalue input, adds item to deque possibly at cost of removing the oldest stored object
         @param value rvalue input of type T
         */
        void insert(T&& value){
            if(data_.size() == capacity_){                             //if size == capacity
                pop();                                                 //call pop member function
            }
            if(data_.empty()){                                         //if deque is empty, set both low_ and high_ to value
                low_ = value;
                high_ = value;
            }
            else{                                                     //else compare value with low_ and high_ and set them appropriately
                low_ = comparison_(low_, value) ? low_ : value;
                high_ = comparison_(high_, value) ? value : high_;
            }
            data_.push_front(value);                                  //insert value (in the front of deque)
        }
        
        /**
         emplace templated member function, accepts an arbitrary number of arguments of arbitrary type to construct an object and add it
         @tparam Types the arbitrary type of arguments
         @param args the arbitray number of arguments
         */
        template<typename ...Types>
        void emplace(Types&& ...args){
            insert(T(std::forward<Types>(args)...));                  //pass all the parameters to make T
        }
        
        /**
         pop member function, removes the oldest element
         */
        void pop(){
            if(data_.empty()){                                        //if empty, throw exception
                throw std::logic_error("pop nothing");
            }
            data_.pop_back();                                         //else remove the oldest element (from the back of deque)
        }
        
        /**
         begin member function, returning an const_iterator to the first element
         @return const_iterator to the first element
         */
        const_iterator begin(){
            return data_.begin();
        }
        
        /**
         end member function, returning an iterator to past-the-end (one past the final element)
         @return const_iterator to past-the-end
         */
        const_iterator end(){
            return data_.end();
        }
        
        /**
         size() member function, counts the number of elements
         @return size_t number of elements in the cache class
         */
        constexpr size_t size() const { return data_.size(); }
        
        /**
         get_low member function, to retrieve the lowest value
         @Tparam T the type of the arguments
         @return a reference to const T to the lowest value in the cache class
         */
        const T& get_low() const { return low_; }
        
        /**
         get_high member function, to retrieve the highest value
         @Tparam T the type of the argument
         @return a reference to const T to the highest value in the cache class
         */
        const T& get_high() const { return high_; }
        
        /**
         print non-member function, prints all the elements of a cache object of any type
         @param C a cache object
         */
        friend void print(cache C){
            for(const_iterator it = C.begin(), itend = C.end(); it != itend; ++it){     //iterate from first to last element and print the value of each
                std::cout << *it << ' ';
            }
        }
        
    private:
        std::deque<T> data_;    //using std::deque from standard library as the data structure for class cache
        ord comparison_;
        size_t capacity_;
        T low_, high_;
    };
}
#endif /* Cache_h */
