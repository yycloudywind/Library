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
    //����
    User user[100];
    Book books[500];
    Log log[100];

    int n_user, n_book, n_log;    //��ǰ�û��������������ļ�¼��
    int Stu_limit;
    int Tea_limit;  //����������
    string path;    //�ļ���ַ

public:
    Library();
    //��Ϣ��ʼ��
    void UserInit();
    void BookInit();
    void LogInit();

    //��¼
    int login(long id, string password);

    //��Ϣɾ��
    void userdelate();
    void bookdelate();
    void MessageEnd();

    //��Ϣ����
    void userrebuild();
    void bookrebuild();

    //�����Ϣ
    void input_users();        //��ӷǹ����û�
    void input_books();            //����鼮

    //������Ϣ

    int find_book(long id);        //ͨ��id�����鼮�������鼮��ţ�0~4999��
    int find_user(long id);    //ͨ��id�����û��������û���ţ�0~999��

    //�軹

    void borrow(long userID);        //���������Ϣ
    void back(long userID);                //�黹�鼮
//show
    void showallbooks();        //��ӡ�����鼮
    void showallborrow(long userID);        //��ӡ���н��ļ�¼
    void showalluser();            //��ʾ�����û���Ϣ

};

#endif //LIBRARY_LIBRARY_H

