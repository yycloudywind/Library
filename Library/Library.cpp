/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#include<iostream>
#include<string>
#include "Library.h"
#include"User.h"
#include"Book.h"
#include"Log.h"

using namespace std;
void Library::input_users() {                //添加学生
    if (n_user >= 999) {
        cout << "          已达用户最大容量" << endl;
        return;
    }
    user[n_user].input();
    user[n_user].save();
    n_user++;
}

void Library::input_books() {                //添加图书
    if (n_book >= 4999) {
        cout << "          已达书籍最大容量" << endl;
        return;
    }
    books[n_book].input();
    books[n_book].save();
    n_book++;
}

int Library::find_book(long id) {
    int i;
    for (i = 0; i < n_book; i++)
        if (books[i].id == id)
            return i;
    return -1;       //若未找到返回负数
}

int Library::find_user(long id) {
    int i;
    for (i = 0; i < n_user; i++)
        if (user[i].id == id)
            return i;
    return -1;    //同上
}

void Library::borrow(long userID) {
    long id_stu, id_book, ibook, istu;    //书序号 用户序号
    if (n_log >= 999) {
        cout << "          达到最大日志容量" << endl;
        return;
    }
    system("cls");
    cout << "-----------------------------" << endl;
    cout << "----------库存书籍------------" << endl;
    for (int i = 0; i < n_book; i++)
    {
        books[i].briefShow();
        cout << "-----------------------------" << endl;
    }
    cout << "请输入想借阅的书籍的ID: ";
    cin >> id_book;
    ibook = find_book(id_book);
    istu = find_user(userID);
    if (ibook < 0) {                    //未找到返回-1
        cout << "未找到指定书籍" << endl;
        return;
    }
    else {
        if (books[ibook].amount <= 0)    //书有剩余
            return;
        else {
            if (user[istu].category == 1) {
                if (user[istu].getbooks() >= Stu_limit) {
                    cout << "该学生借书已达最大数量" << endl;
                    return;
                }
            }
            else {
                if (user[istu].getbooks() >= Tea_limit) {
                    cout << "该教师借书已达最大数量" << endl;
                    return;
                }
            }

            log[n_log].setuser(user[istu]);
            log[n_log].setbook(books[ibook]);
            log[n_log].timeline = log[n_log].time2str(log[n_log].getTime());
            log[n_log].save();
            books[ibook].borrow();          //书本库存-1
            user[istu].borrow();            //用户借阅量+1
            n_log++;                        //借阅记录+1

            cout << "--------借阅成功---------" << endl;
            cout << "书籍信息:" << endl;
            books[ibook].show();
            cout << "-------------------------" << endl;
        }
    }
}

void Library::back(long userID) {
    system("cls");
    int user_num = find_user(userID);
    cout << "-----------------------------" << endl;
    cout << "--------用户借阅信息---------" << endl;
    for (int i = 0; i < n_log; i++)
    {
        if (user[user_num].id == log[i].user.id)
        {
            log[i].show();
            cout << "-----------------------------" << endl;
        }
    }
    int count = 0, bookID, flag;
    cout << "请输入书ID:";
    cin >> bookID;
    for (int i = 0; i < n_log; i++)
        if (log[i].book.id == bookID) {
            count++;
            break;
        }
    if (count == 0) {
        cout << "--------无该书的借阅记录--------" << endl;
        return;
    }
    count = 0;
    for (int i = 0; i < n_log; i++)
        if (log[i].book.id == bookID && log[i].user.id == userID) {
            count++;
            flag = i;
            break;
        }
    if (count == 0) {
        cout << "--------无该用户借阅此书记录--------" << endl;
        return;
    }
    cout << "-----------借阅记录---------" << endl;
    cout << "书名:" << books[find_book(bookID)].name << endl;
    cout << "用户姓名:" << user[user_num].name << endl;

    for (int i = flag + 1; i < n_log; i++)
        log[i - 1] = log[i];

    books[find_book(bookID)].back();
    user[user_num].back();
    n_log--;
    cout << "----------归还成功----------" << endl;
}

void Library::showallbooks() {                //展示所有书籍信息
    int i;
    system("cls");
    cout << "---------所有书籍--------" << endl;
    for (i = 0; i < n_book; i++) {
        books[i].show();
        cout << endl;
    }
    cout << "-----------------------" << endl;
}

void Library::showallborrow(long userID) {//展示所有借阅记录
    system("cls");
    vector<int> userLog;
    string timelines;
    for (int i = 0; i < n_log; i++) {
        if ((userID == log[i].user.id) || (userID == -1))
            userLog.emplace_back(i);
    }
    cout << "-----用户借书情况,共 " << userLog.size() << " 条-------- " << endl;
    for (int i = 0; i < userLog.size(); i++)
    {
        int ibook = find_book(log[userLog[i]].book.id);
        int iuser = find_user(log[userLog[i]].user.id);
        cout << "@@@第 " << i + 1 << " 条@@@" << endl;
        cout << "@书籍ID:" << books[ibook].id << endl;
        cout << "@书名:" << books[ibook].name << endl;
        if (userID == -1) cout << "@借阅者：" << user[iuser].name << endl;
        cout << "@借阅时间：" << log[userLog[i]].timeline << endl;
        log[userLog[i]].showDiffTime(log[userLog[i]].timeline, user[iuser].category);
        cout << "----------------------------" << endl;
    }
}

void Library::showalluser() {                        //显示所有同学信息
    int i;
    cout << "----------用户名单----------" << endl;
    for (i = 0; i < n_user; i++) {
        user[i].showUserMsg();
        cout << endl;
    }
}

void Library::UserInit() {
    path = Userpath;
    ifstream file;;
    file.open(this->path.c_str());
    if (file.is_open())
    {
        for (int i = 0; file.peek() != EOF; i++)//循环读取每一行
        {
            file >> user[i].category >> user[i].id >> user[i].password >> user[i].name >> user[i].books;
            n_user = i + 1;
            //cout << "userID: " << user[i].category << endl;
            //cout << "userNum: " << n_user << endl;
        }
    }
    else {
        cout << "User Init Error" << endl;
    }
}

void Library::BookInit() {
    path = Bookpath;
    ifstream file;;
    file.open(this->path.c_str());
    if (file.is_open())
    {
        for (int i = 0; file.peek() != EOF; i++)//循环读取每一行
        {
            file >> books[i].id >> books[i].name >> books[i].author >> books[i].publication >> books[i].amount;
            n_book = i + 1;
        }
    }
    else {
        cout << "Book Init Error" << endl;
    }
}

void Library::LogInit() {
    path = Libpath;
    ifstream file;;
    file.open(this->path.c_str());
    if (file.is_open())
    {
        int user_id, book_id;
        for (int i = 0; file.peek() != EOF; i++)//循环读取每一行
        {
            file >> user_id >> book_id >> log[i].timeline;
            log[i].setuser(user[find_user(user_id)]);
            log[i].setbook(books[find_book(book_id)]);
            n_log = i + 1;
        }
    }
    else {
        cout << "Log Init Error" << endl;
    }
}

Library::Library() {
    UserInit();
    BookInit();
    LogInit();
    Stu_limit = 2;
    Tea_limit = 5;
}

void Library::MessageEnd() {
    ofstream f1;
    f1.open(Bookpath, ios::ate);
    if (f1.is_open()) {
        for (int i = 0; i < n_book; ++i) {
            f1 << books[i].id << ' ' << books[i].name << ' ' << books[i].author << ' ' << books[i].publication << ' '
                << books[i].amount;
            if (i != n_book - 1)  f1 << endl;
        }
        cout << "Succed to save book" << endl;
        f1.close();
    }
    else cout << "Error to save" << endl;
    ofstream f2;
    f2.open(Userpath, ios::ate);
    if (f2.is_open()) {
        for (int i = 0; i < n_user; ++i) {
            f2 << user[i].category << ' ' << user[i].id << ' ' << user[i].password << ' ' << user[i].name << ' '
                << user[i].books;
            if (i != n_user - 1)  f2 << endl;
        }
        cout << "Succed to save user" << endl;
        f2.close();
    }
    else cout << "Error to save" << endl;
    ofstream f3;
    f3.open(Libpath, ios::ate);
    if (f3.is_open()) {
        for (int i = 0; i < n_log; ++i) {
            f3 << log[i].user.id << ' ' << log[i].book.id << ' ' << log[i].timeline;
            if (i != n_log - 1)  f3 << endl;
        }
        cout << "Succed to save log" << endl;
        f3.close();
    }
    else cout << "Error to save" << endl;
}

int Library::login(long id, string password) {
    int iuser;
    iuser = find_user(id);
    if (iuser < 0) {                    //用户是否存在
        cout << "----------ID不存在-----------" << endl;
        return -1;
    }
    if (user[iuser].password != password)
        // if (stoi(user[iuser].password) != stoi(password))
    {
        cout << "----------密码错误-----------" << endl;
        return -1;
    }
    else {
        system("cls");
        cout << "----------登陆成功-----------" << endl;
        cout << "-----------------------------" << endl;
        cout << "||欢迎使用吉林大学图书管理系统||" << endl;
        user[iuser].showUserMsg();
        if (user[iuser].category < 3)
        {
            cout << "-----------------------------" << endl;
            cout << "--------用户借阅信息---------" << endl;
            for (int i = 0; i < n_log; i++)
            {
                if (user[iuser].id == log[i].user.id)
                {
                    log[i].show();
                    cout << "-----------------------------" << endl;
                }
            }
        }
        return user[iuser].category;
    }
}

void Library::userdelate() {
    long id;
    cout << "-----请输入删除编号-----" << endl;
    cin >> id;
    int iuser = 0, i;
    iuser = find_user(id);
    i = iuser + 1;
    for (i; i < n_user; i++)
        user[i - 1] = user[i];
    n_user -= 1;
    cout << "-------删除成功----------" << endl;
}

void Library::bookdelate() {
    long id;
    cout << "-----请输入删除编号-----" << endl;
    cin >> id;
    int ibook = 0, i;
    ibook = find_book(id);
    i = ibook + 1;
    for (i; i < n_book; i++)
        books[i - 1] = books[i];    //直接赋值，前一项等于后一项
    n_book -= 1;
    cout << "-------删除成功-------" << endl;
}

void Library::userrebuild() {
    userdelate();
    input_users();
}

void Library::bookrebuild() {
    bookdelate();
    input_books();
}