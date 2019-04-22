//
//  ScoreList.hpp
//  cs32_Assignment1
//
//  Created by Radhika Nayar on 4/14/19.
//  Copyright © 2019 Radhika Nayar. All rights reserved.
//

#ifndef ScoreList_H
#define ScoreList_H

#include "Sequence.h"
#include <limits>

const unsigned long NO_SCORE = std::numeric_limits<unsigned long>::max();

class ScoreList
{
public:
    // Create an empty score list.
    ScoreList();
    
    // If the score is valid (a value from 0 to 100) and the score list
    // has room for it, add it to the score list and return true.
    // Otherwise, leave the score list unchanged and return false.
    bool add(unsigned long score);
    
    // Remove one instance of the specified score from the score list.
    // Return true if a score was removed; otherwise false.
    bool remove(unsigned long score);
    
    // Return the number of scores in the list.
    int size() const;
    
    // Return the lowest score in the score list.  If the list is
    // empty, return NO_SCORE.
    unsigned long minimum() const;
    
    // Return the highest score in the score list.  If the list is
    // empty, return NO_SCORE.
    unsigned long maximum() const;
    
private:
    Sequence s1;
};


#endif // ScoreList_H
