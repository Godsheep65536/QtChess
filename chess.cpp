#include "chess.h"
#include "./ui_chess.h"

Chess::Chess(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
    this->PlayTime = new QTimer(this);
    this->play = new Piece(this);


    this->play->playZone(ui->graphicsView);
    setWindowTitle("五子棋");
    setFixedSize(900, 800);

    connect(PlayTime, SIGNAL(timeout()), this, SLOT(TimerTimeOut()));
    connect(ui->graphicsView, &Chessboard::judgeWin, play, &Piece::judge);
    connect(play, &Piece::playerWin, this, &Chess::Win);
    connect(play, &Piece::playerPeace, this, &Chess::Peace);

}

Chess::~Chess()
{
    disconnect(PlayTime, SIGNAL(timeout()), this, SLOT(TimerTimeOut()));
    disconnect(ui->graphicsView, &Chessboard::judgeWin, play, &Piece::judge);
    disconnect(play, &Piece::playerWin, this, &Chess::Win);
    disconnect(play, &Piece::playerPeace, this, &Chess::Peace);
    delete play;
    delete ui;
}

void Chess::TimerTimeOut(){
    ui->lcdnum->display(time);
    ++time;
}

void Chess::on_pushButton_clicked()
{
    play->undo();
}

void Chess::on_pushButton_2_clicked()
{
    QMessageBox::information(this, tr("和棋"), tr("黑白和棋, 请重新开局"));
}

void Chess::on_pushButton_3_clicked()
{
    time = 0;
    PlayTime->start(1000);
    play->clean();
}

void Chess::Win(QString & winner){
    QMessageBox::information(this, winner, winner+tr("获胜, 请重新开局"));
}

void Chess::Peace(){
    QMessageBox::information(this, tr("和棋"), tr("本局和棋, 请重新开局"));
}

