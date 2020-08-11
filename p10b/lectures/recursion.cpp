// main.cpp
// recursion

#include <iostream>
#include <vector>

//Sum consecutive integers in a range from a to b inclusive:
constexpr int sum_a_to_b(int a, int b){
    int sum = 0;
    for(int i = a; i <= b; ++i){
        sum += i;
    }
    return sum;
}

//Recursive Sum consecutive integers in a range from a to b inclusive:
constexpr int rsum_a_to_b(int a, int b){
    if(a<b){                              //if more to sum, pull out a single number and recurse
        return a + sum_a_to_b(a+1, b);
    }
    else if(a == b){                      //if lower and upper bounds are equal
        return a;
    }
    else{                                 //there is nothing to sum over
        return 0;
    }
}

//Recursive factorial function:
constexpr int factorial (int n){
    return (n > 0)? n * factorial(n-1) : 1;
}

//Palindrome function:
bool isPalindrome(const std::string& s){
    if(s.size() <= 1){                    //empty string or string with only a single char is palindrome
        return true;
    }
    for(size_t start = 0, end = s.size()-1; start <= end; ++start, --end){
        if(s[start] != s[end]){           //if mismatch, not palindrome
            return false;
        }
    }
    return true;
}

//Recursive Palindrome function:
bool risPalindrome(const std::string& s){
    if(s.size() <= 1){                              //base case
        return true;
    }
    else{                                           //do recursion
        if(s[0] != s[s.size()-1]){                  //match first and last element
            return false;
        }
    }
    return risPalindrome(s.substr(1, s.size()-2));  //nips off the ends
}

//Recursive to reverse a string in place:
void ReverseStrRec(std::string& toReverse, size_t start, size_t end){
    if(start >= end){                                //Base case: string of size 1 or less - do nothing
        return;
    }
    else{
        std::swap(toReverse[start], toReverse[end]); //otherwise swap first and last character
    }
    ReverseStrRec(toReverse, start+1, end-1);        //continue with substring
}


//std::string_view can be used with constexpr!
std::string message("hello");
std::string_view first(message.c_str()); //acts like message but is not a copy of it
constexpr std::string_view second(" world");
std::cout << first << second; //prints "hello world"

//Tower of Hanoi
using PEG = std::vector<int>;
void TowerofHanoi(size_t n, PEG& source, PEG& dest, PEG& idle){
    if(n == 1){                                      //Base case: moving one block
        dest.push_back(source.back());               //Copy top(last) block to dest
        source.pop_back();                           //Delete top(last) block at source
        return;
    }
    else{
        TowerofHanoi(n-1, source, idle, dest);       //move n-1 blocks from source to idle
        TowerofHanoi(1, source, dest, idle);         //move nth block from source to dest
        TowerofHanoi(n-1, idle, dest, source);       //move n-1 blocks from idle to dest
    }
}

//Generating All Permutations:
void permute(std::vector<int>& v, size_t place = 0){
    size_t sz = v.size();
    if(place == sz - 1){              //index at the last element of vector
        for(auto i : v){              //print each element of the vector
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
    else{                                                  //recursion: still more place to go
        for(size_t other = place; other < sz; ++other){    //give all unplaced elements a chance to be at position
            std::swap(v[place], v[other]);                 //place unplaced
            permute(v, place+1);                           //have placed one more
            std::swap(v[place], v[other]);                 //undo for next unplaced ?
        }
    }
}
// calling this function:
std::vector<int> v {1,2,3,4,5};
permute(v); //will print all 5! = 120 permutations

//Selection sort: Repeatedly find the minimum of the unsorted entries and
//swap the minimum with the first of the unsorted entries. (need a loop since compares through all elements!)
/**
 This will sort a vector via selection sort
 @param v the vector to sort
 @param beg the lowest index position to include in the sort
 @param end the largest index position to include in the sort
 */
void r_selSort(std::vector<int>& v, size_t beg, size_t end){
    size_t n = v.size();
    if( (end > n-1) || (beg > end) || (beg > n-1) || (beg < 0) ){   //check if indices are valid for the sort
        throw std::logic_error("invalid input range");              //throw exception if not
    }
    if(beg == end){                                                 //Base case: nothing to sort
        return;
    }
    else{
        size_t minpos = beg;                                        //index of smallest value
        for(size_t i = beg+1; i <= end; ++i){                       //loop to compare values with each element
            if(v[i] < v[minpos]){                                   //update index to smallest value if new smallest
                minpos = i;
            }
        }
        std::swap(v[beg], v[minpos]);                               //place smallest element of unsorted range in its place
        r_selSort(v, beg+1, end);                                   //with beg in place, sort smaller part of vector (beg+1)
    }
}

//Bubble sort: Move forward through list swapping adjacent entries if they are not in sorted order.
//cycling back over the unsorted parts until all the items have been sorted.
/**
 This will sort a vector via bubble sort
 @param v the vector to sort
 @param beg the lowest index position to include in the sort
 @param end the largest index position to include in the sort
 */
void r_bubSort(std::vector<int>& v, size_t beg, size_t end){
    size_t n = v.size();
    if( (end > n-1) || (beg > end) || (beg > n-1) || (beg < 0) ){   //check if indices/range is valid for the sort
        throw std::logic_error("invalid input range");              //throw exception if not
    }
    if(beg == end){                                                 //Base case: no range to swap
        return;
    }
    else{
        for(size_t i = beg; i < end; ++i){               //loop to compare adjacent elements; swap so lower is left of upper
            if(v[i] < v[i+1]){                           //swap if left bigger than right
                std::swap(v[i], v[i+1]);
            }
        }
        r_bubSort(v, beg, end-1);                        //with end in place, sort over smaller range (end-1)
    }
}

//SelSort iteratively
void selSort(std::vector<int>& v, size_t beg, size_t end){
    size_t n = v.size();
    if( (end > n-1) || (beg > end) || (beg > n-1) || (beg < 0) ){   //check if indices are valid for the sort
        throw std::logic_error("invalid input range");              //throw exception if not
    }
    for(size_t i = beg; i < end; ++i){                              //first loop - loop over unsorted range
        size_t minpos = i;                                          //index of smallest value (assume leftmost (beg))
        for(size_t j = i+1; j < end; ++j){                          //second loop - to compare each remaining element
            if(v[j] < v[minpos]){                                   //update minpos if new min found
                minpos = j;
            }
        }
        std::swap(v[i], v[minpos]);                                 //place new min in lowest available position
    }
}

/**
 This function merges two consecutive ranges of a vector that are already sorted, and overwrites
 the vector elements so that all the elements in the overall range are in order.
 @param v the vector that is being sorted on a range
 @param beg the lowest index range to be included in the first list
 @param mid the highest index range to be included in the first list
 with mid+1 being the lowest index range to be included in the second list
 @param end the highest index range to be included in the second list
 */
void mergeSorted(std::vector<int>& v, size_t beg, size_t mid, size_t end){
    size_t first = beg, second = mid+1, resIndex = 0;     //initialize first index, second index, temp vector index
    std::vector<int>res(end-beg+1);                       //temp vector with size including range of values
    while( (first <= mid) && (second <= end) ){           //while both first and second lists are not exhausted
        if(v[first] < v[second]){                         //check if first value is less than second value
            res[resIndex++] = v[first++];                 //store first value in temp and increment first and temp indices
        }
        else{                                             //store second value in temp and increment second and temp indices
            res[resIndex++] = v[second++];
        }
    }                                                     //one of the list is exhausted- only one of two while loops below will run
    while(first <= mid){                                  //if first list is not exhausted
        res[resIndex++] = v[first++];
    }
    while(second <= end){                                 //if second list is not exhausted
        res[resIndex++] = v[second++];
    }
    size_t resSize = res.size();
    for(resIndex = 0; resIndex < resSize; ++resIndex){    //overwrite all values from temp into v
        v[beg + resIndex] = res[resIndex];
    }
}

//Merge sort: repeatedly split the list into smaller lists and those smaller lists into smaller lists.
//then merge the small lists into larger sorted lists, and merge those into even larger sorted lists.
/**
 This will sort a vector via merge sort
 @param v the vector of ints to sort
 @param beg the lowest index position to include in the sort
 @param end the largest index position to include in the sort
 */
void mergeSort(std::vector<int>& v, size_t beg, size_t end){
    if(beg == end){                          //Base case: nothing to merge or sort
        return;
    }
    size_t mid = (beg + end) / 2;            //find middle position with integer division
    mergeSort(v, beg, mid);                  //sort first half
    mergeSort(v, mid+1, end);                //sort second half
    mergeSorted(v, beg, mid, end);           //with first and second halves sorted, the two lists can be merged
}

//local static variable to track how many times a function is called
/**
 This function increments a count when told to and returns its count value
 @param increase whether or not to increment the counter
 @return the count value
 */
int count(bool increase){
    static int counter = 0;                  //initialized to 0 only once!
    if(increase){                            //if should increase(bool), increase
        ++counter;
    }
    return counter;
}

//Usage: counting how many times mergeSort function gets called
void _mergeSort(std::vector<int>& v, size_t beg, size_t end){
    count(true);                             //count each time this function is entered
    // rest of mergeSort code...
    std::cout << count(false);               //to check count simply print count without incrementing it
}

//Binary Search: already sorted vector, employ "divide and conquer" approach to find targest - start in the middle.
/**
 Searching if a value is found over a range of iterators
 @param beg the first iterator
 @param past_end the iterator just past the search range
 @param val value to search for (target)
 @return whether the value is found within the range
 */
bool binSearch(const std::vector<int>::const_iterator beg, const std::vector<int>::const_iterator past_end, int val){
    if(beg == past_end){                     //no range to search over
        return false;
    }
    if(beg == past_end - 1){                 //only one item in range - check whether element is val
        return *beg == val;
    }
    auto len = past_end - beg;               //total number of elements
    auto mid = beg + len/2;                  //move iterator from beg to mid
    if(*mid == val){                         //check midpoint
        return true;
    }
    else if(val > *mid){                     //check right half
        binSearch(mid+1, past_end, val);
    }
    else{                                    //check left half
        binSearch(beg, mid, val);
    }
}

 
