/*
@Author: yycloudywind
@Date: 2022.9.3
*/
#define Libpath "Liblog.txt"

#include<ctime>
#include<string>

#ifndef LIBRARY_BORROW_H
#define LIBRARY_BORROW_H

class Log {
public:
    User user;
    Book book;
    string timeline;

    //设置借阅者
    void setuser(User stu);    
    //设置被借书籍
    void setbook(Book book);        

    //获取系统时间
    time_t getTime();   
    //time_t转string
    string time2str(time_t rawtime);    
    //string转time_t
    time_t str2time(string str);    
    //显示借书剩余时间
    void showDiffTime(string log_time, int cg);
    void show();
    void save();
};
#endif //LIBRARY_BORROW_H
