//
//  MagicSquare.cpp
//  assignment6

#include "MagicSquare.h"

MagicSquare::MagicSquare(const std::vector<std::vector<int>>& vec): data_(vec){}

bool MagicSquare::empty(size_t row, size_t col) const{
    return data_[row][col] == 0 ? true : false;
}

bool MagicSquare::taken(int i) const{
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
        if(sum_row != target || sum_col != target){
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
    if(checkRow()){
        for(size_t i = 0; i < n; ++i){
            sum_diag1 += data_[i][i];
            sum_diag2 += data_[i][n - 1 - i];
        }
    }
    if(sum_diag1 != target || sum_diag2 != target){
        return false;
    }
    return true;
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

//void MagicSquare::solveSquare(int index){
//    size_t n = data_.size();
//    std::vector<size_t> unused;
//    if(index == n * n){
//        std::cout << data_ << '\n';
//    }
//    for(size_t idx = 0; idx < n * n; ++idx){
//        if(getnum(idx) == 0){
//            unused.push_back(idx);
//        }
//    }
//    for(size_t j = 0; j < unused.size(); ++j){
//        setnum(
//
//    }
//}
