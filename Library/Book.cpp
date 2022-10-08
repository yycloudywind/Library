/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#include"Book.h"

using namespace std;
void Book::show() {
    cout << "id:" << id << endl;
    cout << "书名:" << name << endl;
    cout << "作者:" << author << endl;
    cout << "出版社:" << publication << endl;
    cout << "现剩余 " << amount << " 本可借." << endl;
}

void Book::briefShow()
{
    cout << setiosflags(ios::left);
    cout << "id:" << id << " ";
    cout << "书名:" << setw(30) << name << " ";
    cout << "作者:" << setw(20) << author << " ";
    cout << "出版社:" << setw(20) << publication << " ";
    cout << "现剩余 " << amount << " 本可借." << endl;
}

void Book::input() {
    cout << "请输入id: ";
    cin >> id;
    cout << "请输入书名: ";
    cin >> name;
    cout << "请输入作者: ";
    cin >> author;
    cout << "输入出版社: ";
    cin >> publication;
    cout << "输入数目: ";
    cin >> amount;
}

void Book::save() {
    ofstream file;
    file.open(Bookpath, ios::app);
    file << id << ' ' << name << ' ' << author << ' ' << publication << ' ' << amount << endl;
}


