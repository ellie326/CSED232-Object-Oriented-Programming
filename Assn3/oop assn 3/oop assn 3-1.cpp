#include <iostream>
#include <vector>
#include <string>
#include "artist.hpp"
#include "drawer.hpp"
#include "parser.hpp"


using namespace std;

int main(int argc, char* argv[]) {
	
	if (argc != 4) {
		cout << "argc is not 4, but " << argc << endl;
		throw;
	}
	// CREATE PARSER
	parser p;
	// LOAD IMAGE AND CONFIG
	vector<int> tokens = p.load_image(argv[1]);
	vector<string> configs = p.load_config(argv[2]);	string style_target = configs[0];
	string drawer_target = configs[1];
	char* path_output = argv[3];
	int width = tokens[0];
	int height = tokens[1];
	vector<int> vals = { tokens.begin() + 2, tokens.end() };

	// CREATE ARTIST
	artist* style;
	if (style_target == "classic") {
		style = new classic(width, height, vals);
	}
	else if (style_target == "iclassic") {
		style = new iclassic(width, height, vals);
	}
	else if (style_target == "sobelx") {
		style = new sobelx(width, height, vals);
	}
	else if (style_target == "sobely") {
		style = new sobely(width, height, vals);
	}
	else if (style_target == "gradient") {
		style = new gradient(width, height, vals);
	}
	else if (style_target == "mine"){
		style = new mine(width, height, vals);
	}
	else {
		throw;
	}

	// CREATE DRAWER
	drawer* d;
	if (drawer_target == "drawer") {
		d = new drawer(style);
	}
	else if (drawer_target == "upsample") {
		d = new upsample(style);
	}
	else if (drawer_target == "downsample") {
		d = new downsample(style);
	}
	else if (drawer_target == "scale") {
		int scale_x = stoi(configs[2]);
		int scale_y = stoi(configs[3]);
		d = new scale(style, scale_x, scale_y);
	}
	else {
		throw;
	}

	// PERFORM DRAWING
	string output = d->draw();
	cout << output;
	// WRITE OUTPUT
	p.write_result(path_output, output);
	cout << "hi" << endl;
	delete d;
	return 0;
}vector<int> parser::load_image(const char* filename) {
	ifstream input_file;
	input_file.open(filename);

	vector <int> pixel;
	string whole_text;


	while (getline(input_file, whole_text)) {
		string number_str = "";
		for (char temp : whole_text) {
			if (temp == '|') {
				int number = stoi(number_str);
				pixel.push_back(number);
				number_str = "";
			}
			else {
				number_str.append(1, temp);
			}
		}
		if (!number_str.empty()) {
			int number = stoi(number_str);
			pixel.push_back(number);
		}
	}
	input_file.close();
	return pixel;
}

vector<string> parser::load_config(const char* filename) {
	ifstream input_file;
	input_file.open(filename);

	vector <string> config;
	string whole_text;

	while (getline(input_file, whole_text)) {
		string class_str;
		for (char temp : whole_text) {
			if (temp == '|') {
				config.push_back(class_str);
				class_str = "";
			}
			else {
				class_str.append(1, temp);
			}
		}
		if (!class_str.empty()) {
			config.push_back(class_str);
		}
	}
	input_file.close();
	return config;
}

void parser::write_result(const char* path, const string& contents) {
	ofstream myfile;
	myfile.open(path);
	myfile << contents;
	myfile.close();
}char classic::mapper(int x, int y) {
	int quotient = artist::getint(x, y) / 17;
	switch (quotient) {
	case 0: return '@';
	case 1: return '&';
	case 2: return '%';
	case 3: return 'W';
	case 4: return 'X';
	case 5: return 'A';
	case 6: return 'H';
	case 7: return 'O';
	case 8: return 'T';
	case 9: return '*';
	case 10: return '^';
	case 11: return '+';
	case 12: return '-';
	case 13: return '.';
	default: return ' ';
	}
}

char iclassic::mapper(int x, int y) {
	int quotient = artist::getint(x, y) / 17;
	switch (quotient) {
	case 0: return ' ';
	case 1: return '.';
	case 2: return '-';
	case 3: return '+';
	case 4: return '^';
	case 5: return '*';
	case 6: return 'T';
	case 7: return 'O';
	case 8: return 'H';
	case 9: return 'A';
	case 10: return 'X';
	case 11: return 'W';
	case 12: return '%';
	case 13: return '&';
	default: return '@';
	}
}

char sobelx::mapper(int x, int y) {
	int current = artist::getint(x, y);
	if (x+1 == getwidth()) {
		return '0';
	}
	else {
		int next = artist::getint(x + 1, y);
		if (abs(current - next) > 50) {
			return '|';
		}
		else {
			return '0';
		}
	}
}

char sobely::mapper(int x, int y) {
	int current = artist::getint(x, y);
	if (y+1 == getheight()) {
		return ' ';
	}
	else {
		int under = artist::getint(x, y + 1);
		if (abs(current - under) > 50) {
			return '-';
		}
		else {
			return ' ';
		}
	}
}

char gradient::mapper(int x, int y) {
	int current = artist::getint(x, y);

	if (x+1 == getwidth() && y+1 == getheight()) {
		return '1';
	}
	else if (x + 1 == getwidth() && y + 1 != getheight()) {
		int under = artist::getint(x, y + 1);
		if (abs(current - under) > 50) {
			return '-';
		}
		else {
			return '2';
		}
	}
	else if (x+1 != getwidth() && y+1 == getheight()) {
		int right = artist::getint(x + 1, y);
		if (abs(current - right) > 50) {
			return '|';
		}
		else {
			return '3';
		}
	}
	else {
		int right = artist::getint(x + 1, y);
		int under = artist::getint(x, y + 1);
		if (abs(current - right) < 50 && abs(current - under) > 50) {
			return '-';
		}
		else if (abs(current - right) > 50 && abs(current - under) < 50) {
			return '|';
		}
		else if (abs(current - right) > 50 && abs(current - under) > 50) {
			return '+';
		}
		else {
			return '4';
		}
	}
}

drawer::drawer(artist* A) {
	characters_D = A->getchar();
	width_D = A->getwidth();
	height_D = A->getheight();
	delete A; 
}

string drawer::draw() {
	int position;
	string result;

	for (int i = 0; i < height_D; i++) {
		for (int j = 0; j < width_D; j++) {
			position = i * width_D + j;
			result = result + characters_D[position];
		}
		result += "\n";
	}
	return result;
}

string downsample::draw() {
	int position;
	string result;

	int width = getwidth();
	int height = getheight();
	vector<char>characters = getchar();

	for (int i = 0; i < height; i += 2) {
		for (int j = 0; j < width; j += 2) {
			position = i * width + j;
			result = result + characters[position];
		}
		result += "\n";
	}
	return result;
}

string upsample::draw() {
	int position;
	string result;

	int width = getwidth();
	int height = getheight();
	vector<char>characters = getchar();

	for (int j = 0; j < height; j++) {
		int repeat = 2;
		while (repeat) {
			for (int i = 0; i < width; i++) {
				position = j * width + i;
				result = result + characters[position] + characters[position];
			}
			result += "\n";
			repeat--;
		}
	}
	return result;
}

scale::scale(artist* A, int x, int y)
	:drawer(A)
{
	x_mul = x;
	y_mul = y;
	width = getwidth();
	height = getheight();
	characters = getchar();
}

string scale::draw() {
	string result;

	if (y_mul > 1) {// y축 늘리기 
		increase_y(result);
	}
	else if (y_mul == 1) {
		same_y(result);
	}
	else {
		decrease_y(result);
	}

	return result;
}

void scale::increase_y(string& result) {

	for (int j = 0; j < height; j++) {
		for (int y_cnt = y_mul; y_cnt > 0; y_cnt--) {
			if (x_mul == 1) { // same 
				for (int i = 0; i < width; i++) {
					int position = j * width + i;
					result = result + characters[position];
				}
			}
			else if (x_mul > 1) { // increase x 
				for (int i = 0; i < width; i++) {
					int position = j * width + i;
					for (int x_cnt = x_mul; x_cnt > 0; x_cnt--) {
						result = result + characters[position];
					}
				}
			}
			else { //decrease x 
				for (int i = 0; i < width; i += abs(x_mul)) {
					int position = j * width + i;
					result = result + characters[position];
				}
			}
			result += "\n";
		}
	}
	return;
}

void scale::same_y(string& result) {

	for (int j = 0; j < height; j++) {
		if (x_mul == 1) { // same 
			for (int i = 0; i < width; i++) {
				int position = j * width + i;
				result = result + characters[position];
			}
		}
		else if (x_mul > 1) { // increase x 
			for (int i = 0; i < width; i++) {
				int position = j * width + i;
				for (int x_cnt = x_mul; x_cnt > 0; x_cnt--) {
					result = result + characters[position];
				}
			}
		}
		else { //decrease x 
			for (int i = 0; i < width; i += abs(x_mul)) {
				int position = j * width + i;
				result = result + characters[position];
			}
		}
		result += "\n";
	}
	return;
}

void scale::decrease_y(string& result) {

	for (int j = 0; j < height; j += abs(y_mul)) {
		if (x_mul == 1) { // same 
			for (int i = 0; i < width; i++) {
				int position = j * width + i;
				result = result + characters[position];
			}
		}
		else if (x_mul > 1) { // increase x 
			for (int i = 0; i < width; i++) {
				int position = j * width + i;
				for (int x_cnt = x_mul; x_cnt > 0; x_cnt--) {
					result = result + characters[position];
				}
			}
		}
		else { //decrease x 
			for (int i = 0; i < width; i += abs(x_mul)) {
				int position = j * width + i;
				result = result + characters[position];
			}
		}
		result += "\n";
	}
	return;
}

char mine::mapper(int x, int y) {
	int current = artist::getint(x, y);
	if (x+1 == getwidth()) {
		return ' ';
	}
	else {
		int next = artist::getint(x + 1, y);
		if (current > next) {
			return '>';
		}
		else {
			return '<';
		}
	}
}