#include "board.h"
#include <iostream>
#include <gameui.h>

Board::Board()
{
    //dynamically allocated shared array for _board and buffer.
    _board = new SharedArray<Block>[4];
    for (int i = 0; i < 4; i++){
        _board[i] = SharedArray<Block>(new Block[4]);
    }

    buffer = new SharedArray<Block>[4];
    for (int i = 0; i < 4; i++){
        buffer[i] = SharedArray<Block>(new Block[4]);
    }

    //initialize score and buffer_score.
    //score = 0;
    //buffer_score = 0;

}

void Board::generate_random_number(){
    //this function created a random block that has either 2 or 4 by chance in a random place.

    srand(static_cast<unsigned>(time(nullptr)));
    int x, y;

    while(true){
        //this will generate a number between 0 to 3.
        x = rand() % 4;
        y = rand() % 4;
        int cost = rand() % 10;
        if(_board[x][y].get_value() == 0){ //check where the (x,y) already contain a block or not.

            //this if statement will determine whether the newly generated block contains either 2 or 4.
            if(cost < 2){ //20% chance
                _board[x][y].set_value(4);
                break;
            }else{ //80% chance
                _board[x][y].set_value(2);
                break;
            }
        }
    }

    //this will append the newly generated block into the txt file
    QString progress = "GENERATE " + QString::number(x+1) + " " + QString::number(y+1) + " " + QString::number(_board[x][y].get_value());
    QFile file ("progress.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        QTextStream stream(&file);
        stream << progress << '\n';
        file.close();
    }

    return;
}

//saves the board information before the movement occurs. The saved buffer will be used for restore function.
void Board::copy(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            buffer[i][j].set_value(_board[i][j].get_value());
        }
    }
    //buffer_score = score;
}

//This is when the user clicks the restore button
// Restore the values from the buffer to the main board
void Board::restore(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            _board[i][j].set_value(buffer[i][j].get_value());
            buffer[i][j].set_value(0);
        }
    }
    //score = buffer_score;
}

// Move tiles upwards
void Board::moveUp(){

    int move = 0;

    // Iterate over the columns
    for(int j = 0; j < 4; j++){

        // Iterate over the rows from second row to the last
        for (int i = 1; i < 4; i ++){
            if(_board[i][j].get_value() != 0){
                move = i - 1;

                // Move the tile upwards until reaching the top or another tile
                while(_board[move][j].get_value() == 0){
                    _board[move][j].set_value(_board[move+1][j].get_value());
                    _board[move+1][j].set_value(0);

                    if(move == 0){
                        break;
                    }else{
                        move --;
                    }
                }
            }
        }
    }

    return;
}

// Merge tiles upwards
int Board::MergeUp(){
    int score = 0;
    for(int j = 0; j < 4; j++){
        for (int i = 1; i < 4; i ++){
            if(_board[i][j].get_value() != 0 && _board[i-1][j].get_value() == _board[i][j].get_value()){
                int merge = 2* (_board[i][j].get_value());
                _board[i-1][j].set_value(2 * _board[i][j].get_value());
                _board[i][j].set_value(0);
                score += merge;

                // Print the updated score on application output
                //std::cout << "board score: " << score << std::endl;

                // Save the merge progress to a file
                QString progress = "MERGE " + QString::number(i) + " " + QString::number(j+1) + " " + QString::number(merge);
                QFile file ("progress.txt");
                if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
                    QTextStream stream(&file);
                    stream << progress << '\n';
                    file.close();
                }

                i++;
            }
        }
    }

     // Move the tiles again after merging
    moveUp();

    return score;
}

// Move tiles downwards
void Board::moveDown(){
    int move = 0;

    // Iterate over the columns
    for(int j = 0; j < 4; j++){

        // Iterate over the rows from third row to the first
        for (int i = 2; i >= 0; i --){
            if(_board[i][j].get_value() != 0){
                move = i + 1;

                // Move the tile downwards until reaching the bottom or another tile
                while(_board[move][j].get_value() == 0){
                    _board[move][j].set_value(_board[move-1][j].get_value());
                    _board[move-1][j].set_value(0);

                    if(move == 3){
                        break;
                    }else{
                        move ++;
                    }
                }
            }
        }
    }
    return;
}

// Merge tiles downwards
int Board::MergeDown(){
    int score = 0;

    for(int j = 0; j < 4; j++){
        for (int i = 2; i >= 0; i --){
            if(_board[i][j].get_value() != 0 && _board[i][j].get_value() == _board[i+1][j].get_value()){
                int merge = 2* (_board[i][j].get_value());
                _board[i+1][j].set_value(2 * _board[i+1][j].get_value());
                _board[i][j].set_value(0);
                score += merge;

                // Print the updated score on the application output
                //std::cout << "board score: " << score << std::endl;

                // Save the merge progress to a file
                QString progress = "MERGE " + QString::number(i+2) + " " + QString::number(j+1) + " " + QString::number(merge);
                QFile file ("progress.txt");
                if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
                    QTextStream stream(&file);
                    stream << progress << '\n';
                    file.close();
                }
                i--;
            }
        }
    }

    // Move the tiles again after merging
    moveDown();

    return score;
}

// Move tiles to the right
void Board::moveRight(){
    int move = 0;

    // Iterate over the rows
    for(int i = 0; i < 4; i ++){

        // Iterate over the columns from the third column to the first
        for (int j = 2; j >= 0; j--){
            if(_board[i][j].get_value() != 0){
                move = j + 1;

                // Move the tile to the right until reaching the rightmost column or another tile
                while(_board[i][move].get_value() == 0){

                    _board[i][move].set_value(_board[i][move-1].get_value());
                    _board[i][move-1].set_value(0);

                    if(move == 3){
                        break;
                    }else{
                        move ++;
                    }
                }
            }
        }
    }

    return;
}

// Merge tiles to the right
int Board::MergeRight(){
    int score = 0;
    for(int i = 0; i < 4; i ++){
        for (int j = 2; j >= 0; j--){
            if(_board[i][j].get_value() != 0 && _board[i][j].get_value() == _board[i][j+1].get_value()){
                int merge = 2* (_board[i][j].get_value());
                _board[i][j+1].set_value(2 * _board[i][j].get_value());
                _board[i][j].set_value(0);
                score = score + merge;

                // Print the updated score on the application output
                //std::cout << "board score: " << score << std::endl;

                // Save the merge progress to a file
                QString progress = "MERGE " + QString::number(i+1) + " " + QString::number(j+2) + " " + QString::number(merge);
                QFile file ("progress.txt");
                if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
                    QTextStream stream(&file);
                    stream << progress << '\n';
                    file.close();
                }
                j--;
            }
        }
    }

    // Move the tiles again after merging
    moveRight();

    return score;
}

// Move tiles to the left
void Board::moveLeft(){
    int move = 0;

    // Iterate over the rows
    for(int i = 0; i < 4; i ++){

        // Iterate over the columns from the second column to the fourth
        for (int j = 1; j < 4; j++){
            if(_board[i][j].get_value() != 0){
                move = j - 1;

                // Move the tile to the left until reaching the leftmost column or another tile
                while(_board[i][move].get_value() == 0){
                    _board[i][move].set_value(_board[i][move+1].get_value());
                    _board[i][move+1].set_value(0);

                    if(move == 0){
                        break;
                    }else{
                        move --;
                    }
                }
            }
        }
    }


    return;
}

// Merge tiles to the left
int Board::MergeLeft(){
    int score = 0;

    for(int i = 0; i < 4; i ++){
        for (int j = 1; j < 4; j++){
            if(_board[i][j].get_value() != 0 && _board[i][j-1].get_value() == _board[i][j].get_value()){
                int merge = 2* (_board[i][j].get_value());
                _board[i][j-1].set_value(2 * _board[i][j].get_value());
                _board[i][j].set_value(0);
                score = score + merge;

                // Print the updated score on the application output
                //std::cout << "board score: " << score << std::endl;

                // Save the merge progress to a file
                QFile file("progress.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                    QString progress = "MERGE " + QString::number(i + 1) + " " + QString::number(j) + " " + QString::number(merge);
                    QTextStream stream(&file);
                    stream << progress << '\n';
                    file.close();
                }

                j++;
            }
        }
    }

    // Move the tiles again after merging
    moveLeft();

    return score;
}

// Check if any tile has moved during a move
bool Board::check_movement(){
    bool moved = false;

    // Iterate over the board
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(_board[i][j].get_value() != buffer[i][j].get_value()){
                moved = true;
            }
        }
    }
    return moved;
}

// Save the initial board state
void Board::save_initial (int x1, int x2, int y1, int y2){
    QString progress;

    // Determine the order of the coordinates
    if (x1 < x2 || (x1 == x2 && y1 < y2)){
        progress = "INITIAL " + QString::number(x1 + 1) + " " + QString::number(y1 + 1) + " " + QString::number(x2 + 1) + " " + QString::number(y2 + 1);
    }
    else if (x1 > x2 || (x1 == x2 && y1 > y2)){
        progress = "INITIAL " + QString::number(x2 + 1) + " " + QString::number(y2 + 1) + " " + QString::number(x1 +1 ) + " " + QString::number(y1 + 1);
    }

    // Save the initial board state to a file
    QFile file ("progress.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << progress << '\n';
        file.close();
    }

}
