#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <set>
#include <utility>

bool coords_arent_edges(int x, int y, int width, int height){
    if(y == 0 || y == height - 1){
        return false;
    }
    else if (x == 0 || x == width - 1){
        return false;
    }
    return true;
}

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

std::set<std::pair<int,int>> calculate_visible_trees_north(const std::vector<std::vector<int>> &grid) {
    std::set<std::pair<int, int>> visible = {};
    for(int i = 0; i < grid.size(); i++){
        int max_tree = -1;
        for(int j = 0; j < grid[i].size(); j++){
            if(max_tree < grid[j][i]){
                visible.insert({j, i});
            }
            max_tree = max_tree > grid[j][i] ? max_tree : grid[j][i];
        }
    }
    return visible;
}

std::set<std::pair<int, int>> calculate_visible_trees_south(const std::vector<std::vector<int>> &grid){
    std::set<std::pair<int, int>> visible = {};
    for(int i = 0; i < grid.size(); i++){
        int max_tree = -1;
        for(int j = grid[i].size() - 1; j >= 0; j--){
            if(max_tree < grid[j][i]){
                visible.insert({j, i});
            }
            max_tree = max_tree > grid[j][i] ? max_tree : grid[j][i];
        }
    }
    return visible;
}

std::set<std::pair<int, int>> calculate_visible_trees_east(const std::vector<std::vector<int>> &grid) 
{
    std::set<std::pair<int, int>> visible = {};
    for(int i = 0; i < grid.size(); i++){
        int max_tree = -1;
        for(int j = grid[i].size() - 1; j >= 0; j--){
            if(max_tree < grid[i][j]){
                visible.insert({i, j}); 
            }
            max_tree = max_tree > grid[i][j] ? max_tree : grid[i][j];
        }
    }
    return visible; 
}

std::set<std::pair<int, int>> calculate_visible_trees_west(const std::vector<std::vector<int>> &grid)
{
    std::set<std::pair<int, int>> visible = {};
    for(int i = 0; i < grid.size(); i++){
        int max_tree = -1;
        for(int j = 0; j < grid[i].size(); j++){
            if(max_tree < grid[i][j]){
                visible.insert({i, j}); 
            }
            max_tree = max_tree > grid[i][j] ? max_tree : grid[i][j];
        }
    }
    return visible; 
}

void print_set(const std::set<std::pair<int, int>> set) {
    for(auto i :set )
    {
        std::cout << "{" << i.first << ", " << i.second << "}\n";
    }
    std::cout << std::endl;
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
    auto visible = calculate_visible_trees_east(grid);
    const auto south = calculate_visible_trees_south(grid);
    const auto north = calculate_visible_trees_north(grid);
    print_set(north);
    const auto west = calculate_visible_trees_west(grid);
    visible.insert(south.begin(), south.end());
    visible.insert(north.begin(), north.end());
    visible.insert(west.begin(), west.end());
    print_set(visible);
    std::cout << visible.size() << std::endl;
}