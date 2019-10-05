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
#include <map>
#include <list>
#include <algorithm>
#include <cmath>

using std::deque; using std::vector; using std::string;

//Function Prototypes
//========================================================================
void read_file(char*, deque<vector<int>>&);
void print_int_set(const deque<vector<int>>&);
void print_bool_set(const deque<vector<bool>>&);
deque<vector<int>> generate_next_candidate_set(const deque<vector<int>>&, const deque<vector<int>>&);
deque<vector<int>> generate_c1_set(const deque<vector<int>>&);
deque<vector<int>> get_frequent_sets(const deque<vector<int>>&, const deque<vector<int>>&, double);
deque<vector<int>> apriori_alg(const deque<vector<int>>&, double);
//========================================================================


//main function
//========================================================================
int main(int argc, char** argv){

	if(argc < 3){
		std::cerr << "Error: Not enough arguments.\n";
		std::cerr << "Usage: myapriori [path_to_file] [frequency]";
		exit(1);
	}

	//Get Min Support
	std::cout << "Getting Minimum Support\n";
	int len = 0;
	double min_support = 0;
	for(int i = 0; argv[2][i] != '\0'; ++i){
		++len;
	}
	for(int i = 0; argv[2][i] != '\0'; ++i){
		min_support += ((argv[2][i] - '0') * pow(10, len - i - 1));
	}

	//Print
	std::cout << "Min Support: " << min_support << '\n';

	//Create Data Sets
	std::cout << "Reading Data Sets\n";
	deque<vector<int>> int_item_sets;
	read_file(argv[1], int_item_sets);

	//Calculate frequent item sets
	std::cout << "Running Apriori Algorithm\n";
	deque<vector<int>> frequent_sets = apriori_alg(int_item_sets, min_support);
	std::cout << "Completed Apriori Algorithm\n";

	//print results
	std::cout << "Printing Results\n";
	std::cout << "Frequent Item Sets:\n";
	std::cout << "=======================================\n";
	print_int_set(frequent_sets);
	std::cout << "=======================================\n";

	return 0;
}
//========================================================================


//Function Implementations
//========================================================================
void read_file(char* file_name, deque<vector<int>>& int_item_sets){
	std::ifstream in_file(file_name);

	//Candidate Set 1 
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

	//boolean set creation code
	/*
		bool_item_sets.push_back(vector<bool>(c1.size(), false));
		for(const std::vector<int> v : int_item_sets){
			for(int item : v){
				(*(bool_item_sets.end() - 1))[item - 1] = true;
			}
			bool_item_sets.push_back(vector<bool>(c1.size(), false));	
		}
	*/

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

deque<vector<int>> generate_next_candidate_set(const deque<vector<int>>& prev_freq_sets, const deque<vector<int>>& first_freq_set){
	deque<vector<int>> result;
	vector<int> cur_set;

	for(const vector<int>& v : prev_freq_sets){
		for(vector<int> ele : first_freq_set){
			if(std::find(v.begin(), v.end(), ele[0]) == v.end()){
				//std::cerr << "Didn't find ele[0]\n";
				vector<int> clone(v);
				//std::cerr << "CLONE:\n";
				//for(int x : clone){std::cerr << x;}
				//std::cerr << "\n";

				for(vector<int>::iterator itr = clone.begin(); itr != clone.end(); ++itr){
					if(ele[0] < *itr || itr == clone.end() - 1){
						if(itr == clone.end() - 1 && !(ele[0] < *itr)){
							clone.push_back(ele[0]);
						}else{
							clone.insert(itr, ele[0]);
						}

						if(std::find(result.begin(), result.end(), clone) == result.end()){
							result.push_back(clone);
						}
						break;
					}
				}
			}
		}
	}

	return result;
}

deque<vector<int>> generate_c1_set(const deque<vector<int>>& item_sets){
	deque<vector<int>> c1;
	for(const vector<int>& v : item_sets){
		for(int x : v){
			vector<int> temp; temp.push_back(x);
			if(std::find(c1.begin(), c1.end(), temp) == c1.end()){
				c1.push_back(temp);
			}
		}
	}

	return c1;
}

deque<vector<int>> get_frequent_sets(const deque<vector<int>>& item_sets, const deque<vector<int>>& candidate_set, double min_support){
	deque<vector<int>> frequent_set;

	std::map<vector<int>, int> frequency_map;
	for(vector<int> v : candidate_set){
		frequency_map.emplace(v, 0);
	}

	for(const vector<int>& c_set : candidate_set){
		for(const vector<int>& set : item_sets){
			vector<int>::const_iterator candidate_itr = c_set.begin();
			vector<int>::const_iterator set_itr = set.begin();
			while(candidate_itr != c_set.end() && set_itr != set.end()){
				if(*candidate_itr == *set_itr){
					++candidate_itr;
				}
				++set_itr;
			}
			if(candidate_itr == c_set.end()){
				frequency_map.find(c_set)->second += 1;
			}
		}
	}

	for(auto pair : frequency_map){ 
		double frequency = ((double)pair.second / item_sets.size()) * 100;
		if(frequency >= min_support){
			frequent_set.push_back(pair.first);
		}
	}

	return frequent_set;
}

deque<vector<int>> apriori_alg(const deque<vector<int>>& item_sets, double min_support){

	deque<vector<int>> result;
	deque<vector<int>> ck;
	deque<vector<int>> fk;
	deque<vector<int>> f1;

	int set_len = 1;
	int max_len;
	
	ck = generate_c1_set(item_sets);
	fk = get_frequent_sets(item_sets, ck, min_support);
	f1 = fk;

	for(vector<int> v : f1){result.push_back(v);}
	++max_len;

	max_len = ck.size();

	while(set_len <= max_len){
		ck = generate_next_candidate_set(fk, f1);
		if(ck.size() == 0){break;}
		fk = get_frequent_sets(item_sets, ck, min_support);
		if(fk.size() == 0){break;}
		for(vector<int> v : fk){result.push_back(v);}
		++max_len;
	}

	return result;
}
//========================================================================