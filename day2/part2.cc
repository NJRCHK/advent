#include <iostream>
#include <fstream>

int calculate_round_score(char outcome, char opponent_move) {
    outcome -= 'Y'; //want outcome to equal -1 for loss, 0 for draw, and 1 for win
    auto my_move = opponent_move + outcome;
    my_move = my_move > 'C' ? my_move - 3 : my_move;
    my_move = my_move < 'A' ? my_move + 3 : my_move;
    return (my_move - 64) + (outcome+1)*3;
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
