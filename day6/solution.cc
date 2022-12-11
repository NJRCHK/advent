#include <iostream>
#include <fstream>


bool contains_duplicate(const char arr[], size_t size) {
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(arr[i] == arr[j]){
                return true;
            }
        }
    }
    return false;
}

void setup_arr(char arr[], size_t size, std::fstream &file) {
    for(int i = 0; i < size; i++){
        file >> std::noskipws >> arr[i]; 
    }
}

int main() {
    std::fstream file("input.txt");
    size_t size = 14;
    char arr[size];
    int count = size;
    setup_arr(arr, size, file);
    while(contains_duplicate(arr, size)){
        for(int i = 0; i < size-1; i++){
            arr[i] = arr[i + 1];
        }
        file >> std::noskipws >> arr[size-1];
        count++;
    }
    
    std::cout << count << std::endl;
}
