//File: myapriori.cpp
//Author: P.J. Leyden
//Date: Sept. 26th, 2019

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>

using std::deque; using std::vector; using std::string;

deque<vector<int>> read_file(char*);
void print_item_set(const deque<vector<int>>&);

int main(int argc, char** argv){

	if(argc < 3){
		std::cerr << "Error: Not enough arguments.\n";
		std::cerr << "Usage: myapriori [path_to_file] [frequency]";
		exit(1);
	}

	deque<vector<int>> item_sets = read_file(argv[1]);

	print_item_set(item_sets);

	return 0;
}



deque<vector<int>> read_file(char* file_name){
	std::ifstream in_file(file_name);

	deque<vector<int>> item_sets;
	item_sets.push_back(vector<int>());

	string line;
	int indx = 0;
	while(!in_file.eof()){
		std::getline(in_file, line);
		for(int i = 0; line[i] != '\0'; ++i){
			if (line[i] != ' '){
				(item_sets.end() - 1)->push_back(line[i] - '0'); 
			}	
		}
		item_sets.push_back(vector<int>());
	}

	for(deque<vector<int>>::iterator itr = item_sets.begin(); itr != item_sets.end(); ++itr){
		if(itr->empty()){
			itr = item_sets.erase(itr);
			--itr;
		}
	}

	return item_sets;
}

void print_item_set(const deque<vector<int>>& item_sets){
	for(const vector<int>& v : item_sets){
		for(int item : v){
			std::cout << item << " ";
		}
		std::cout << '\n';
	}
}