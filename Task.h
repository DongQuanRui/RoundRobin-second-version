//
// Created by Albert Yu on 2019-03-14.
//
#ifndef LAB_9_TASK_H
#define LAB_9_TASK_H

#include <string>
#include <fstream>
using namespace std;

class Task {
private:
    double TIME_start;
    double TIME_end;
    double TASK_start;
    double TASK_end;
    double CPU_request;
    double RAM_request;
    double TIME_DDL;
    int SERVER_asgn;
    double TIME_calculated;
public:
    double get_TIME_start();
    double get_TIME_end();
    double get_TASK_start();
    double get_TASK_end();
    double get_CPU_request();
    double get_RAM_request();
    double get_TIME_DDL();
    int get_SERVER_asgn();
    double get_TIME_calculated();

    void set_SERVER_asgn(int n);
    void set_TASK_start(double n);
    void set_TASK_end(double n);
    void Readfrom(istream & infile);
    void set_TIME_calculated(double n);
    bool sort_task_start(Task t1,Task t2);
    bool sort_task_end(Task t1,Task t2);
    
    Task();
};



#endif //LAB_9_TASK_H
