#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <qpalette.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QDebug>
#include <QVector>

class Chessboard : public QGraphicsView
{
    Q_OBJECT
    typedef enum {
        None,
        White,
        Black,
    }PieceColor;
    QGraphicsScene* Scene;
    PieceColor playerhand;
    QVector<QGraphicsEllipseItem*> PlayerPiece;
    QGraphicsLineItem **RedLine;
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
//    void timerEvent(QTimerEvent *event);
public:
    int mouse_x = 0, mouse_y = 0;
    PieceColor piece_all[15][15] = {None};
    explicit Chessboard(QWidget *parent = nullptr);
    void piece_clear();
    void clear_signle(int ,int, int);
signals:
    void judgeWin();
private:
    QLine *redLine;
    void chessboard_init();
    void repaint_rect();
};

#endif // CHESSBOARD_H
