#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <tuple>
#include <array>

std::array<char, 220> screen = {'.'};

bool is_noop(const std::string &str)
{
    return str.substr(0, 4) == "noop";
}

int parse_addx_line(const std::string &str)
{
    return std::stoi(str.substr(5, std::string::npos));
}

void draw_pixel(int r1, int cycle)
{
    std::cout << cycle << std::endl;
    if(r1 <= (cycle % 40) && (cycle % 40) <= r1 + 2){
        screen[cycle] = '#';
    } else {
        screen[cycle] = '.';
    }
}
void initialize_screen()
{
    for(int i = 0; i < 240; i++){
        screen[i] = '.';
    }
}


std::tuple<int, int> increment_cycle(int cycle, int r1, int sum)
{
    cycle++;
    draw_pixel(r1, cycle);
    if((cycle - 20) % 40 == 0){
        sum += cycle * r1;
    }
    return {cycle, sum};
}

void print_screen() {
    for(int i = 0; i < 240; i++){
        std::cout << screen[i];
        if((i + 1) % 40 == 0){
            std::cout << std::endl;
        }
    }
}

int main() 
{
    std::fstream file("input.txt");
    std::string line;
    initialize_screen();
    int cycle = 0;
    int r1 = 1;
    int sum = 0;
    while(getline(file, line)) {
        if(is_noop(line)){
            std::tie(cycle, sum) = increment_cycle(cycle, r1, sum);
            continue;
        }
        std::tie(cycle, sum) = increment_cycle(cycle, r1, sum);
        std::tie(cycle, sum) = increment_cycle(cycle, r1, sum);
        r1 += parse_addx_line(line);
    }
    std::cout << sum << std::endl;
    print_screen();
}
