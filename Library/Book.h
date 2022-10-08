/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#define Bookpath "Booklog.txt"

#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include<iostream>
#include<string>
#include <fstream>
#include <iomanip>

using namespace std;

class Book {
public:
    void input();
    void save();
    void show();            //��ʾ������Ϣ
    void briefShow();

    //�軹
    void borrow() { amount -= 1; }
    void back() { amount += 1; }

    //id ���� ������ ���� ����
    long id;
    int amount;
    string publication;
    string author;
    string name;
};

#endif //LIBRARY_BOOK_H
