//
//  main.cpp
//  SpellCheck

#include<iostream>
#include<string>
#include<fstream>
#include<unordered_set>
//key: mark functions as const which do not change the class private member variables
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SpellCheck{
public:
    SpellCheck(): dictionary_(0) {}
    void read_dictionary(const std::string& dictionary = "dictionary.txt"); //modifies the private member dictionary_
    bool is_valid(const std::string& word) const;
    void process_file(const std::string& filename = "example.txt") const;
private:
    std::unordered_set<std::string> dictionary_;                            //to store the dictionary words
};

bool is_white_space(const char& character);
bool final_punctuation(const std::string& word);
void depunctuate(std::string& input);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool is_white_space(const char& character){
    if(character == ' ' || character == '\t' || character == '\n'){
        return true;
    }
    return false;
}
bool final_punctuation(const std::string& word){
    if(word.back() == '.' || word.back() == ',' || word.back() == '!' ||\
        word.back() == '?'|| word.back() == ';' || word.back() == ':'){
        return true;
    }
    return false;
}
void depunctuate(std::string& input){
    if(final_punctuation(input)){
        input.pop_back();                                               //or input.substr(0, input.size()-1)
    }
    if(input != "I" && input.front() >= 'A' && input.front() <= 'Z'){
        input.front() += ('a' - 'A');
    }
}
void SpellCheck::read_dictionary(const std::string& dictionary){
    std::fstream fin(dictionary);                                    //or fin.open(filename)
    if(fin.fail()){                                                  //or fin.is_open(){} or if(!fin)
        std::cout << "failed to open";
    }
    while(!fin.eof()){                                               //while(fin >> line) { dictionary_.insert(line) }
        std::string line;
        fin >> line;                                                 //cannot use getline! (getline reads ' ', '\t')
        dictionary_.insert(line);
    }
    fin.close();
}
bool SpellCheck::is_valid(const std::string& word) const{
    if(word == "i"){
        return false;
    }
    auto ptr = dictionary_.find(word);                     //returns an iterator
    if(ptr != dictionary_.end()){                          //if no such iterator, return past-the-end (.end()) iterator
        return true;
    }
    return false;
}
void SpellCheck::process_file(const std::string& filename) const{
    std::ifstream fin(filename);                                     //or fin.open(filename)
    if(fin.fail()){
        std::cout << "failed to open.";
    }
    std::string temp_console = "";                           //empty string representing console display at the end
    while(!fin.eof()){
        while(is_white_space(fin.peek())){                   //check for all whitespaces
            temp_console += fin.get();
        }
        std::string word;
        fin >> word;                                         //cannot use getline!
        std::string word_copy = word;
        depunctuate(word_copy);
        if(is_valid(word_copy)){
            temp_console += word;
        }
        else{
            temp_console += '*';
            if(final_punctuation(word)){
                word.insert(word.end() - 1, '*');            //add * before punctuation
                temp_console += word;
            }
            else{
                temp_console += (word + '*');                //if no punctuation, add * after word
            }
        }
    }
    fin.close();
    std::cout << temp_console << '\n';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    SpellCheck s;
    const std::string dictionary = "dictionary.txt";
    
    s.read_dictionary(dictionary);
    std::cout << "Enter file to spell check: ";
    std::string fileName;
    getline(std::cin,fileName);
    s.process_file(fileName);
    return 0;
}
