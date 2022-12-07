#include <iostream>
#include <fstream>
#include <algorithm>

int main() {
    std::ifstream myFile("input.txt");
    std::string line;
    int max_calories[3] = {0, 0, 0};
    auto sum = 0;
    while (getline(myFile, line)){
        if (line != ""){
            sum += std::stoi(line, NULL, 10);
            continue;            
        }
        if (max_calories[0] < sum){
            max_calories[0] = sum;
            std::sort(std::begin(max_calories), std::end(max_calories));
        }
        sum = 0;
    }
    std::cout << max_calories[0] + max_calories[1] + max_calories[2] << "\n";
}
