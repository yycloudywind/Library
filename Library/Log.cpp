/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"User.h"    //�õ�������������
#include"Book.h"
#include"Log.h"

using namespace std;
void Log::setuser(User _user) { user = _user; }    //���ý�����
void Log::setbook(Book _book) { book = _book; }        //���ñ����鼮

time_t Log::getTime()
{
    time_t rawtime;
    time(&rawtime);
    return rawtime;
}

string Log::time2str(time_t rawtime)
{
    struct tm* ptr_tm_info;
    ptr_tm_info = localtime(&rawtime);
    string timestr =
        to_string(ptr_tm_info->tm_year + 1900) + "/" +
        to_string(ptr_tm_info->tm_mon + 1) + "/" +
        to_string(ptr_tm_info->tm_mday) + "-" +
        to_string(ptr_tm_info->tm_hour / 10) + to_string(ptr_tm_info->tm_hour % 10) + ':' +
        to_string(ptr_tm_info->tm_min / 10) + to_string(ptr_tm_info->tm_min % 10) + ':' +
        to_string(ptr_tm_info->tm_sec / 10) + to_string(ptr_tm_info->tm_sec % 10);
    return timestr;
}

time_t Log::str2time(string str)
{
    char* c = (char*)str.data();               // ��stringת����char*��
    tm tm_;                                    // ����tm�ṹ�塣
    int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
    sscanf(c, "%d/%d/%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
    tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
    tm_.tm_mon = month - 1;                        // �¡�
    tm_.tm_mday = day;                         // �ա�
    tm_.tm_hour = hour;                        // ʱ��
    tm_.tm_min = minute;                       // �֡�
    tm_.tm_sec = second;                       // �롣
    //tm_.tm_isdst = 0;                          // ������ʱ��
    time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
    return t_;                                 // ����ֵ��
}

void Log::showDiffTime(string log_time_str, int cg)
{
    time_t now_time = getTime();
    time_t log_time = str2time(log_time_str);
    time_t dif_time = difftime(now_time, log_time);
    //cout << ctime(&now_time) << endl;
    //cout << ctime(&log_time) << endl;
    //cout << dif_time << endl;
    long long time_limit;
    if (cg == 1) time_limit = 30 * 3600 * 24;
    else time_limit = 180 * 3600 * 24;
    if (time_limit - dif_time >= 0)
    {
        dif_time = time_limit - dif_time;
        cout << "@����ʱ��ʣ�ࣺ" << dif_time / (3600 * 24) << "��"
            << (dif_time % 86400) / 3600 << "Сʱ"
            << ((dif_time % 86400) % 3600) / 60 << "����"
            << dif_time % 60 << "��" << endl;
    }
    else
    {
        dif_time = dif_time - time_limit;
        cout << "@���ѳ�ʱ��" << dif_time / (3600 * 24) << "��"
            << (dif_time % 86400) / 3600 << "Сʱ"
            << ((dif_time % 86400) % 3600) / 60 << "����"
            << dif_time % 60 << "��" << endl;
        cout << "@����ɳ�ʱ���� " << ((double)dif_time / 86400.0) * 0.5 << " Ԫ" << endl;
    }
    return;
}

void Log::show() {
    if (user.category >= 3) return;
    cout << "@�鼮ID��" << book.id << endl;
    cout << "@����:" << book.name << endl;
    cout << "@�û�����:" << user.name << endl;
    cout << "@���ʱ��:" << timeline << endl;
    showDiffTime(timeline, user.category);
    return;
}

void Log::save() {
    ofstream file;
    file.open(Libpath, ios::app);
    file << user.id << ' ' << book.id << ' ' << timeline << endl;
}
