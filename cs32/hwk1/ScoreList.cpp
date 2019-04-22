//
//  ScoreList.cpp
//  cs32_Assignment1
//
//  Created by Radhika Nayar on 4/14/19.
//  Copyright © 2019 Radhika Nayar. All rights reserved.
//

#include "ScoreList.h"

// Create an empty score list.
ScoreList::ScoreList(){}
    // putting after : instead after {}


// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
bool ScoreList::add(unsigned long score){
    if(s1.size()!= DEFAULT_MAX_ITEMS && (score>=0 && score<=100)){
        s1.insert(score); // to access member functions of another class need to declare object of another class in header and then that object has access to its own class member functions!
        return true;}
    return false;
}


// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
bool ScoreList::remove(unsigned long score){
    int p = s1.find(score);
    return s1.erase(p); //need return statement for non-void function!!
}


// Return the number of scores in the list.
int ScoreList::size() const{
    return s1.size(); //need return statement for non-void function!!
}

//insert() function adds all values in ascending order!!


// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::minimum() const{
    if(s1.empty()){
        return NO_SCORE;}
    
    ItemType value;
    // Another way to write code:
    //    s1.get(0, value);
    //    return value;
    
    unsigned long min = 101;
    
    for(int i=0; i<size(); i++){
        s1.get(i, value);
        if(value<min){
            min = value;
        }
    }
    return min;
}


// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::maximum() const{
    if(s1.empty()){
        return NO_SCORE;}
    ItemType value;
    // Another way to write code:
    //    s1.get(size()-1, value); //size function is also present in score list so no need to do s1.size() -1 but that works as well
    //    return value;
    unsigned long max = 0;
    
    for(int i=0; i<size(); i++){
        s1.get(i, value);
        if(value>max){
            max=value;}
    }
    return max;
}
