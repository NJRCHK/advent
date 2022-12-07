#include <iostream>
#include <fstream>
#include <map>

int main() {
    std::ifstream myFile("input.txt");
    std::string line;
    auto max_calories = 0;
    auto sum = 0;
    while (getline(myFile, line)){
        if (line != ""){
            sum += std::stoi(line, NULL, 10);
            continue;
        }
        max_calories = max_calories < sum ? sum : max_calories;
        sum = 0;
    }
    std::cout << max_calories << "\n";
}
