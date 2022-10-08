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
void Library::input_users() {                //���ѧ��
    if (n_user >= 999) {
        cout << "          �Ѵ��û��������" << endl;
        return;
    }
    user[n_user].input();
    user[n_user].save();
    n_user++;
}

void Library::input_books() {                //���ͼ��
    if (n_book >= 4999) {
        cout << "          �Ѵ��鼮�������" << endl;
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
    return -1;       //��δ�ҵ����ظ���
}

int Library::find_user(long id) {
    int i;
    for (i = 0; i < n_user; i++)
        if (user[i].id == id)
            return i;
    return -1;    //ͬ��
}

void Library::borrow(long userID) {
    long id_stu, id_book, ibook, istu;    //����� �û����
    if (n_log >= 999) {
        cout << "          �ﵽ�����־����" << endl;
        return;
    }
    system("cls");
    cout << "-----------------------------" << endl;
    cout << "----------����鼮------------" << endl;
    for (int i = 0; i < n_book; i++)
    {
        books[i].briefShow();
        cout << "-----------------------------" << endl;
    }
    cout << "����������ĵ��鼮��ID: ";
    cin >> id_book;
    ibook = find_book(id_book);
    istu = find_user(userID);
    if (ibook < 0) {                    //δ�ҵ�����-1
        cout << "δ�ҵ�ָ���鼮" << endl;
        return;
    }
    else {
        if (books[ibook].amount <= 0)    //����ʣ��
            return;
        else {
            if (user[istu].category == 1) {
                if (user[istu].getbooks() >= Stu_limit) {
                    cout << "��ѧ�������Ѵ��������" << endl;
                    return;
                }
            }
            else {
                if (user[istu].getbooks() >= Tea_limit) {
                    cout << "�ý�ʦ�����Ѵ��������" << endl;
                    return;
                }
            }

            log[n_log].setuser(user[istu]);
            log[n_log].setbook(books[ibook]);
            log[n_log].timeline = log[n_log].time2str(log[n_log].getTime());
            log[n_log].save();
            books[ibook].borrow();          //�鱾���-1
            user[istu].borrow();            //�û�������+1
            n_log++;                        //���ļ�¼+1

            cout << "--------���ĳɹ�---------" << endl;
            cout << "�鼮��Ϣ:" << endl;
            books[ibook].show();
            cout << "-------------------------" << endl;
        }
    }
}

void Library::back(long userID) {
    system("cls");
    int user_num = find_user(userID);
    cout << "-----------------------------" << endl;
    cout << "--------�û�������Ϣ---------" << endl;
    for (int i = 0; i < n_log; i++)
    {
        if (user[user_num].id == log[i].user.id)
        {
            log[i].show();
            cout << "-----------------------------" << endl;
        }
    }
    int count = 0, bookID, flag;
    cout << "��������ID:";
    cin >> bookID;
    for (int i = 0; i < n_log; i++)
        if (log[i].book.id == bookID) {
            count++;
            break;
        }
    if (count == 0) {
        cout << "--------�޸���Ľ��ļ�¼--------" << endl;
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
        cout << "--------�޸��û����Ĵ����¼--------" << endl;
        return;
    }
    cout << "-----------���ļ�¼---------" << endl;
    cout << "����:" << books[find_book(bookID)].name << endl;
    cout << "�û�����:" << user[user_num].name << endl;

    for (int i = flag + 1; i < n_log; i++)
        log[i - 1] = log[i];

    books[find_book(bookID)].back();
    user[user_num].back();
    n_log--;
    cout << "----------�黹�ɹ�----------" << endl;
}

void Library::showallbooks() {                //չʾ�����鼮��Ϣ
    int i;
    system("cls");
    cout << "---------�����鼮--------" << endl;
    for (i = 0; i < n_book; i++) {
        books[i].show();
        cout << endl;
    }
    cout << "-----------------------" << endl;
}

void Library::showallborrow(long userID) {//չʾ���н��ļ�¼
    system("cls");
    vector<int> userLog;
    string timelines;
    for (int i = 0; i < n_log; i++) {
        if ((userID == log[i].user.id) || (userID == -1))
            userLog.emplace_back(i);
    }
    cout << "-----�û��������,�� " << userLog.size() << " ��-------- " << endl;
    for (int i = 0; i < userLog.size(); i++)
    {
        int ibook = find_book(log[userLog[i]].book.id);
        int iuser = find_user(log[userLog[i]].user.id);
        cout << "@@@�� " << i + 1 << " ��@@@" << endl;
        cout << "@�鼮ID:" << books[ibook].id << endl;
        cout << "@����:" << books[ibook].name << endl;
        if (userID == -1) cout << "@�����ߣ�" << user[iuser].name << endl;
        cout << "@����ʱ�䣺" << log[userLog[i]].timeline << endl;
        log[userLog[i]].showDiffTime(log[userLog[i]].timeline, user[iuser].category);
        cout << "----------------------------" << endl;
    }
}

void Library::showalluser() {                        //��ʾ����ͬѧ��Ϣ
    int i;
    cout << "----------�û�����----------" << endl;
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
        for (int i = 0; file.peek() != EOF; i++)//ѭ����ȡÿһ��
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
        for (int i = 0; file.peek() != EOF; i++)//ѭ����ȡÿһ��
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
        for (int i = 0; file.peek() != EOF; i++)//ѭ����ȡÿһ��
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
    if (iuser < 0) {                    //�û��Ƿ����
        cout << "----------ID������-----------" << endl;
        return -1;
    }
    if (user[iuser].password != password)
        // if (stoi(user[iuser].password) != stoi(password))
    {
        cout << "----------�������-----------" << endl;
        return -1;
    }
    else {
        system("cls");
        cout << "----------��½�ɹ�-----------" << endl;
        cout << "-----------------------------" << endl;
        cout << "||��ӭʹ�ü��ִ�ѧͼ�����ϵͳ||" << endl;
        user[iuser].showUserMsg();
        if (user[iuser].category < 3)
        {
            cout << "-----------------------------" << endl;
            cout << "--------�û�������Ϣ---------" << endl;
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
    cout << "-----������ɾ�����-----" << endl;
    cin >> id;
    int iuser = 0, i;
    iuser = find_user(id);
    i = iuser + 1;
    for (i; i < n_user; i++)
        user[i - 1] = user[i];
    n_user -= 1;
    cout << "-------ɾ���ɹ�----------" << endl;
}

void Library::bookdelate() {
    long id;
    cout << "-----������ɾ�����-----" << endl;
    cin >> id;
    int ibook = 0, i;
    ibook = find_book(id);
    i = ibook + 1;
    for (i; i < n_book; i++)
        books[i - 1] = books[i];    //ֱ�Ӹ�ֵ��ǰһ����ں�һ��
    n_book -= 1;
    cout << "-------ɾ���ɹ�-------" << endl;
}

void Library::userrebuild() {
    userdelate();
    input_users();
}

void Library::bookrebuild() {
    bookdelate();
    input_books();
}