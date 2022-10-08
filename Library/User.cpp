/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#include "User.h"
#include<iostream>
using namespace std;

User::User() {
    books = 0;
}

void User::input()
{
    cout << "请输入类别: ";
    cin >> category;

    cout << "请输入id: ";
    cin >> id;
    cout << "请设置密码: ";
    cin >> password;

    cout << "输入姓名: ";
    cin >> name;
}

//void User::show()
//{
//    cout << "ID  :" << id << endl;
//    cout << "姓名:" << name << endl;
//    switch (category)
//    {
//    case 1:
//        cout << "身份: 学生" << endl;
//        cout << "已借书 " << books << " 本" << endl;
//        cout << "还可借书 " << (2 - books) << " 本" << endl;
//        break;
//    case 2:
//        cout << "身份: 教师" << endl;
//        cout << "已借书 " << books << " 本" << endl;
//        cout << "还可借书 " << (5 - books) << " 本" << endl;
//        break;
//    case 3:
//        cout << "身份: 图书管理员" << endl;
//        break;
//    case 4:
//        cout << "身份: 系统管理员" << endl;
//        break;
//    }
//}

User::User(int category, long id, char* password_, char* name_, int books) :category(category), id(id), books(books) {
    password = password_;
    name = name_;
}

void User::save() {
    ofstream file;
    file.open(Userpath, ios::app);
    file << category << ' ' << id << ' ' << password << ' ' << name << ' ' << books << ' ' << endl;
}

void User::showUserMsg()
{
    cout << "      ID: " << name << endl;
    switch (category)
    {
    case 1:
        cout << "      身份: 学生" << endl;
        cout << "      已借书 " << books << " 本" << endl;
        cout << "      还可借书 " << (2 - books) << " 本" << endl;
        break;
    case 2:
        cout << "      身份: 教师" << endl;
        cout << "      已借书 " << books << " 本" << endl;
        cout << "      还可借书 " << (5 - books) << " 本" << endl;
        break;
    case 3:
        cout << "      身份: 图书管理员" << endl;
        break;
    case 4:
        cout << "      身份: 系统管理员" << endl;
        break;
    }
}

