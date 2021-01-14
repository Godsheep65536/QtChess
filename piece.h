#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include "chessboard.h"

class Piece : public QObject
{
    Q_OBJECT
    Chessboard *playview = nullptr;
public:
    explicit Piece(QObject *parent = nullptr);
    void playZone(Chessboard *view){playview = view;}
    void clean();
    void undo();

private:
    int last_x = 0, last_y = 0;
    int piece_num = 0;
    bool checkWin(int xIndex, int yIndex);
signals:
    void playerWin(QString &);
    void playerPeace();
public slots:
    void judge();
};

#endif // PIECE_H
