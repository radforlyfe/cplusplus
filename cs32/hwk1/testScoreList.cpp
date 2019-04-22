//
//  testScoreList.cpp
//  cs32_Assignment1
//
//  Created by Radhika Nayar on 4/14/19.
//  Copyright © 2019 Radhika Nayar. All rights reserved.
//

#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{

    ScoreList sl1;
    assert(sl1.add(100));
    assert(sl1.add(2));
    assert(sl1.add(3));
    assert(sl1.add(4));
    assert(sl1.add(5));
    assert(sl1.add(30));
    assert(sl1.add(30));
    assert(!sl1.add(-1));
    assert(!sl1.add(101));
    assert(sl1.size()==7);
    
   //  assert(s1.get(0,x) && x==2);
        //Is there a way to access the elements of ScoreList sl1 through get function?
    
    assert(sl1.remove(30) ==1);
    
    cerr << sl1.maximum() <<endl;
    cerr<< sl1.minimum()<<endl;
    
    
    cout << "Passed all tests" << endl;
}
