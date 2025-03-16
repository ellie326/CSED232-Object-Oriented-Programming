#pragma once 
#include <iostream>

using namespace std; 

class drawer {
	int width_D, height_D;									//private member 
	vector<char> characters_D; 
public: 
	drawer(artist* A);										//constructor 
	drawer() { width_D = 0; height_D = 0; }					//default constructor 
	virtual ~drawer() { cout << "drawer destroyed ";  }

	int getwidth() { return width_D; }						//getter functions used in other classes 
	int getheight() { return height_D; }
	vector<char> getchar() { return characters_D; }

	virtual string draw();									//same function name for inherited classes, so virtual 
};

class downsample : public drawer {
public: 
	downsample(artist* A): drawer(A) { }					//constructor & uses drawer constructor 
	downsample() : drawer() {}								//default constructor 
	~downsample() { cout << "downsample destroyed "; }
	string draw(); 
};

class upsample : public drawer {
public: 
	upsample(artist* A) : drawer(A){ }					//constructor & uses drawer constructor 
	upsample() : drawer() {}								//default constructor 
	~upsample() { cout << "upsample destroyed"; }
	string draw(); 
};

class scale : public drawer {	
	int x_mul, y_mul;										//private member 
	int width, height; 
	vector<char>characters; 

	void increase_y(string&); 
	void same_y(string&);
	void decrease_y(string&);

public: 
	scale(artist*, int, int); 
	scale() { x_mul = 0; y_mul = 0; width = 0; height = 0; }
	~scale() { cout << "scale destroyed"; }
	string draw(); 
};

