//  MagicSquare.cpp - NO PERMUTATIONS
//  assignment6

#include "MagicSquare.h"

MagicSquare::MagicSquare(const std::vector<std::vector<int>>& vec): data_(vec){
    size_t n = data_.size();
    for(size_t index = 0; index < n*n; ++index){
        if(getnum(index) != 0){
            taken_.insert(getnum(index));
        }
        else{
            unused_indices.push_back(index);
        }
    }
}

bool MagicSquare::empty(size_t row, size_t col) const{
    return data_[row][col] == 0;
}

bool MagicSquare::taken(int i){
    return taken_.find(i) != taken_.end();
}

bool MagicSquare::checkRow() const{
    size_t n = data_.size();
    size_t target = n * ((n * n) + 1)/2;
    for(size_t i = 0; i < n; ++i){
        int sum_row = 0;
        int sum_col = 0;
        for(size_t j = 0; j < n; ++j){
            sum_row += data_[i][j];
            sum_col += data_[j][i];
        }
        if(sum_row != target || sum_col > target){
            return false;
        }
    }
    return true;
}

bool MagicSquare::checkValid() const{
    size_t n = data_.size();
    size_t target = n * (n * n + 1)/2;
    int sum_diag1 = 0;
    int sum_diag2 = 0;
    if(!checkRow()){
        return false;
    }
    for(size_t i = 0; i < n; ++i){
        sum_diag1 += data_[i][i];
        sum_diag2 += data_[i][n - 1 - i];
    }
    if(sum_diag1 != target || sum_diag2 != target){
        return false;
    }
    return true;
}

int& MagicSquare::getnum(size_t index){
    size_t i = index / data_.size();
    size_t j = index % data_.size();
    return data_[i][j];
}

int MagicSquare::getnum(size_t index) const{
    size_t i = index / data_.size();
    size_t j = index % data_.size();
    return data_[i][j];
}

void MagicSquare::setnum(size_t index, int value){
    size_t i = index / data_.size();
    size_t j = index % data_.size();
    data_[i][j] = value;
}

int MagicSquare::getcount() const{
    return count_solutions;
}

void MagicSquare::solveSquare(size_t index){
    size_t n = data_.size();
    size_t row = index / data_.size();
    size_t col = index % data_.size();
    if(col == 0 && row != 0){                                  //checks if each row is valid
        checkRow();
    }
    if(index == n * n){                                        //base case of recursion step
        if(checkValid()){                                      // checks if whole square is valid
            ++count_solutions;
            std::cout << data_ << '\n';
        }
    }
    else{                                                      //if index not at last position
        if(empty(row, col)){                                   // if value at index is 0
            for(int value = 1; value <= n * n; ++value){
                if(!taken(value)){                             // ensure value not in taken
                    data_[row][col] = value;
                    taken_.insert(value);
                    solveSquare(index+1);
                    data_[row][col] = 0;
                    taken_.erase(value);
                }
            }
        }
        else{                                                  // if value at index is not 0
            solveSquare(index+1);
        }
    }
}
