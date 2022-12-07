#include <iostream>
#include <fstream>
#include <map>

inline int calculate_priority(char c)
{
    if (c < 'a'){
        return c - 38;
    }
    return c - 96;
}

inline char calculate_badge(const std::string &s1, const std::string &s2, const std::string &s3)
{
    std::map<char, int> seen;

    for(int i = 0; i < s1.size(); i++){
        seen.insert(std::pair<char, int>(s1[i], 1));
    }    

    for(int i = 0; i < s2.size(); i++){
        if(seen.count(s2[i])){
            seen.erase(s2[i]);
            seen.insert(std::pair<char, int>(s2[i], 2));
        }
    }

    for(int i = 0; i < s3.size(); i++){
        if(seen.count(s3[i]) && seen.at(s3[i])== 2){
            return s3[i];
        }
    }

    return -1;
}

int main() {
    std::fstream file("input.txt");
    std::string line1;
    std::string line2;
    std::string line3;

    auto sum = 0;
    while (getline(file, line1) && getline(file, line2) && getline(file, line3)){
        sum += calculate_priority(calculate_badge(line1, line2, line3));
    }
    std::cout << sum << std::endl;
}