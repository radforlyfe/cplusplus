//
//  Print_Tree.h
//  p10b_assignment8

#ifndef __PRINT_TREE__
#define __PRINT_TREE__
/*
 Written by : Bumsu Kim (TA, P10)
 Date       : May 22, 2019
 
 ****   NOTE   ****
 First declare a free function
 std::ostream& operator<<(std::ostream& out, const Tree& T)
 and a member function
 std::ostream& Tree::iterator::output_it(std::ostream& out) const
 in the header "BinarySearchTree.h".
 
 Also include this (#include "Print_Tree.h") in the source, "BinarySearchTree.cpp".
 
 Then you have your operator<< overloaded on Tree, and may use it in the source file (BinarySearchTree.cpp), or in the main routine (HW8_Source.cpp).
 
 ****   Sample Usage   ****
 (ex) std::cout << myTree;        // in the main routine with a Tree object myTree
 (ex) std::cout << (*this);       // in a Tree's member function
 (ex) std::cout << (*container);  // in an iterator's member function
 */

#include <iomanip>            // std::setprecision, std::setw, std::fixed
#include <iostream>
#include <string>
#include "BinarySearchTree.h"

namespace pic10b {
    // Tree output format parameters
    constexpr size_t outputdigits = 6; // number of digits to print, for node values
    
    constexpr size_t stemsz = 6;       // size of each stem (must be the same)
    /* FORMAT
     123456        123456
     /--           /--
     |          --/     (One child on the left)
     (TWO children)     --<
     |          --\
     \--           \--  (One child on the right)
     */
    const std::string stem_v       = "   |  ";   // stem vertical
    const std::string stem_h_out_b = "--<   ";   // horizontal, out from the node, both
    const std::string stem_h_out_u = "--/   ";   // horizontal, out from the node, upward (left)
    const std::string stem_h_out_d = "--\\   ";  // horizontal, out from the node, downward (right)
    const std::string stem_h_in_u  = "   /--";   // horizontal, in to the node, upward (left)
    const std::string stem_h_in_d  = "   \\--";  // horizontal, in to the node, downward (right)
    
    /**
     operator<< prints a tree in the specified format above.
     usage:
     (ex) std::cout << myTree;        // in the main routine with a Tree object myTree
     (ex) std::cout << (*this);       // in a Tree's member function
     (ex) std::cout << (*container);  // in an iterator's member function
     etc.
     
     sample output:
     Data input (in this order): 0.454939 0.638752 0.672109 0.221564 0.913114 0.453078 0.586779 0.63329 0.525407 0.130406
     
     /--0.1304
     /--0.2216--<
     |           \--0.4531
     0.4549--<
     |                       /--0.5254
     |           /--0.5868--<
     |           |           \--0.6333
     \--0.6388--<
     \--0.6721--\
     \--0.9131
     */
    std::ostream& operator<<(std::ostream& out, const Tree& T) {
        out << std::setprecision(outputdigits - 2) << std::fixed;
        for (auto it = T.begin(); it != T.end(); ++it) {
            it.output_it(out) << '\n';
        }
        out << "\n\n";
        return out;
    }
    
    /**
     (Member of Tree::iterator) (Accessor) (Helper function for operator<< for Tree)
     Prints the current node, curr in the specified format
     @param  out ostream object
     @return the same ostream object after outputting
     
     usage: (ex) iter->output_it(out) << '\n';
     */
    std::ostream& Tree::iterator::output_it(std::ostream& out) const {
                                  // compute distance to the root
        size_t lev = 0;           // level (how far it is from the root)
        node* temp = curr_;        // temporary node
        while (temp->parent_) {    // while it has a parent (i.e. while it is not a root)
            temp = temp->parent_;  // go up
            lev++;                // increment level
        }
                                  // temp = root now
        
        // now temp will track curr's pedigree ( ancestor --> child )
        // when direction ( parent->child;  left or right ) changes, print stem_v
        char dir = 0; // L : left, R : right
        bool dir_change_flag = false; // if direction is changed from the previous step
        for (size_t i = 0; i < lev; ++i) { // for each level (from the root to the target node)
            
            // Find the direction and track
            if (curr_->value_ < temp->value_) {  // to the left
                if (dir == 'R') { // direction is changed from R to L
                    dir_change_flag = true;
                }
                else { // direction didn't change (or it's the first step)
                    dir_change_flag = false;
                }
                dir = 'L'; // set direction = true;
                temp = temp->left_; // track pedigree
            }
            else if (curr_->value_ > temp->value_) { // to the right
                if (dir == 'L') { // direction is changed from L to R
                    dir_change_flag = true;
                }
                else {
                    dir_change_flag = false;
                }
                dir = 'R';
                temp = temp->right_;
            }// Now we determined which child to follow from level i, and found the direction, and we also know if the direction has changed or not
            // Print stem, if any. Otherwise print white space
            if (dir_change_flag) { // direction changed --> add vertical stem
                out << stem_v;
            }
            else if (i > 0) { // otherwise add the same sized white space except the first level (the root has no input stem)
                out << std::string(stemsz, ' ');
            }
            // Now print the white space of size = (parent node's output size)
            out << std::string(outputdigits, ' ');
        }
        // Now print the node with the stem
        if (dir == 'L') { // upward
            out << stem_h_in_u;
        }
        else if (dir == 'R') { // downward
            out << stem_h_in_d;
        }
        out << std::setw(outputdigits) << curr_->value_; // node value
        if (curr_->left_) { // has a left child
            if ((curr_->right_)) { // has both
                out << stem_h_out_b;
            }
            else { // left only
                out << stem_h_out_u;
            }
        }
        else if (curr_->right_) { // right only
            out << stem_h_out_d;
        }
        return out;
    } // end function output_it
    
} // end namespace pic10b

#endif // !__PRINT_TREE__
