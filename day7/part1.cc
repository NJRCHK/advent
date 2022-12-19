#include <iostream>
#include <fstream>
#include <ctype.h>
#include <map>
#include <vector>

class Directory {


    std::string directory_name;
    Directory* parent;
    std::vector<Directory> children;
    std::map<std::string, int> files;
    int size;
    bool ls_called;

    public:
        Directory(std::string directory_name, Directory* parent) {
            this->directory_name = directory_name;
            this->parent = parent;
            this->children = {};
            this->files = {};
            this->ls_called = false;
        }

        int calculate_size(){

            int child_size = 0;
            for(int i = 0; i < this->children.size(); i++){
                child_size += this->children[i].calculate_size();
            }

            return child_size + this->size;
        }

        void set_ls_called() {
            this->ls_called = true;
        }

        Directory* add_child(std::string name) {
            Directory new_child = Directory(name, this);
            this->children.push_back(new_child);
            return &(this->children.back());
        }

        void recursive_print(int level = 0){
            this->print_tabs(level);
            std::cout << "Directory: " << this->directory_name << " size: " << this->calculate_size() <<  std::endl;
            for(int i = 0; i < this->children.size(); i++){
                this->children[i].recursive_print(level + 1);
            }
        }

        std::vector<std::pair<std::string, int>> get_directories() {
            std::vector<std::pair<std::string, int>> out = {};
            out.push_back({this->directory_name, this->calculate_size()}); 
            if(this->children.size() == 0){
                return out;
            }
            for(int i = 0; i < this->children.size(); i++){
                const auto val = this->children[i].get_directories();
                out.insert(out.end(), val.begin(), val.end());
            }

            return out;
        }

        std::vector<Directory>* get_children() {
            return &(this->children);
        }

        void add_file(std::string file_name, int size) {
            if(this->files.count(file_name)){
                return;
            }
            this->size += size;
            this->files.insert({file_name, size});
        }

        Directory* get_child(std::string name) {
            for(int i = 0; i < this->children.size(); i++){
                if(this->children[i].get_name() == name){
                    return &(this->children[i]);
                }
            }
            throw std::invalid_argument("Child not found1");
        }

        bool has_child(std::string name) {
            for(int i = 0; i < this->children.size(); i++){
                if(this->children[i].get_name() == name){
                    return true;
                }
            } 
            return false;
        }
        
        Directory* get_parent() {
            return this->parent;
        }

        std::string get_name() {
            return this->directory_name;
        }

    private:
        void print_tabs(int tabs) {
            for(int i = 0; i < tabs; i++){
                std::cout << '\t';
            }
        }
};

int read_file_size_line(std::string &line) {
    std::string buf = "";
    int count = 0;
    while(isdigit(line[count])){
        buf += line[count];
        count++;
    }
    return std::stoi(buf);
}

bool is_cd_command(const std::string &command) {
    return command.substr(0, 4) == "$ cd";
}

std::string get_dir_name_from_command(const std::string &command) {
    return command.substr(5, std::string::npos); 
}

void handle_cd_command(const std::string &command,  Directory* &current_directory) {
    const std::string dir_name = get_dir_name_from_command(command);
    if(current_directory->has_child(dir_name)){
        std::cout << dir_name << std::endl;
        current_directory = current_directory->get_child(dir_name);
        return; 
    }
    else if (dir_name == ".."){
        current_directory = current_directory->get_parent();
        return;
    }
    current_directory->add_child(dir_name); 
    current_directory = current_directory->get_child(dir_name);
}

bool is_ls_command(const std::string &command){
    return command.substr(0, 4) == "$ ls";
}

bool is_ls_output(const std::string &command) {
    return command[0] != '$';
}

bool is_dir_line(const std::string &command){
    return command.substr(0, 3) == "dir";
}

std::string get_file_name_from_ls_output(const std::string &output) {
    bool flag = false;
    for (int i = 0; i < output.size(); i++){
        if(flag){
            return output.substr(i, std::string::npos);
        }        
        if(output[i] == ' '){
            flag = true;
        }
    }
    throw std::invalid_argument("File name not found");
}

int get_file_size_from_ls_output(const std::string &output) {
    std::string size;

    for(int i = 0; i < output.size(); i++){
        if(output[i] == ' '){
            return stoi(size);
        }
        size.push_back(output[i]);
    }
    throw std::invalid_argument("File name not found");
}

void handle_ls_output(Directory* &current_directory, const std::string &command) {
    if(is_dir_line(command)){
        return;
    }

    const std::string file_name = get_file_name_from_ls_output(command);
    const int file_size = get_file_size_from_ls_output(command);

    current_directory->add_file(file_name, file_size);
}

int main () {
    std::fstream file("input.txt");
    std::string line;
    getline(file, line); 
    Directory root_dir = Directory(get_dir_name_from_command(line), nullptr);
    Directory* current_directory = &root_dir;
    
    while(getline(file, line)){
        if(is_cd_command(line)){
            handle_cd_command(line, current_directory);
        }
        else if (is_ls_output(line)){
            handle_ls_output(current_directory, line);
        }
    }
    
    const auto nodes = root_dir.get_directories();
    int sum = 0;
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i].second <= 100000){
            sum += nodes[i].second;
        }
    }
    std::cout << sum << std::endl;
}