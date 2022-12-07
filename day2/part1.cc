#include <iostream>
#include <fstream>

int calculate_round_score(char my_move, char opponent_move) {
    auto their_move = opponent_move + 23;
    auto score = my_move - 87;
    auto their_losing_move = my_move - 1 < 88 ? my_move + 2 : my_move - 1;
    if (their_move == my_move){
        score += 3;
    }
    else if (their_move == their_losing_move){
        score += 6; 
    }
    return score;
}

int main() {
    std::fstream myFile("input.txt");
    std::string line;
    auto score = 0;
    while (getline(myFile, line)){
        score += calculate_round_score(line[2], line[0]);
    }
    std::cout << score << std::endl;
}
