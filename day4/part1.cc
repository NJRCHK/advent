#include <iostream>
#include <fstream>
#include <tuple>

inline std::tuple<int, int, int, int> parse_line(const std::string &line) {
    int num1, num2, num3, num4;
    for (int i = 0; i < line.length(); i++){
        
    }
    return std::tuple<int, int, int, int>{1, 2, 3, 4};
}

inline bool does_contain(const std::tuple<int, int, int, int> &value) {

    
    
    return true; 
}


int main() {
    std::fstream file("input.txt");
    std::string line;
    

    auto count = 0;
    while(getline(file, line)){
        count += does_contain(parse_line(line));
    }
    std::cout << "test" << std::endl;

}