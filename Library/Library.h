/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H

#define Userpath "Userlog.txt"
#define Bookpath "Booklog.txt"
#define Libpath "Liblog.txt"

#include "User.h"
#include "Book.h"
#include "Log.h"
#include <string.h>
#include <vector>

class Library {
private:
    //容量
    User user[100];
    Book books[500];
    Log log[100];

    int n_user, n_book, n_log;    //当前用户数、书数、借阅记录数
    int Stu_limit;
    int Tea_limit;  //最大借书数量
    string path;    //文件地址

public:
    Library();
    //信息初始化
    void UserInit();
    void BookInit();
    void LogInit();

    //登录
    int login(long id, string password);

    //信息删除
    void userdelate();
    void bookdelate();
    void MessageEnd();

    //信息更改
    void userrebuild();
    void bookrebuild();

    //添加信息
    void input_users();        //添加非管理用户
    void input_books();            //添加书籍

    //查找信息

    int find_book(long id);        //通过id查找书籍，返回书籍序号（0~4999）
    int find_user(long id);    //通过id查找用户，返回用户序号（0~999）

    //借还

    void borrow(long userID);        //输入借阅信息
    void back(long userID);                //归还书籍
//show
    void showallbooks();        //打印所有书籍
    void showallborrow(long userID);        //打印所有借阅记录
    void showalluser();            //显示所有用户信息

};

#endif //LIBRARY_LIBRARY_H

