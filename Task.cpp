//
// Created by Albert Yu on 2019-03-15.
//

#include "Task.h"
Task::Task(){
    TIME_start = 0;
    TIME_end = 0;
    TASK_start = 0;
    CPU_request = 0;
    RAM_request = 0;
    TIME_DDL = 0;
    SERVER_asgn = 0;
    TIME_calculated = 0;
}

double Task::get_TIME_start(){
    return TIME_start;
}


double Task::get_TIME_end(){
    return TIME_end;
}

double Task::get_TASK_start(){
    return TASK_start;
}

double Task::get_TASK_end(){
    return TASK_end;
}

double Task::get_CPU_request(){
    return CPU_request;
}

double Task::get_RAM_request(){
    return RAM_request;
}

double Task::get_TIME_DDL(){
    return TIME_DDL;
}

int Task::get_SERVER_asgn(){
    return SERVER_asgn;
}

double Task::get_TIME_calculated(){
    return TIME_calculated;
}


void Task::set_SERVER_asgn(int n){
    this->SERVER_asgn = n;

}

void Task::set_TASK_start(double n){
    this->TASK_start = n;

}

void Task::set_TASK_end(double n){
    this->TIME_end = n;
}

void Task::set_TIME_calculated(double n){
    this->TIME_calculated = n;
}

void Task::Readfrom(istream & infile){
    char comma;
    int index;
    infile>>index>>comma>>TIME_start>>comma>>TIME_end>>comma>>CPU_request>>comma>>RAM_request;
    TIME_DDL = TIME_end  + (rand()%24);
    TASK_start = TIME_start;
    TASK_end = TIME_end;
    TIME_calculated = TASK_start;
}



//bool Task::sort_task_start(Task t1,Task t2){
//    return t1.get_TASK_start() > t2.get_TASK_start();//???????
//}
//
//bool Task::sort_task_end(Task t1,Task t2){
//    return t1.get_TASK_end() < t2.get_TASK_end();
//}
