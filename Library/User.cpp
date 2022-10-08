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
    cout << "���������: ";
    cin >> category;

    cout << "������id: ";
    cin >> id;
    cout << "����������: ";
    cin >> password;

    cout << "��������: ";
    cin >> name;
}

//void User::show()
//{
//    cout << "ID  :" << id << endl;
//    cout << "����:" << name << endl;
//    switch (category)
//    {
//    case 1:
//        cout << "���: ѧ��" << endl;
//        cout << "�ѽ��� " << books << " ��" << endl;
//        cout << "���ɽ��� " << (2 - books) << " ��" << endl;
//        break;
//    case 2:
//        cout << "���: ��ʦ" << endl;
//        cout << "�ѽ��� " << books << " ��" << endl;
//        cout << "���ɽ��� " << (5 - books) << " ��" << endl;
//        break;
//    case 3:
//        cout << "���: ͼ�����Ա" << endl;
//        break;
//    case 4:
//        cout << "���: ϵͳ����Ա" << endl;
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
        cout << "      ���: ѧ��" << endl;
        cout << "      �ѽ��� " << books << " ��" << endl;
        cout << "      ���ɽ��� " << (2 - books) << " ��" << endl;
        break;
    case 2:
        cout << "      ���: ��ʦ" << endl;
        cout << "      �ѽ��� " << books << " ��" << endl;
        cout << "      ���ɽ��� " << (5 - books) << " ��" << endl;
        break;
    case 3:
        cout << "      ���: ͼ�����Ա" << endl;
        break;
    case 4:
        cout << "      ���: ϵͳ����Ա" << endl;
        break;
    }
}

