//
// Created by 10031 on 2020/9/24.
//

#include "replay.h"
void replay::insert(int a,int b,int c) {
    LinkNode* p=new LinkNode(a, b, c);
    if(head){
        tail->next = p;
        p->prev=tail;
        tail=tail->next;
    }else{
        head=p;
        tail=head;
    }

}

void replay::save(std::string s) {

}

void replay::load(std::string s) {

}

replay::replay() {
    head = nullptr;
    tail = nullptr;
}
replay::replay(int a, int b, int c) {
    head=new LinkNode(a, b, c);
    tail=head;
}
replay::~replay() {
    tail = nullptr;
    clear(head);
}