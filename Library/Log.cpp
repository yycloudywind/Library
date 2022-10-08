/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"User.h"    //用到了另外两个类
#include"Book.h"
#include"Log.h"

using namespace std;
void Log::setuser(User _user) { user = _user; }    //设置借阅者
void Log::setbook(Book _book) { book = _book; }        //设置被借书籍

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
    char* c = (char*)str.data();               // 将string转换成char*。
    tm tm_;                                    // 定义tm结构体。
    int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
    sscanf(c, "%d/%d/%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);// 将string存储的日期时间，转换为int临时变量。
    tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
    tm_.tm_mon = month - 1;                        // 月。
    tm_.tm_mday = day;                         // 日。
    tm_.tm_hour = hour;                        // 时。
    tm_.tm_min = minute;                       // 分。
    tm_.tm_sec = second;                       // 秒。
    //tm_.tm_isdst = 0;                          // 非夏令时。
    time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
    return t_;                                 // 返回值。
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
        cout << "@到期时间剩余：" << dif_time / (3600 * 24) << "天"
            << (dif_time % 86400) / 3600 << "小时"
            << ((dif_time % 86400) % 3600) / 60 << "分钟"
            << dif_time % 60 << "秒" << endl;
    }
    else
    {
        dif_time = dif_time - time_limit;
        cout << "@您已超时：" << dif_time / (3600 * 24) << "天"
            << (dif_time % 86400) / 3600 << "小时"
            << ((dif_time % 86400) % 3600) / 60 << "分钟"
            << dif_time % 60 << "秒" << endl;
        cout << "@需缴纳超时罚款 " << ((double)dif_time / 86400.0) * 0.5 << " 元" << endl;
    }
    return;
}

void Log::show() {
    if (user.category >= 3) return;
    cout << "@书籍ID：" << book.id << endl;
    cout << "@书名:" << book.name << endl;
    cout << "@用户姓名:" << user.name << endl;
    cout << "@借出时间:" << timeline << endl;
    showDiffTime(timeline, user.category);
    return;
}

void Log::save() {
    ofstream file;
    file.open(Libpath, ios::app);
    file << user.id << ' ' << book.id << ' ' << timeline << endl;
}
