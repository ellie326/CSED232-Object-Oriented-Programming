#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <QFile>
#include <QTextStream>
#include "SharedPtr.h"
#include "block.h"

class Board
{
private:
    SharedArray<SharedArray<Block>> _board;
    SharedArray<SharedArray<Block>> buffer;
    //int score;
    //int buffer_score;

public:
    //default constructor
    Board();

    //getter functions for block and buffer
    SharedArray<SharedArray<Block>> get_block (){return _board;}
    SharedArray<SharedArray<Block>> get_buffer (){return buffer;}

    //to access the board array or buffer array in form to 2d array ([#][#])
    SharedArray<Block>& operator[](int x)
    {
        return _board[x];
    }

    const SharedArray<Block>& operator[](int x) const
    {
        return _board[x];
    }

    //getter and setter function for score
    //int get_score(){return score; }
    //void set_score(int num) {score = num; }

    //generates random number when the blocks moved
    void generate_random_number();

    //when the user clicks "restore" button, go back to the previous board
    void copy();
    void restore();

    //block movement functions
    void moveUp();
    int MergeUp();

    void moveDown();
    int MergeDown();

    void moveRight();
    int MergeRight();

    void moveLeft();
    int MergeLeft();

    //check whether the blocks have moved or not
    bool check_movement();

    //when the game starts, save the initial two random number into the txt file.
    void save_initial (int, int, int, int);
};

#endif // BOARD_H
