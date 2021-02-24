//
// Created by 10031 on 2020/9/24.
//

#ifndef CHESS_REPLAY_H
#define CHESS_REPLAY_H
#include <string>
struct LinkNode{
    int x;
    int y;
    int chessType;
    int board[8][8]{};
    LinkNode* next;
    LinkNode* prev;
    LinkNode(int a, int b, int c){
        x=a;
        y=b;
        chessType=c;
        prev = nullptr;
        next = nullptr;
    };
};

class replay {
public:
    void insert(int a,int b,int c);
    void save(std::string s);
    void load(std::string s);

    replay();
    ~replay();
    replay(int a,int b,int c);

private:
    void clear(LinkNode* t){
        if(!t) return;
        clear(t->next);
        delete t;
    }
    LinkNode* head;
    LinkNode* tail;
};


#endif //CHESS_REPLAY_H
