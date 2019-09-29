//File: myapriori.cpp
//Author: P.J. Leyden
//Date: Sept. 26th, 2019
//Due: Oct. 2nd, 2019 

/*
Notes:
	
	Will probably want to represent the sets as vector<bool> easier for sorting and counting.

	think to self how would I generate all itemsets. What method would I use to write them out. 


*/

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <list>
#include <algorithm>

using std::deque; using std::vector; using std::string;

//Function Prototypes
//========================================================================
void read_file(char*, deque<vector<bool>>&, deque<vector<int>>&);
void print_int_set(const deque<vector<int>>&);
void print_bool_set(const deque<vector<bool>>&);
//========================================================================


//main function
//========================================================================
int main(int argc, char** argv){

	if(argc < 3){
		std::cerr << "Error: Not enough arguments.\n";
		std::cerr << "Usage: myapriori [path_to_file] [frequency]";
		exit(1);
	}

	deque<vector<bool>> bool_item_sets;
	deque<vector<int>> int_item_sets;
	read_file(argv[1], bool_item_sets, int_item_sets);

	print_int_set(int_item_sets);

	std::cout << '\n';

	print_bool_set(bool_item_sets);







	return 0;
}
//========================================================================


//Function Implementations
//========================================================================
void read_file(char* file_name, deque<vector<bool>>& bool_item_sets, deque<vector<int>>& int_item_sets){
	std::ifstream in_file(file_name);

	//Category 1 
	std::vector<int> c1;
	
	//init int item sets
	int_item_sets.push_back(vector<int>());

	//read file
	string line;
	while(!in_file.eof()){
		std::getline(in_file, line);
		for(int i = 0; line[i] != '\0'; ++i){
			if(line[i] != ' '){
				int current_num = line[i] - '0';
				(int_item_sets.end() - 1)->push_back(current_num);
				std::vector<int>::iterator itr = std::find(c1.begin(), c1.end(), current_num);
				if(itr == c1.end()){
					c1.push_back(current_num);
				}
			}
		}
		int_item_sets.push_back(vector<int>());
	}

	//sort c1
	std::sort(c1.begin(), c1.end());

	//get rid of empty sets
	for(deque<vector<int>>::iterator itr = int_item_sets.begin(); itr != int_item_sets.end(); ++itr){
		if(itr->empty()){
			itr = int_item_sets.erase(itr);
			--itr;
		}
	}

	//
	bool_item_sets.push_back(vector<bool>(c1.size(), false));
	for(const std::vector<int> v : int_item_sets){
		for(int item : v){
			(*(bool_item_sets.end() - 1))[item - 1] = true;
		}
		bool_item_sets.push_back(vector<bool>(c1.size(), false));
	}


	

	in_file.close();
}

void print_int_set(const deque<vector<int>>& item_sets){
	for(const vector<int>& v : item_sets){
		for(int item : v){
			std::cout << item << " ";
		}
		std::cout << '\n';
	}
}

void print_bool_set(const deque<vector<bool>>& item_sets){
	for(const vector<bool> v : item_sets){
		for(int i = 0; i < v.size(); ++i){
			std::cout << "=";
		}

		std::cout << '\n';

		for(int i = 0; i < v.size(); ++i){
			if(v[i]){
				std::cout << 1 << " ";
			}else{
				std::cout << 0 << " ";
			}
		}

		std::cout << '\n';

		for(int i = 0 ; i < v.size(); ++i){
			std::cout << i << " ";
		}

		std::cout << '\n';

		for(int i = 0; i < v.size(); ++i){
			std::cout << "=";
		}

		std::cout << '\n';
	}
}

//========================================================================