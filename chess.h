#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include <QPainter>
#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include "chessboard.h"
#include "piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Chess; }
QT_END_NAMESPACE

class Chess : public QWidget
{
    Q_OBJECT

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void TimerTimeOut();
    void Win(QString &);
    void Peace();
private:
    QTimer *PlayTime;
    Piece *play = nullptr;
    int time = 0;
    Ui::Chess *ui;
};
#endif // CHESS_H
