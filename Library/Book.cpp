/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#include"Book.h"

using namespace std;
void Book::show() {
    cout << "id:" << id << endl;
    cout << "����:" << name << endl;
    cout << "����:" << author << endl;
    cout << "������:" << publication << endl;
    cout << "��ʣ�� " << amount << " ���ɽ�." << endl;
}

void Book::briefShow()
{
    cout << setiosflags(ios::left);
    cout << "id:" << id << " ";
    cout << "����:" << setw(30) << name << " ";
    cout << "����:" << setw(20) << author << " ";
    cout << "������:" << setw(20) << publication << " ";
    cout << "��ʣ�� " << amount << " ���ɽ�." << endl;
}

void Book::input() {
    cout << "������id: ";
    cin >> id;
    cout << "����������: ";
    cin >> name;
    cout << "����������: ";
    cin >> author;
    cout << "���������: ";
    cin >> publication;
    cout << "������Ŀ: ";
    cin >> amount;
}

void Book::save() {
    ofstream file;
    file.open(Bookpath, ios::app);
    file << id << ' ' << name << ' ' << author << ' ' << publication << ' ' << amount << endl;
}


