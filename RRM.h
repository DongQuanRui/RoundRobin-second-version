//
//  RRM.hpp
//  EE599project
//
//  Created by zhendong ju on 3/14/19.
//  Copyright © 2019 zhendong ju. All rights reserved.
//
#ifndef RRM_hpp
#define RRM_hpp

#include <iostream>
#include <stdio.h>
#include "Task.h"
#include <vector>
#include "Server.h"

class RRM{
public:
    static bool sort_task_start(Task &t1, Task &t2);

    static bool sort_task_end(Task &t1, Task &t2);
    
    vector<double> RR_M(Task task, vector< vector<Task> > &Task_process, vector< Server > Server, int &i);

    Task cal_end(vector < vector< Task > > &Task_process, int &i);
};



#endif /* RRM_hpp */
