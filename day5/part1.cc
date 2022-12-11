#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <regex>

int calculate_num_cranes(const std::string &line) {
    return (line.size() + 1) / 4;
}

std::vector<std::stack<char>> setup(std::fstream &file) {
    std::vector<std::stack<char>> vector;
    std::string line;
    getline(file, line);
    int num_cranes = calculate_num_cranes(line);
    file.seekg(0);
    std::string buffer = "";
    while (getline(file, line)){
        if(line[1] == '1'){
            break;
        }
        for(auto i = 0; i < line.size(); i++){
            if((i + 3) % 4 == 0){
                buffer += line[i];
            }
        }
    }

    for(int i = 0; i < num_cranes; i++){
        vector.push_back({});
    }
    for(int i = buffer.size() - 1; i >= 0; i--){
        if(buffer[i] == ' '){
            continue;
        }
        int temp = i % num_cranes;
        vector[temp].push(buffer[i]);
    }
    file.seekg(0);
    return vector;
}

std::tuple<int, int, int> parse_nums_from_line(const std::string &line) {
    int nums[] = {0, 0, 0};
    std::smatch results;
    std::regex_match(line, results, std::regex("^move (\\d*) from (\\d*) to (\\d*)"));
    int count = -1;
    for(auto result : results){
        if(count == -1){
            count = 0;
            continue;            
        }
        nums[count++] = std::stoi(result);
    }
    return {nums[0], nums[1], nums[2]};
}

void print_stacks_tops(const std::vector<std::stack<char>> &vector) {
    for(int i = 0; i < vector.size(); i++){
        std::cout << vector[i].top();
    }
    std::cout << "\n";
}
void move (int source, int destination, std::vector<std::stack<char>> &vector) {
    vector[destination].push(vector[source].top());
    vector[source].pop();
}


int main() {
    std::fstream file("input.txt");
    std::vector<std::stack<char>> config = setup(file);
    std::string line;
    while(getline(file, line)){
        if(line[0] != 'm'){
            continue;
        }
        std::tuple<int, int, int> nums = parse_nums_from_line(line);
        for(int i = 0; i < std::get<0>(nums); i++){
            move(std::get<1>(nums)-1 , std::get<2>(nums)-1, config);
        }
    }
    print_stacks_tops(config);
}
