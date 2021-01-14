#include "chessboard.h"

Chessboard::Chessboard(QWidget *parent) : QGraphicsView(parent)
{
    Scene = new QGraphicsScene(this);
    RedLine = new QGraphicsLineItem*[8];
    this->setScene(Scene);
    chessboard_init();
    setMouseTracking(true);
//    startTimer(500);
}

void Chessboard::chessboard_init(){
    Scene->setBackgroundBrush(QColor("#B1723C"));
    playerhand = Black;

    QPen pen;
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);

    QBrush brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);

    Scene->addRect(20,40,600,600, pen, brush);

    pen.setColor(Qt::black);
    pen.setWidth(1);
    for(int i = 0; i < 15; ++i){
        Scene->addLine(40 + i*40, 60, 40 + i*40, 620, pen);
        Scene->addLine(40, 60 + i*40, 600, 60 + i*40, pen);
    }

    brush.setColor(Qt::black);
    Scene->addRect(155, 175, 10, 10, pen, brush);
    Scene->addRect(475, 175, 10, 10, pen, brush);
    Scene->addRect(155, 495, 10, 10, pen, brush);
    Scene->addRect(315, 335, 10, 10, pen, brush);
    Scene->addRect(475, 495, 10, 10, pen, brush);

    pen.setColor(Qt::red);
    for(int i = 0; i < 8; ++i){
        RedLine[i] = Scene->addLine(0,0,0,0);
        RedLine[i]->setPen(pen);
    }

}

void Chessboard::mouseMoveEvent(QMouseEvent *event){
    mouse_x = (event->x() - 140) / 40;
    mouse_y = (event->y() - 50) / 40;
    for(int i = 0; i < 8; ++i) RedLine[i]->update();
    repaint_rect();
}

void Chessboard::repaint_rect(){
    if((mouse_x*40 + 20) >= 0 && (mouse_x*40 + 20) <= 600 &&
            (mouse_y*40 + 50) >= 20 && (mouse_y*40 + 50) <= 620){
        RedLine[0]->setLine((mouse_x + 1) * 40 - 20, (mouse_y + 1) * 40,
                       (mouse_x + 1) * 40 - 10, (mouse_y + 1) * 40);
        RedLine[1]->setLine((mouse_x + 1) * 40 + 20, (mouse_y + 1) * 40,
                       (mouse_x + 1) * 40 + 10, (mouse_y + 1) * 40);
        RedLine[2]->setLine((mouse_x + 1) * 40 - 20, (mouse_y + 1) * 40 + 40,
                       (mouse_x + 1) * 40 - 10, (mouse_y + 1) * 40 + 40);
        RedLine[3]->setLine((mouse_x + 1) * 40 + 20, (mouse_y + 1) * 40 + 40,
                       (mouse_x + 1) * 40 + 10, (mouse_y + 1) * 40 + 40);
        RedLine[4]->setLine((mouse_x + 1) * 40 - 20, (mouse_y + 1) * 40,
                       (mouse_x + 1) * 40 - 20, (mouse_y + 1) * 40 + 10);
        RedLine[5]->setLine((mouse_x + 1) * 40 + 20, (mouse_y + 1) * 40,
                       (mouse_x + 1) * 40 + 20, (mouse_y + 1) * 40 + 10);
        RedLine[6]->setLine((mouse_x + 1) * 40 - 20, (mouse_y + 1) * 40 + 40,
                       (mouse_x + 1) * 40 - 20, (mouse_y + 1) * 40 + 30);
        RedLine[7]->setLine((mouse_x + 1) * 40 + 20, (mouse_y + 1) * 40 + 40,
                       (mouse_x + 1) * 40 + 20, (mouse_y + 1) * 40 + 30);
    }
    else{
        return;
    }
}


//void Chessboard::timerEvent(QTimerEvent *event){
//    qDebug() << piece_all[mouse_x][mouse_y] << endl;
//}

void Chessboard::mousePressEvent(QMouseEvent *event){
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);

    if((mouse_x*40 + 40) >= 20 && (mouse_x*40 + 40) <= 620 &&
            (mouse_y*40 + 20) >= 20 && (mouse_y*40 + 20) <= 640
            && piece_all[mouse_x][mouse_y] == None){
        if(playerhand == White){
            piece_all[mouse_x][mouse_y] = White;
            PlayerPiece.push_back(Scene->addEllipse(QRect((mouse_x + 1) * 40 - 18, (mouse_y + 1) * 40, 36, 36),
                              pen, QBrush(Qt::white)));
            playerhand = Black;
        }
        else{
            piece_all[mouse_x][mouse_y] = Black;
            PlayerPiece.push_back(Scene->addEllipse(QRect((mouse_x + 1) * 40 - 18, (mouse_y + 1) * 40, 36, 36),
                              pen, QBrush(Qt::black)));
            playerhand = White;
        }
        emit judgeWin();
        qDebug() << mouse_x << "," << mouse_y << endl;
    }
}

void Chessboard::piece_clear(){
    for(int i = 0; i < PlayerPiece.size(); ++i) {
        PlayerPiece[i]->update();
        PlayerPiece[i]->setVisible(false);
    }
    for(int i = 0; i < 15; ++i)
        for(int j = 0; j < 15; ++j)
            piece_all[i][j] = None;
    PlayerPiece.clear();

}

void Chessboard::clear_signle(int x, int y, int n){
    piece_all[x][y] = None;
    PlayerPiece[n - 1]->setVisible(false);
    PlayerPiece.erase(&PlayerPiece[n - 1]);
}

