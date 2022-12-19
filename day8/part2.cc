#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <set>
#include <utility>


int get_grid_width(std::fstream &file) 
{
    std::string line;
    getline(file, line);
    file.clear();
    file.seekg(0, std::ios::beg);
    return line.size();
}

int get_grid_height(int width, int file_size)
{
    return (file_size / width) - 1;
}

void print_grid(const std::vector<std::vector<int>> &grid)
{
    for(auto row: grid){
        for(auto element : row){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int calculate_scenic_score(const std::pair<int, int> &coord, const std::vector<std::vector<int>> &grid)
{
    int scenic = 0;
    const auto x = coord.first;
    const auto y = coord.second;
    const int my_tree = grid[y][x];
    int scenic_left = 0;
    for(int i = x -1 ; i >= 0; i--){
        scenic_left++;
        if(grid[y][i] >= my_tree){
            break;
        }
    }

    int scenic_right = 0;
    for(int i = x + 1; i < grid[y].size(); i++){
        scenic_right++;
        if(grid[y][i] >= my_tree){
            break;
        }
    }
    int scenic_down = 0;
    for(int i = y + 1; i < grid.size(); i++){
        scenic_down++;
        if(grid[i][x] >= my_tree){
            break;
        }
    }

    int scenic_up = 0;
    for(int i = y - 1; i >= 0; i--){
        scenic_up++;
        if(grid[i][x] >= my_tree){
            break;
        }
    }
    std::cout << "Checking Pair: " << coord.first << ", " << coord.second << std::endl;
    std::cout << "Value: " << grid[coord.second][coord.first] << std::endl;
    std::cout << "Up Scenic Score: " << scenic_up << std::endl;
    std::cout << "Down Scenic Score: " << scenic_down << std::endl;
    std::cout << "Left Scenic Score: " << scenic_left << std::endl;
    std::cout << "Right Scenic Score: " << scenic_right << std::endl;
    std::cout << "Scenic Score: " << scenic_down * scenic_left * scenic_right * scenic_up << std::endl;
    std::cout << std::endl;
    return scenic_up * scenic_down * scenic_left * scenic_right;
}

int main() 
{
    const std::string file_to_read = "input.txt";

    std::fstream file(file_to_read);
    const auto size = std::filesystem::file_size(file_to_read);
    const int width = get_grid_width(file);
    const int height = get_grid_height(width, size);
    std::vector<std::vector<int>> grid; 
    grid.reserve(height);
    std::string line;
    int count = 0;
    while(getline(file, line)){
        std::vector<int> row; 
        row.reserve(width);
        for(int i = 0; i < line.size(); i++){
            row.push_back(line[i] - '0');
        }
        grid.push_back(row);
    }

    int max = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int temp = calculate_scenic_score({i, j}, grid);
            if(temp > max){
                max = temp;
            }
        }
    }
    std::cout << max << std::endl;
}