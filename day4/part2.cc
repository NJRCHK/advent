#include <iostream>
#include <fstream>
#include <tuple>
#include <regex>

inline std::tuple<int, int, int, int> parse_line(const std::string &line) {
    int nums[] = {0, 0, 0, 0};
    std::smatch results;
    std::regex_match(line, results, std::regex("^(\\d*)-(\\d*),(\\d*)-(\\d*)"));
    int count = -1;
    for(auto result : results){
        if(count == -1){
            count = 0;
            continue;            
        }
        nums[count++] = std::stoi(result);
    }
    return {nums[0], nums[1], nums[2], nums[3]};
}

inline bool does_contain(const std::tuple<int, int, int, int> &value) {
    int elf1low = std::get<0>(value);
    int elf1high = std::get<1>(value);
    int elf2low = std::get<2>(value);
    int elf2high = std::get<3>(value);
    if (elf1low >= elf2low && elf1low <= elf2high){
        return true;
    }
    else if (elf1high >= elf2low && elf1high <= elf2high ){
        return true;
    }
    else if (elf2low >= elf1low && elf2low <= elf1high){
        return true;
    }
    else if (elf2high >= elf1low && elf2high <= elf1high){
        return true;
    }
    return false;
}


int main() {
    std::fstream file("input.txt");
    std::string line;

    int count = 0;
    while(getline(file, line)){
        count += does_contain(parse_line(line));
    }
    std::cout << count << std::endl;
}
