/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#include<iostream>
#include<string>

#include"Library.h"

using namespace std;

long id_input;
string password_input;

void print_login() {
    cout << "----------ͼ�����ϵͳ----------" << endl;
    cout << "     ������ID: ";
    cin >> id_input;
    cout << "     ����������: ";
    cin >> password_input;
}

void print_usermenu() {
    cout << "----------ͼ�����ϵͳ----------" << endl;
    cout << "          1.�����鼮" << endl;
    cout << "          2.�黹�鼮" << endl;
    cout << "          3.��ʾ������" << endl;
    cout << "          4.��ʾ�������" << endl;
    cout << "          0.�˳�" << endl;
    cout << "-----------------------------" << endl;
}

void print_administer() {
    cout << "----------ͼ�����ϵͳ----------" << endl;
    cout << "          1.�û�ע��" << endl;
    cout << "          2.�û�ɾ��" << endl;
    cout << "          3.�û��б�" << endl;
    cout << "          4.�û���Ϣ�޸�" << endl;
    cout << "          0.�˳�" << endl;
    cout << "-----------------------------" << endl;
}

void print_libmanager() {
    cout << "----------ͼ�����ϵͳ----------" << endl;
    cout << "          1.¼���鼮" << endl;
    cout << "          2.ɾ���鼮" << endl;
    cout << "          3.�޸��鼮" << endl;
    cout << "          4.��ʾ������" << endl;
    cout << "          5.��ʾ�������" << endl;
    cout << "          0.�˳�" << endl;
    cout << "-----------------------------" << endl;
}

int getcommond() {
    string num;
    cout << "        ������ָ��:";
    cin >> num;
    if (num >= "0" && num <= "9")
    {
        return stoi(num);
    }
    else
    {
        return 100;
    }
}

int main() {
    Library lib;
    int command = 1;
    int condition = 1;

    while (condition > -2 && condition < 5) {
        print_login();
        condition = lib.login(id_input, password_input);
        system("pause");
        system("cls");
        switch (condition) {
        case 1:
        case 2:
            while (command != 0) {
                system("cls");
                print_usermenu();
                command = getcommond();
                switch (command) {
                case 1:
                    lib.borrow(id_input);
                    system("pause");
                    continue;
                case 2:
                    lib.back(id_input);
                    system("pause");
                    continue;
                case 3:
                    lib.showallbooks();
                    system("pause");
                    continue;
                case 4:
                    lib.showallborrow(id_input);
                    system("pause");
                    continue;
                case 0:
                    lib.MessageEnd();
                    break;
                }
            }
            break;
        case 3:
            while (command != 0) {
                system("cls");
                print_libmanager();
                command = getcommond();
                switch (command) {
                case 1:
                    lib.input_books();
                    system("pause");
                    continue;
                case 2:
                    lib.bookdelate();
                    system("pause");
                    continue;
                case 3:
                    lib.bookrebuild();
                    system("pause");
                    continue;
                case 4:
                    lib.showallbooks();
                    system("pause");
                    continue;
                case 5:
                    lib.showallborrow(-1);
                    system("pause");
                    continue;
                case 0:
                    lib.MessageEnd();
                    break;
                }
                break;
            }

        case 4:
            while (command != 0) {
                system("cls");
                print_administer();
                command = getcommond();
                switch (command) {
                case 1:
                    lib.input_users();
                    system("pause");
                    continue;
                case 2:
                    lib.userdelate();
                    system("pause");
                    continue;
                case 3:
                    lib.showalluser();
                    system("pause");
                    continue;
                case 4:
                    lib.userrebuild();
                    system("pause");
                    continue;
                case 0:
                    lib.MessageEnd();
                    break;
                }
                break;
            }
        default:
            break;
        }
        condition = 1;
        command = 1;
        lib.LogInit();
        lib.BookInit();
        lib.LogInit();
        system("cls");
    }
    return 0;
}
