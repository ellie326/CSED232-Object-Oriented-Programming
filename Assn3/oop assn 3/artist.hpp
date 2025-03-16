#pragma once 
#include <iostream>
#include <cstdlib>
using namespace std; 

class artist {	
	int width, height;															//private member 
	vector<int> numbers;
	vector<char> characters;
public: 
	artist(int width_, int height_, const std::vector<int>& pixel) {			//constructor 
		width = width_; 
		height = height_; 
		numbers = pixel; 
	} 
	artist() { width = 0; height = 0; }											//default constructor 
	virtual ~artist() { cout << "artist destroyed"; }

	virtual char mapper(int, int) { return ' '; } 
	void setchar(vector<char> characters_) { characters = characters_; }		//setter function used in other classes 
	int getint(int x, int y) {													//when x and y coordinates given, return its position in 1D vector 
		int position = y * width + x; 
		return numbers[position]; }
	vector<char> getchar() const { return characters; }							//getter functions used in other classes 
	int getwidth() const { return width; }
	int getheight() const { return height; }
};

class classic : public artist {											//classic : bigger number -> complex character 
public: 
	classic(int width, int height, const std::vector<int>& pixel) 
		: artist(width, height, pixel)									//use artist constructor (inheritance) 
	{
		vector<char>chars ;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				chars.push_back(classic::mapper(i, j));					//add a returned character from classic mapper function "chars" vector 
			}
		}
		artist::setchar(chars);											//save above "chars" vector to "characters" vector in artist private member 
	}  
	classic() :artist() {  }												// default constructor
	~classic() { cout << "classic destroyed"; }
	
	char mapper(int, int);												//input of x, y coordinate and returns corresponding character 
};

class iclassic : public artist {										//iclassic : smaller number -> complex character 
public:
	iclassic(int width, int height, const std::vector<int>& pixel)
		: artist(width, height, pixel)									//use artist constructor (inherited) 
	{
		vector<char>chars;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				chars.push_back(iclassic::mapper(i, j));				//add a returned character from iclassic mapper function "chars" vector 
			}
		}
		artist::setchar(chars);											//save above "chars" vector to "characters" vector in artist private member 
	}
	iclassic() :artist() {}												// default constructor
	~iclassic() { cout << "iclassic destroyed "; }

	char mapper(int, int);												//input of x, y coordinate and returns corresponding character 
};

class sobelx : public artist {											//if x and x+1 (coordinate) has difference greater than 50, return "|"
public:
	sobelx(int width, int height, const std::vector<int>& pixel)		//constructor 
		: artist(width, height, pixel)									//use artist constructor (inherited) 
	{
		vector<char>chars;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				chars.push_back(sobelx::mapper(i, j));					//add a returned character from sobelx mapper function "chars" vector 
			}
		}
		artist::setchar(chars);											//save above "chars" vector to "characters" vector in artist private member 
	}
	sobelx() :artist() {}												// default constructor
	~sobelx() {}

	char mapper(int, int);												//input of x, y coordinate and returns corresponding character 
};

class sobely : public artist {											//if y and y+1 (coordinate) has difference greater than 50, return "-"
public:
	sobely(int width, int height, const std::vector<int>& pixel)		//constructor 
		: artist(width, height, pixel)									//use artist constructor (inherited) 
	{
		vector<char>chars;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				chars.push_back(sobely::mapper(i, j));					//add a returned character from sobely mapper function "chars" vector 
			}
		}
		artist::setchar(chars);											//save above "chars" vector to "characters" vector in artist private member
	}
	sobely() :artist() {}												// default constructor
	~sobely() {}

	char mapper(int, int);												//input of x, y coordinate and returns corresponding character 
};

class gradient : public artist {										//sobelx and sobely and if both, then return "+" 
public:
	gradient(int width, int height, const std::vector<int>& pixel)		//constructor 
		: artist(width, height, pixel)									//use artist constructor (inherited) 
	{
		vector<char>chars;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				chars.push_back(gradient::mapper(i, j));				//add a returned character from gradient mapper function "chars" vector 
			}
		}
		artist::setchar(chars);											//save above "chars" vector to "characters" vector in artist private member
	}
	gradient() :artist() {}												// default constructor
	~gradient() {}
	
	char mapper(int, int);												//input of x, y coordinate and returns corresponding character 
};

class mine: public artist {												//assignment #5 problem 
public: 
	mine(int width, int height, const std::vector<int>& pixel)
		: artist(width, height, pixel)
	{
		vector<char>chars;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				chars.push_back(mine::mapper(i, j));
			}
		}
		chars.push_back(' ');
		artist::setchar(chars);
	}
	mine() :artist() {} // default constructor
	~mine() {}

	char mapper(int, int);
};