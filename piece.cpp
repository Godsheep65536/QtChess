#include "piece.h"

Piece::Piece(QObject *parent) : QObject(parent)
{

}

void Piece::judge(){
    QString winner;
    bool peace = true;
    ++piece_num;
    for(int i = 0; i < 15; ++i){
        for(int j = 0; j < 15; ++j){
            if(checkWin(i, j) && playview->piece_all[i][j] != 0){
                if(playview->piece_all[i][j] == 1)
                    winner = tr("白方");
                else
                    winner = tr("黑方");
                emit playerWin(winner);
                return;
            }
            else if( playview->piece_all[i][j] == 0)
                peace = false;
        }
    }
    if(peace) {emit playerPeace(); return;};
    last_x = playview->mouse_x;
    last_y = playview->mouse_y;
}

bool Piece::checkWin(int xIndex, int yIndex){
    int max = 0;
    bool flag = false;
    int count = 0;
    int tempXIndex = xIndex;
    int tempYIndex = yIndex;
    // 三维数组记录横向，纵向，左斜，右斜的移动
    int dir[][2][2] = {
            // 横向
            { { -1, 0 }, { 1, 0 } },
            // 竖着
            { { 0, -1 }, { 0, 1 } },
            // 左斜
            { { -1, -1 }, { 1, 1 } },
            // 右斜
            { { 1, -1 }, { -1, 1 } } };

    for (int i = 0; i < 4; i++) {
        count = 1;
        //j为0,1分别为棋子的两边方向，比如对于横向的时候，j=0,表示下棋位子的左边，j=1的时候表示右边
        for (int j = 0; j < 2; j++) {
            flag = true;
            /**
             while语句中为一直向某一个方向遍历
             有相同颜色的棋子的时候，Count++
             否则置flag为false，结束该该方向的遍历
             **/
            while (flag) {
                tempXIndex = tempXIndex + dir[i][j][0];
                tempYIndex = tempYIndex + dir[i][j][1];

                //这里加上棋盘大小的判断，这里我设置的棋盘大小为15 具体可根据实际情况设置 防止越界
                if (tempXIndex >= 0 && tempXIndex <= 15 && tempYIndex >= 0 && tempYIndex <= 15) {
                    if (playview->piece_all[tempXIndex][tempYIndex] == playview->piece_all[xIndex][yIndex]) {
                        count++;
                    }
                    else
                        flag = false;
                }else{
                    flag = false;
                }

            }
            tempXIndex = xIndex;
            tempYIndex = yIndex;
        }

        if (count >= 5) {
            max = 1;
            break;
        } else
            max = 0;
    }
    if (max == 1)
        return true;
    else
        return false;
}

void Piece::clean(){
    playview->piece_clear();
}

void Piece::undo(){
    if(piece_num != 0){
        playview->clear_signle(last_x, last_y, piece_num);
        piece_num--;
    }
}


