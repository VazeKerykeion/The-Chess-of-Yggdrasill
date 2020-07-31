//
// Created by 10031 on 2020/7/18.
//

#ifndef HELLO_CHESSBOARD_H
#define HELLO_CHESSBOARD_H

struct cell
{
    //棋子类型，1 2 3为三种棋子种类，正负表示阵营,正为灰方，负为青方；
    int chessType;
    //是否为起源区域，0不是，1为灰方起源，-1为青方起源
    int root;
};
class chessboard
{
private:
    //灰方剩余棋子数
    int num_Gray;

    //青方剩余棋子数
    int num_Green;

    //扫描周围是否有可以攀附的棋子,type参数为扫描方式，1为扫描周围的根或叶，2为扫描周围的枝，如果都没有则返回false
    bool scan_board(int x, int y, int camp, int type);

    //落子成功后推动周围棋子
    void push(int x, int y, char dir, int camp);
public:
    cell ** board;
    //棋盘初始化
    chessboard();
    ~chessboard();
    void setup();

    //接受落子，x，y为棋子坐标，chesstype为棋子类型，正负分阵营，范围值为落子是否有效
    bool step(int x, int y, int chessType);

    //判断游戏是否结束，返回值为胜利方，0未未结束
    int judge();
};

#endif //HELLO_CHESSBOARD_H
