#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <set>
#include <array>

constexpr int num_rope_segments = 10;

std::pair<char, int> parse_line(const std::string &line){
    return {line[0], stoi(line.substr(2))};
}

void update_pos(char direction, std::pair<int ,int> &location) 
{
    if(direction == 'L'){
            location = {location.first - 1, location.second};
    }
    else if (direction == 'R'){
        location = {location.first + 1, location.second};
    } 
    else if (direction == 'D'){
        location = {location.first, location.second - 1};
        }
    else if (direction == 'U'){
        location = {location.first, location.second + 1};
    }
}

void fix_pos(std::pair<int, int> &tail, const std::pair<int, int> &head) {
    int xdif = head.first - tail.first;
    int ydif = head.second - tail.second;
    auto xsign = xdif == 0 ? 0 : xdif/abs(xdif);
    auto ysign = ydif == 0 ? 0 : ydif/abs(ydif);
    if(abs(xdif) > 1 || abs(ydif) > 1){
        tail.first += xsign;
        tail.second += ysign;
    }
}


std::array<std::pair<int, int>, num_rope_segments> initialize_rope() {
    std::array<std::pair<int, int>, num_rope_segments> arr;
    arr.fill({0, 0});
    return arr;
}


bool tail_close(const std::pair<int, int> &tail, const std::pair<int, int> &head)
{
    if(abs(tail.second - head.second) > 1){
        return false;
    }
    else if(abs(tail.first - head.first) > 1){
        return false;
    }
    return true;
}

int main() {
    std::fstream file("input.txt");
    std::set<std::pair<int, int>> past_tail_locations = {};
    std::array<std::pair<int, int>, num_rope_segments> rope = initialize_rope();
    past_tail_locations.insert(rope[num_rope_segments - 1]);
    std::string line;
    while(getline(file,line)){
        const auto [direction, spaces] = parse_line(line);
        for(int i = 0; i < spaces; i++){
            update_pos(direction, rope[0]);
            for(int j = 1; j < rope.size(); j++){
                fix_pos(rope[j], rope[j-1]);
            }
            past_tail_locations.insert(rope[num_rope_segments-1]);
        }
    }

    // print_past_locations(past_tail_locations);
    std::cout << "Visited: " << past_tail_locations.size() << std::endl;
} 