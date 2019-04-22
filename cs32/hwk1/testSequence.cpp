//
//  testSequence.cpp
//  cs32_Assignment1
//
//  Created by Radhika Nayar on 4/14/19.
//  Copyright © 2019 Radhika Nayar. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
    assert(s.insert(40) == 0);
    assert(s.size() == 2  &&  s.find(42) == 1);
    assert(s.insert(2, 20) == 2);
    assert(s.insert(0, 10) == 0);
    assert(s.size() == 4  &&  s.find(42) == 2);
    assert(s.insert(4, 100) == 4);
    assert(s.insert(5, 42) == 5);
    ItemType x;
    assert(s.get(4, x) && x==100);
    assert(s.set(1, 1000) ==1);
    assert(s.get(1,x) && x==1000);
    assert(s.remove(42) ==2);
    assert(s.remove(200) ==0);
    assert(s.size()==4);
    assert(s.insert(10, 42) == -1);
    assert(s.insert(4, 1) == 4);
    assert(s.erase(3) == 1);
    assert(s.find(1)==3);
    Sequence s1;
    s1.insert(0, 1);
    s1.insert(1,2);
    s1.insert(3);
    s1.insert(4);
    s1.insert(5);
    assert(s1.get(0,x)&& x==1);
    assert(s1.get(1,x) && x==2);
    assert(s1.get(2,x) && x==3);
    assert(s1.get(3,x) && x==4);
    assert(s1.get(4,x) && x==5);
    assert(s1.size()==5);
    Sequence s2;
    s2.insert(0, 6);
    s2.insert(1,7);
    assert(s2.get(0,x)&& x==6);
    assert(s2.get(1,x) && x==7);
    assert(s2.size()==2);
    s1.swap(s2);
    assert(s1.size()==2 && s2.size()==5);
    assert(s1.get(0,x) && x==6);
    assert(s1.get(1,x) && x==7);
    assert(s1.get(2,x) == 0);
    assert(s2.get(0,x) && x==1);
    assert(s2.get(1,x) && x==2);
    assert(s2.get(2,x) && x==3);
    assert(s2.get(3,x) && x==4);
    assert(s2.get(4,x) && x==5);
    assert(s2.get(5,x) ==0);
    
    cout << "Passed all tests" << endl;

}
