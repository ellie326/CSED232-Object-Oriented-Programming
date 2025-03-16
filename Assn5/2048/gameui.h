#ifndef GAMEUI_H
#define GAMEUI_H

#include <QtWidgets>
#include <QKeyEvent>
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QTextStream>


#include "blockui.h"
#include "board.h"
#include "game.h"

class GameUi : public QWidget
{
private:

    // Array of BlockUi objects representing the game board
    BlockUi* blocks [4][4];

    // Pointer to a Game object
    Game* temp;
    int score;
public:
    GameUi(Game t, QWidget* parent = nullptr) : QWidget(parent)
    {
        temp = new Game;
        *temp = t;
        score = 0;
        // Set the focus policy to receive key events
        setFocusPolicy(Qt::StrongFocus);
        // Set the size of the widget
        resize(1300, 1000);

        // Create a grid layout to arrange the blocks and score label
        QGridLayout* gridLayout = new QGridLayout;
        gridLayout->setSpacing(10);
        gridLayout->setColumnStretch(4,1000);
        gridLayout->setRowStretch(4,1000);

        // Create BlockUi objects and add them to the grid layout
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                BlockUi* blockUi = new BlockUi;
                gridLayout->addWidget(blockUi, row, col);
                blocks[row][col] = blockUi;
            }
        }

        // Create a score label and add it to the grid layout
        QLabel* scoreLabel = new QLabel;
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setAlignment(Qt::AlignCenter);
        scoreLabel->setFont(QFont("Arial", 20, QFont::Bold));
        gridLayout->addWidget(scoreLabel, 0, 4, 1, 1);

        // Create exit and restore buttons
        QPushButton* exitButton = new QPushButton("EXIT", this);
        QPushButton* restoreButton = new QPushButton("Restore", this);

        // Set the size of the buttons
        exitButton->setFixedSize(300, 200);
        restoreButton->setFixedSize(300, 200);

        // Set the font for the buttons
        exitButton->setFont(QFont("Arial", 20, QFont::Bold));
        restoreButton->setFont(QFont("Arial", 20, QFont::Bold));

        // Create a vertical layout for the buttons
        QVBoxLayout* buttonLayout = new QVBoxLayout;
        buttonLayout->addWidget(exitButton);
        buttonLayout->addWidget(restoreButton);
        buttonLayout->setSpacing(20);
        buttonLayout->setAlignment(Qt::AlignCenter);

        // Create a horizontal layout for the main content
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addLayout(gridLayout);
        mainLayout->addLayout(buttonLayout);
        mainLayout->setAlignment(buttonLayout, Qt::AlignBottom | Qt::AlignRight);
        mainLayout->setSpacing(20);

        exitButton->setFocusPolicy(Qt::NoFocus);
        restoreButton->setFocusPolicy(Qt::NoFocus);

        // Set the main layout for the widget
        setLayout(mainLayout);

        // Connect button signals to corresponding slots
        connect(exitButton, &QPushButton::clicked, this, &GameUi::showExitConfirmation);
        connect(restoreButton, &QPushButton::clicked, this, &GameUi::showRestoreConfirmation);

    }

    // Function to update the UI based on the board state
    void updateUi(Board b)
    {
        score = temp->get_gamescore();
        std::cout <<"score : " << score << std::endl;

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                //pint the board on the application output
                std::cout << b.get_block()[row][col].get_value() << "\t";
                int blockValue = b.get_block()[row][col].get_value();
                blocks[row][col]->setBlockValue(blockValue);
            }
            std::cout << std::endl;
        }

        // Update the score label with the current score

        // Find the score label widget
        QLabel* scoreLabel = findChild<QLabel*>("scoreLabel");
        if (scoreLabel) {

            // Update the score label text
            scoreLabel->setText("Score: " + QString::number(score));
        }

        // Write the progress (score) to a file
        QString progress = "Score " + QString::number(score);
        QFile file ("progress.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << progress << '\n';
             file.close();
        }
    }

    // Handle key press events
    void keyPressEvent(QKeyEvent *event) override
    {
        if(temp->check_full()){
             temp->copy_buffer();
            if (event->type() == QEvent::KeyPress)
            {
                switch(event->key())
                {
                case Qt::Key_Up:
                    move_up();
                    break;
                case Qt::Key_Down:
                    move_down();
                    break;
                case Qt::Key_Left:
                    move_left();
                    break;
                case Qt::Key_Right:
                    move_right();
                    break;
                default: ;
                    break;
                }
            }
            if(temp->check_2048()){
                QMessageBox::information(this, "Win", "Congratulations! \nScore: " + QString::number(score));
                QApplication::quit();
            }
        }
        else{
            QMessageBox::information(this, "Game Over", "You lose...\nScore: "+ QString::number(score));
            QApplication::quit();
        }
        QWidget::keyPressEvent(event);
    }

    // Move the blocks up
    void move_up(){
        QString progress = "UP";
        QFile file ("progress.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << progress << '\n';
            file.close();
        }

        //print the key pressed
        //std::cout << "move up" << std:: endl;

        temp->get_board().moveUp();
        temp->add_gamescore(temp->get_board().MergeUp());

        if(temp->get_board().check_movement()){
            temp->get_board().generate_random_number();
        }
        updateUi(temp->get_board());
    }

    // Move the blocks down
    void move_down(){
        QString progress = "DOWN";
        QFile file ("progress.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << progress << '\n';
            file.close();
        }

        //print the key pressed
        //std::cout << "move down" << std:: endl;

        temp->get_board().moveDown();
        temp->add_gamescore(temp->get_board().MergeDown());

        if(temp->get_board().check_movement()){
            temp->get_board().generate_random_number();
        }
        updateUi(temp->get_board());
    }

    // Move the blocks left
    void move_left(){
        QString progress = "LEFT";
        QFile file ("progress.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << progress << '\n';
            file.close();
        }

        //print the key pressed
        //std::cout << "move left" << std:: endl;


        temp->get_board().moveLeft();
        temp->add_gamescore(temp->get_board().MergeLeft());

        if(temp->get_board().check_movement()){
            temp->get_board().generate_random_number();
        }
        updateUi(temp->get_board());
    }

    // Move the blocks right
    void move_right(){
        QString progress = "RIGHT";
        QFile file ("progress.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file);
            stream << progress << '\n';
            file.close();
        }

        //print the key pressed
        //std::cout << "move right" << std:: endl;

        temp->get_board().moveRight();
        temp->add_gamescore(temp->get_board().MergeRight());

        if(temp->get_board().check_movement()){
            temp->get_board().generate_random_number();
        }
        updateUi(temp->get_board());
    }

    // Show exit confirmation dialog
    void showExitConfirmation() {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Exit", "Are you sure to quit?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qApp->quit(); // end the program
        }
    }

    // Show restore confirmation dialog
    void showRestoreConfirmation()
    {
        if(temp->is_empty_buffer()){
            QMessageBox::information(this, "Restore", "There is no previously saved board in the buffer");
        }else if(temp->get_restore_cnt() == 0){
            QMessageBox::information(this, "Restore", "No more chance to restore the board to its previous state");
        }
        else{
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Restore", "Restore the game board to its previous state?\nRemaining chances: " + QString::number(temp->get_restore_cnt()), QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                temp->restore_buffer();
                temp->set_restore_cnt(1);
                std::cout << "restore" << std::endl;
                updateUi(temp->get_board());
            }
        }
    }
};

#endif // GAMEUI_H
