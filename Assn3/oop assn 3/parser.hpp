#pragma once 
#include <iostream>
#include <vector>
#include<fstream>

using namespace std; 

class parser {
public: 
	vector<int> load_image(const char*);					//open file and save integers into the vector 
	vector<string> load_config(const char*);				//decide artist type and drawer type 
	void write_result(const char*, const string&);			//save result into the ouput txt file 
};

