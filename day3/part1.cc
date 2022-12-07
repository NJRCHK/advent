#include <iostream>
#include <fstream>
#include <map>

inline int calculate_priority(char c){
    if(c < 'a'){
        return c - 38;
    }
    return c - 96;
}

inline char calculate_duplicate(const std::string &s) {
    std::map<char, bool> seen;

    for(int i = 0; i < s.size(); i++){
        if (i < s.size() / 2){
            seen.insert(std::pair<char, bool>(s[i], true));
            continue;
        } 
        if(seen.count(s[i])){
            return s[i];
        }
    }
    std::cout << "BAD" << std::endl;
    return -1;
}

int main() {
    std::fstream myFile("input.txt");
    std::string line;
    auto sum = 0;
    while (getline(myFile, line)){
        sum += calculate_priority(calculate_duplicate(line));
    }
    std::cout << sum << std::endl;
}
