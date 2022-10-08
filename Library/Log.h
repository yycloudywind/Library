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

    //���ý�����
    void setuser(User stu);    
    //���ñ����鼮
    void setbook(Book book);        

    //��ȡϵͳʱ��
    time_t getTime();   
    //time_tתstring
    string time2str(time_t rawtime);    
    //stringתtime_t
    time_t str2time(string str);    
    //��ʾ����ʣ��ʱ��
    void showDiffTime(string log_time, int cg);
    void show();
    void save();
};
#endif //LIBRARY_BORROW_H
