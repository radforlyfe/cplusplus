//
//  vector (without reserve) -- all in one file

#include<iostream>
#include <memory>
#include<string>

namespace pic10b{
    
class VectorString{
public:
    VectorString();
    VectorString(size_t count);
    VectorString(size_t count, const std::string& value);
    VectorString(const VectorString& other);
    VectorString(VectorString&& other);
    VectorString& operator=(const VectorString& other);
    VectorString& operator=(VectorString&& other);
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void push_back(const std::string& value);
    void pop_back();
    void deleteAt (size_t pos);
    void insertAt (size_t pos, std::string value);
    std::string& at(size_t pos);
    const std::string& at(size_t pos) const;
        
private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<std::string[]> data_; // pointer to dynamic array of string vector, defaulted to nullptr
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VectorString::VectorString(): size_(0), capacity_(1){
    data_ = std::make_unique<std::string[]>(capacity_);
}

VectorString::VectorString(size_t count): size_(count), capacity_(count*2){
    data_ = std::make_unique<std::string[]>(capacity_);
}

VectorString::VectorString(size_t count, const std::string& value): size_(count), capacity_(count*2){
    data_ = std::make_unique<std::string[]>(capacity_);
    for(size_t index = 0; index < count; ++index){ // initializes all string variables to value
        data_[index] = value;
    }
}

// Copy constructor:
VectorString::VectorString(const VectorString& other): size_(other.size_), capacity_(other.capacity_){
    data_ = std::make_unique<std::string[]>(capacity_);
    for(size_t index = 0; index < other.size(); ++index){ // copies each element of data_ equal to the elements of other.data_
        data_[index] = other.data_[index];
    }
}

// Move constructor:
VectorString::VectorString( VectorString&& other): VectorString(){ // invoke the default constructor
    std::swap(data_, other.data_); // then swap their pointers
    std::swap(size_, other.size_); // then swap their sizes
    std::swap(capacity_, other.capacity_); // then swap their capacities
}

// Copy assignment:
VectorString& VectorString::operator=(const VectorString& rhs){
    if(this == &rhs){ // self-assign
        return *this;
    }
    auto new_data_ = std::make_unique<std::string[]>(rhs.capacity_);
    for(size_t i = 0; i < rhs.size_; ++i){
        new_data_[i] = rhs.data_[i];
    }
    data_.reset(new_data_.release());
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    return *this;
}
    
// Move assignment:
VectorString& VectorString::operator=(VectorString&& other){
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    return *this;
}

bool VectorString::empty() const { return size()==0; }

size_t VectorString::size() const { return size_; }

size_t VectorString::capacity() const { return capacity_; }

// Push-back
void VectorString::push_back(const std::string& value){
    if(size_ == capacity_){
        auto new_data_ = std::make_unique<std::string[]>(2*capacity_);
        for(size_t i = 0; i < size_; ++i){  // copy each element from data_ into new_data_
            new_data_[i] = data_[i];
        }
        data_.reset(new_data_.release());   //data_ now points to the new array with double capacity
        capacity_ = 2*capacity_;
    }
    data_[size_] = value;                   // sets last element plus one to value
    size_++;
}

// Pop-back
void VectorString::pop_back(){
    if(size()!=0){
        size_--; // deletes one element as long as size is not zero
    }
}

// DeleteAt
void VectorString::deleteAt(size_t pos){
    if(pos >= 0 && pos < size()){
        for(size_t index = pos; index < size()-1; ++index){ // copies one element ahead to element behind
            data_[index] = data_[index+1];
        }
        size_--;
    }
}

// InsertAt
void VectorString::insertAt(size_t pos, std::string value){
    if(pos < 0 && pos > size()){
        return;
    }
    if(size_ == capacity_){
        auto new_data_ = std::make_unique<std::string[]>(2*capacity_);
        for(size_t i = 0; i < size_; ++i){  // copy each element from data_ into new_data_
            new_data_[i] = data_[i];
        }
        data_.reset(new_data_.release());   //data_ now points to the new array with double capacity
        capacity_ = 2*capacity_;
    }
    for(size_t index = size(); index > pos; --index){ // moves all element one ahead
        data_[index] = data_[index-1];
    }
    data_[pos] = value; // sets value to pos index
    size_++;
}

// At
std::string& VectorString::at( size_t pos ) { return data_[pos]; }

// At overloaded on const
const std::string& VectorString::at( size_t pos ) const { return data_[pos]; }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pic10b::VectorString foo() {
    return pic10b::VectorString(2);
}

int main() {
    pic10b::VectorString vs;
    std::cout << "vs stats: " << vs.size() << " " << vs.capacity() << '\n';
    vs.push_back("hello");
    std::cout << "vs stores: " << vs.at(0) << '\n';
    
    auto foo_out = foo();
    
    pic10b::VectorString vs2(std::move(foo_out));
    std::cout << "vs2 stats: " << vs2.size() << " " << vs2.capacity() << '\n';
    
    std::cout << "vs2 stores: ";
    for (std::size_t i = 0, total_size = vs2.size(); i < total_size; ++i) {
        std::cout << vs2.at(i) << ",";
    }
    std::cout << '\n';
    
    pic10b::VectorString vs3(4, "beta");
    vs3.pop_back();
    vs3.push_back("delta");
    vs3.push_back("epsilon");
    vs3.at(1) = "gamma";
    vs3.insertAt(0, "alpha");
    vs3.push_back("zeta");
    vs3.push_back("theta");
    vs3.insertAt(vs3.size() - 1, "eta");
    vs3.deleteAt(3);
    
    std::cout << "vs3 stats: " << vs3.size() << " " << vs3.capacity() << '\n';
    std::cout << "vs3 stores: ";
    for (std::size_t i = 0, total_size = vs3.size(); i < total_size; ++i) {
        std::cout << vs3.at(i) << ",";
    }
    std::cout << '\n';
    
    vs2 = vs3;
    
    std::cout << "vs2 stats: " << vs2.size() << " " << vs2.capacity() << '\n';
    std::cout << "vs2 stores: ";
    for (std::size_t i = 0, total_size = vs2.size(); i < total_size; ++i) {
        std::cout << vs2.at(i) << ",";
    }
    std::cout << '\n';
    
    const auto vs4 = std::move(vs);
    
    std::cout << "vs4 stats: " << vs4.size() << " " << vs4.capacity() << '\n';
    std::cout << "vs4 stores: ";
    for (std::size_t i = 0, total_size = vs4.size(); i < total_size; ++i) {
        std::cout << vs4.at(i) << ",";
    }
    std::cout << '\n';
    
    std::cin.get();
    return 0;
}

