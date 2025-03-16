#ifndef BLOCKUI_H
#define BLOCKUI_H

#include <QtWidgets>
#include <iostream>

class BlockUi : public QLabel
{
public:
    BlockUi(QWidget* parent = nullptr) : QLabel(parent){

        // Set the size of the block
        setFixedSize(250, 250);

        // Set the text alignment to center
        setAlignment(Qt::AlignCenter);
    }
    void setBlockValue(int value)
    {
        QString styleSheet;

        // Apply appropriate style based on the value of the block
        switch (value)
        {
        case 0:
            styleSheet = "QLabel { background: rgb(255, 255, 255); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 2:
            styleSheet = "QLabel { background: rgb(187, 173, 160); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 4:
            styleSheet = "QLabel { background: rgb(237, 224, 200); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 8:
            styleSheet = "QLabel { background: rgb(242, 177, 121); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 16:
            styleSheet = "QLabel { background: rgb(245, 149, 99); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 32:
            styleSheet = "QLabel { background: rgb(246, 126, 95); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 64:
            styleSheet = "QLabel { background: rgb(246, 94, 59); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 128:
            styleSheet = "QLabel { background: rgb(237, 207, 114); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 256:
            styleSheet = "QLabel { background: rgb(237, 204, 97); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 512:
            styleSheet = "QLabel { background: rgb(237, 200, 80); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 1024:
            styleSheet = "QLabel { background: rgb(237, 197, 63); color: black; border-style: solid; font: bold 70pt; }";
            break;
        case 2048:
            styleSheet = "QLabel { background: rgb(237, 194, 46); color: black; border-style: solid; font: bold 70pt; }";
            break;
        default:
            styleSheet = "QLabel { background: rgb(255, 255, 255); color: black; border-style: solid; font: bold 70pt; }";
            break;
        }

        // Set the text and style sheet of the QLabel based on the value
        if(value != 0){
            setText(QString::number(value));
        }else{
            setText(QString());
        }
        setStyleSheet(styleSheet);

    }
};

#endif // BLOCKUI_H
