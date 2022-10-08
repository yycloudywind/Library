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

    User();  //��ʼ����ÿ��ͬѧ�����������Ϊ0
    User(int category, long id, char* password_, char* name_, int books);

    long getid() { return id; }        //��ȡid
    string getname() { return name; }    //��ȡ����
    int getbooks() { return books; }    //��ȡ�ѽ�������


    //void show(); 
    void showUserMsg();      //��ӡ�û���Ϣ

    void input();        //������Ϣ
    void save();        //������Ϣ
    void borrow() { books += 1; }    //����
    void back() { books -= 1; }    //����

    //��� ѧ���� ���� ���� ������
    int category;  //1->ѧ�� 2->��ʦ 3->����Ա 4->��������Ա
    long id;
    string password;
    string name;
    int books;
};

#endif //LIBRARY_USER_H
