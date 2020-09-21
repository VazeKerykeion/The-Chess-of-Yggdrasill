//
// Created by 10031 on 2020/7/18.
//

#include "chessBoard.h"

#include <QMessageBox>
chessboard::chessboard() {
    board=new cell *[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new cell[8];
        for (int j = 0; j < 8; j++) {
            board[i][j].chessType = 0;
            // C1 至 F1 设置为灰方根源区域
            if (j > 1 && j < 6 && i == 0) board[i][j].root = -1;
                // C8 至 F8 设置为青方根源区域
            else if (j > 1 && j < 6 && i == 7) board[i][j].root = 1;
                // 其余设置为普通区域;
            else board[i][j].root = 0;
        }
    }

    // D2,E2设置为灰叶
    board[1][3].chessType = -1;
    board[1][4].chessType = -1;
    // D7,E8设置为青叶
    board[6][3].chessType = 1;
    board[6][4].chessType = 1;
    num_Gray = 2;
    num_Green = 2;
}

chessboard::~chessboard(){

}

bool chessboard::scan_board(int x, int y, int camp, int type) {

    if (x < 0 || y < 0 || x>7 || y>7) return false;
    /*
        camp为落子方的阵营，此时的x，y对应的坐标为被扫描的坐标
        （x,y)所在的chessType标记了该格中的棋子，无子（0），叶（1），枝（2），干（3），正负号表示阵营
        因此camp和chessType的乘积可以同时表示该棋子是否属于己方以及棋子类型
    */

    int t = board[x][y].chessType;
    int r = t * camp;
    bool res;
    if (type == 1 && ( r == 1 || r == 2 || r == 3)) return true;
    else if (type == 2 && r == 2) return true;
    else return false;
}


bool chessboard::step(int x, int y, int chessType) {
    //由于规则，不能将棋子落在己方的根源区域，所以直接返回false
    //只有当chesstype为空时，格子才为空
    if (board[x][y].root * chessType > 0 || board[x][y].chessType != 0)
        return false;
    int camp;
    //camp表示阵营，1为灰方，-1为青方
    if (chessType > 0) camp = 1;
    else camp = -1;
    //顺序扫描以落子点为中心的 5X3 的区域，如果存在友方对应棋子则可以攀附
    int raw[3] = { -1,0,1 };
    int col[5] = { -2,-1,0,1,2 };
    int res = false;
    for (int i : raw) {
        for (int j : col) {
            if (!i && !j ) continue;
            if (j == 2 || j == -2)
                res = scan_board(x + i, y + j,camp, 2);
            else
                res = scan_board(x + i, y + j,camp, 1);
            if (res) break;
        }
        if (res) break;
    }
    if (res) {
        if (chessType < 0)
            num_Gray++;
        else
            num_Green++;
        board[x][y].chessType = chessType;
        movedChess.push(pair<point, char>(point{x, y}, ' '));
        //QString s=QString("成功落下的位置为（%1，%2），棋子为%3").arg(x).arg(y).arg(board[x][y].chessType);
        //QMessageBox::information(NULL,"",s);
        push(x - 1, y, 'w', camp);
        push(x + 1, y, 's', camp);
        push(x, y - 1, 'a', camp);
        push(x, y + 1, 'd', camp);
        return true;
    }
    else return false;

}

void chessboard::push(int x, int y, char dir, int camp) {
    //某个值越界说明了落子在边界上，则对应方向不需要推动
    if (x < 0 || y < 0 || x>7 || y>7)
        return;
    /*
        camp为落子方的阵营，此时的x，y对应的坐标为被推动的坐标
        （x,y)所在的chessType标记了该格中的棋子，无子（0），叶（1），枝（2），干（3），正负号表示阵营
        因此camp和chessType的乘积可以表示该棋子是否属于己方
        由于无子（ 积 = 0）和己方棋子不能被推动（ 积 > 0 )
        所以只有当这个积为负数时，表示该格棋子为敌方棋子，可以被推动
        但是，干（3）在规则上不能被推动，所以，当 积 == -1 或 -2 时，才执行推动操作
        dir表示被推动的方向

    */
    if (board[x][y].chessType * camp == -1 || board[x][y].chessType * camp == -2) {
        //x1,y1用于临时标记扫描位置
        int x1 = x;
        int y1 = y;

        switch (dir)
        {
            case 'w'://上
                //边界棋子无法被推动，因此判断条件为 0 < x1 < 7, 0 < y1 <8
                while (x1 >= 0) {
                    // t 为简化下方判断代码的临时变量，表示扫描位置的chessType
                    int t = board[x1][y1].chessType;

                    //根据规则，地方的干 和 我方棋子 会导致该列都无法推动，同时无法将对方棋子推到其根源区域中
                    if (t * camp == -3 || t * camp > 0 || board[x1][y1].root * camp < 0) break;
                        //只有当扫描至一处空白区域时，该列棋子向全部向空白处移动
                        //因为是单向移动所以不需要交换，复制前一个值即可
                    else if (t * camp == 0) {
                        while (x1 < x) {
                            board[x1][y1].chessType = board[x1 + 1][y1].chessType;
                            movedChess.push(pair<point, char>(point{x1, y1}, 'w'));
                            x1++;
                        }
                        board[x1][y1].chessType = 0;
                        break;
                    }
                    x1--;
                }
                break;

            case 's'://下
                while (x1 <= 7) {
                    int t = board[x1][y1].chessType;
                    if (t * camp == -3 || t * camp > 0 || board[x1][y1].root * camp < 0) break;
                    else if (t * camp == 0) {
                        while (x1 > x) {
                            board[x1][y1].chessType = board[x1 - 1][y1].chessType;
                            movedChess.push(pair<point, char>(point{x1, y1}, 's'));
                            x1--;
                        }
                        board[x1][y1].chessType = 0;
                        break;
                    }
                    x1++;
                }
                break;

            case 'a'://左
                while (y1 >= 0) {
                    int t = board[x1][y1].chessType;
                    if (t * camp == -3 || t * camp > 0 || board[x1][y1].root * camp < 0) break;
                    else if (t * camp == 0) {
                        while (y1 < y) {
                            board[x1][y1].chessType = board[x1][y1 + 1].chessType;
                            movedChess.push(pair<point, char>(point{x1, y1}, 'a'));
                            y1++;
                        }
                        board[x1][y1].chessType = 0;
                        break;
                    }
                    y1--;
                }
                break;

            case 'd'://右
                while (y1 <= 7) {
                    int t = board[x1][y1].chessType;
                    if (t * camp == -3 || t * camp > 0 || board[x1][y1].root * camp < 0) break;
                    else if (t * camp == 0) {
                        while (y1 > y) {
                            board[x1][y1].chessType = board[x1][y1 - 1].chessType;
                            movedChess.push(pair<point, char>(point{x1, y1}, 'd'));
                            y1--;
                        }
                        board[x1][y1].chessType = 0;
                        break;
                    }
                    y1++;
                }
                break;
        }
    }
    else return;
}

void chessboard::offset(int *num_chess) {
    if (movedChess.empty()) return;
    //QMessageBox::information(NULL,"","暂停一下");
    while (!movedChess.empty()) {
        //QMessageBox::information(NULL,"","暂停一下");
        point t = movedChess.top().first;
        //if (board[t.x][t.y].root != 0){
        //movedChess.pop();
        //continue;
        //}
        int start = -1, end = 0;
        for (int i = 0; i < 8; i++) {
            if (board[i][t.y].chessType * board[t.x][t.y].chessType > 0) {
                if (start == -1) start = i;
                else end = i;

            } else {
                if (end - start + 1 >= 3) {
                    for (int j = start; j <= end; j++) offsetChess.push(point{j, t.y});
                }
                start = -1;
                end = 0;
            }
        }
        if (end - start + 1 >= 3) {
            for (int j = start; j <= end; j++) offsetChess.push(point{j, t.y});
        }
        start = -1;
        end = 0;
        for(int i=0 ; i < 8 ;i++){
            if(board[t.x][i].chessType * board[t.x][t.y].chessType > 0){
                if( start == -1 ) start=i;
                else end = i;

            }else {
                if( end-start+1 >= 3) {
                    for (int j = start; j <= end; j++) offsetChess.push(point{t.x,j});
                }
                start = -1;
                end = 0;
            }
        }
        if (end - start + 1 >= 3) {
            for (int j = start; j <= end; j++) offsetChess.push(point{t.x, j});
        }
        movedChess.pop();
    }
    while(!offsetChess.empty()) {
        point t = offsetChess.top();
        //QString s=QString("当前消除的位置是（%1，%2），消除的棋子是%3，剩余的棋子数量是%4").arg(t.x).arg(t.y).arg(board[t.x][t.y].chessType).arg(num_chess[board[t.x][t.y].chessType + 3]);
        //QMessageBox::information(NULL,"",s);
        if (board[t.x][t.y].chessType != 0) num_chess[board[t.x][t.y].chessType + 3]++;
        if (board[t.x][t.y].chessType > 0) num_Green--;
        else if (board[t.x][t.y].chessType < 0) num_Gray--;
        board[t.x][t.y].chessType = 0;

        offsetChess.pop();
    }
}

stack<pair<point, char>> chessboard::get_movedChess() {
    return movedChess;
}

int chessboard::judge() {
    bool end = true;
    if (!num_Green) return -1;
    else if (!num_Gray) return 1;
    for (int i = 2; i < 6; i++) {
        if (board[0][i].chessType == 0) end = false;
    }
    if (end) return 1;
    end = true;
    for (int i = 2; i < 6; i++) {
        if (board[7][i].chessType == 0) end = false;
    }
    if (end) return -1;
    return 0;
}