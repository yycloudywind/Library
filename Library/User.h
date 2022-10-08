/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#include "string"
#include <fstream>

#define Userpath "Userlog.txt"

using namespace std;
#ifndef LIBRARY_USER_H
#define LIBRARY_USER_H

class User {
public:

    User();  //初始化，每名同学最初借书量均为0
    User(int category, long id, char* password_, char* name_, int books);

    long getid() { return id; }        //获取id
    string getname() { return name; }    //获取姓名
    int getbooks() { return books; }    //获取已借书数量


    //void show(); 
    void showUserMsg();      //打印用户信息

    void input();        //键入信息
    void save();        //保存信息
    void borrow() { books += 1; }    //借书
    void back() { books -= 1; }    //还书

    //类别 学工号 密码 名字 借书数
    int category;  //1->学生 2->老师 3->管理员 4->超级管理员
    long id;
    string password;
    string name;
    int books;
};

#endif //LIBRARY_USER_H
