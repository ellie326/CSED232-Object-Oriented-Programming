#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include "SharedPtr.h"

class Block
{
private:
    //saves a value for each 4 X 4 block on the board
    int value;

public:
    // default constructor
    Block();

    //returns the private value
    int get_value(){return value; }

    //update the value if two blocks merges or new random block is created
    void set_value(int key){value = key; return; }

};

#endif // BLOCK_H
