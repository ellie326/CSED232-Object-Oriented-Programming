#include "game.h"
#include "gameui.h"
#include <iostream>

//initialize the private integer variables
Game::Game(){
    restoreCnt = 3;
    gamescore = 0;
    bufferscore = 0;
}

// Start the game by initializing the game board and placing two random tiles
void Game::start_the_game() {
    srand(static_cast<unsigned>(time(nullptr)));
    //provide a seed value dependent on time
    // get a random number betweem 0 ~ 3
    int x1 = rand() % 4;
    int x2 = rand() % 4;
    int y1 = rand() % 4;
    int y2 = rand() % 4;

    // When two pairs of (x,y) are equal, regenerate the second pair
    while (x1 == x2 && y1 == y2) {
        x2 = rand() % 4;
        y2 = rand() % 4;
    }

    // Set the value of the tiles at the generated coordinates to 2
    game.get_block()[x1][y1].set_value(2);
    game.get_block()[x2][y2].set_value(2);

    // Save the initial state of the game
    save_initial(x1, x2, y1, y2);

    return;
}

// Check if the game board is full (all tiles are occupied) or there are adjacent tiles with the same value
bool Game::check_full(){
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){

            // There is an empty tile
            if(game.get_block()[i][j].get_value() == 0)
                return true;

            // There are adjacent tiles with the same value horizontally
            if(j < 3 && game.get_block()[i][j].get_value() == game.get_block()[i][j+1].get_value())
                return true;

            // There are adjacent tiles with the same value vertically
            if(i < 3 && game.get_block()[i][j].get_value() == game.get_block()[i+1][j].get_value())
                return true;
        }
    }

    // The board is full and there are no adjacent tiles with the same value
    return false;
}

// Check if the game has reached the 2048 tile
bool Game::check_2048(){
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){

            // The 2048 tile is present on the board
            if(game.get_block()[i][j].get_value() == 2048)
                return true;
        }
    }

    // The 2048 tile is not present on the board
    return false;
}

// Check if the buffer (used for restoring) is empty
bool Game::is_empty_buffer(){
    bool check = true;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){

            // The buffer is not empty
            if(game.get_buffer()[i][j].get_value() != 0)
                check = false;
        }
    }

    // The buffer is empty
    return check;
}

void Game::copy_buffer(){
    bufferscore = gamescore;
    game.copy();
}

void Game::restore_buffer(){
    gamescore = bufferscore;
    bufferscore = 0;
    game.restore();
}



