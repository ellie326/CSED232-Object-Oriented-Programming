#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SharedPtr.h"
#include "board.h"

class Game : public Board
{
private:
    Board game;
    int restoreCnt;
    int gamescore;
    int bufferscore;

public:
    Game(); //default constructor

    void start_the_game();
    Board get_board(){return game;}
    void add_gamescore(int num){gamescore += num; }
    int get_gamescore(){return gamescore; }
    bool check_full();
    bool check_2048();
    int get_restore_cnt(){return restoreCnt; }
    void set_restore_cnt(int num){restoreCnt -= num; }
    bool is_empty_buffer();

    void restore_buffer();
    void copy_buffer();

};

#endif // GAME_H


