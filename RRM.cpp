//
//  RRM.cpp
//  EE599project
//
//  Created by zhendong ju on 3/14/19.
//  Copyright © 2019 zhendong ju. All rights reserved.
//
#include "RRM.h"
#include <iostream>
#include <vector>
#include "Server.h"
#include "Task.h"
#include "pricemodel.h"

using namespace std;

//sort according start time of task decreasingly
bool RRM::sort_task_start(Task &t1,Task &t2){
    return t1.get_TASK_start() > t2.get_TASK_start();
}

//sort according end time of task increasingly
bool RRM::sort_task_end(Task &t1,Task &t2){
    return t1.get_TASK_end() < t2.get_TASK_end();
}

//This part is used to check the virtual end time of task after placing them in th queue
Task RRM::cal_end(vector < vector< Task > > &Task_process, int &i)
{
        Task task_virtual;
        sort(Task_process[i].begin(), Task_process[i].end(), sort_task_end);
        if(Task_process[i].size() > 0)
        {
            double TIME_finish = Task_process[i][Task_process[i].size() - 1].get_TASK_end();
            task_virtual.set_TASK_start(TIME_finish);
            task_virtual.set_TASK_end(TIME_finish);
        }
    return task_virtual;
}

//RRM
vector<double> RRM::RR_M(Task task,vector< vector< Task > > &Task_process, vector< Server > Server, int &i)
{
    vector<double> this_task(2);
    //double this_task[2];
    pricemodel price;
    int num_server = Server.size();
    int count_step = 0;
    while(count_step < num_server)
    {
        double price_cal = 0;
        double CPU_used = 0;
        double RAM_used = 0;
        for (int j = 0; j < Task_process[i].size(); j++)
        {
            CPU_used += Task_process[i][j].get_CPU_request();
            RAM_used += Task_process[i][j].get_RAM_request();
        }
        //sort based on task_end time
        sort(Task_process[i].begin(), Task_process[i].end(), sort_task_end);
        int count = 0;
        for (int j = 0; j < Task_process[i].size(); j++)
        {
            if(Task_process[i][j].get_TASK_end() <= task.get_TIME_start())
            {
                count++;
                price_cal += price.calculate_price(Task_process[i][j].get_TIME_calculated(), Task_process[i][j].get_TASK_end(),CPU_used/Server[i].get_CPU_total());
                for(int k=j+1;k<Task_process[i].size();k++){
                    Task_process[i][k].set_TIME_calculated(Task_process[i][j].get_TASK_end());
                }
                CPU_used -= Task_process[i][j].get_CPU_request();
            }
        }
        //pop those has finished before the task coming
        Task_process[i].erase(Task_process[i].begin(), Task_process[i].begin() + count);//pop those have finished
        //eliminate corner case
        sort(Task_process[i].begin(), Task_process[i].end(), sort_task_start);
        if(Task_process[i].size()>0) {
            if (Task_process[i][0].get_TASK_start() > task.get_TIME_start())
            {
                task.set_TASK_start(Task_process[i][0].get_TASK_start());
                task.set_TASK_end(Task_process[i][0].get_TASK_start() + task.get_TIME_end() - task.get_TASK_start());
                task.set_TIME_calculated(task.get_TASK_start());
            }
        }
        //condition that smaller than 70% corresponding to case 1
        if (CPU_used + task.get_CPU_request() <= 0.7*Server[i].get_CPU_total() &&
            RAM_used + task.get_RAM_request() < Server[i].get_RAM_total())
        {
            if(Task_process[i].size()>0) {
                price_cal += price.calculate_price(Task_process[i][0].get_TIME_calculated(), task.get_TASK_start(),CPU_used / Server[i].get_CPU_total());
            }
            Task_process[i].push_back(task);
            for(int j=0;j<Task_process[i].size();j++){
                Task_process[i][j].set_TIME_calculated(task.get_TASK_start());
            }
            i++;
            i%=num_server;
            
            this_task[0] = price_cal;
            this_task[1] = 1;
            
            return this_task;
            //return price_cal;
        }
        //bigger than 70% corresponding to case 2
        else if(CPU_used+task.get_CPU_request() > 0.7*Server[i].get_CPU_total() &&
                CPU_used+task.get_CPU_request() < Server[i].get_CPU_total() &&
                RAM_used+task.get_RAM_request() < Server[i].get_RAM_total())
        {
            sort(Task_process[i].begin(), Task_process[i].end(), sort_task_end);
            price_cal += price.calculate_price(Task_process[i][0].get_TIME_calculated(), task.get_TASK_start(), CPU_used/Server[i].get_CPU_total());
            for (int j = 0; j < Task_process[i].size(); j++)
            {
                Task_process[i][j].set_TIME_calculated(task.get_TASK_start());
            }
            sort(Task_process[i].begin(), Task_process[i].end(), sort_task_end);

            for (int j = 0; j < Task_process[i].size(); j++)
            {
                double temp_end = Task_process[i][j].get_TASK_end() + task.get_TIME_end() - task.get_TIME_start();
                double temp_CPU = 0, temp_RAM = 0;

                for (int k = j+1; k < Task_process[i].size(); k++)
                {
                    temp_CPU += Task_process[i][k].get_CPU_request();
                    temp_RAM += Task_process[i][k].get_RAM_request();
                }
                temp_CPU += task.get_CPU_request();
                temp_RAM += task.get_RAM_request();
                //check in which queue should be placed
                if(temp_end <= task.get_TIME_DDL() && temp_CPU <= 0.7*Server[i].get_CPU_total() && temp_RAM < Server[i].get_RAM_total())
                {
                    price_cal += price.calculate_price(Task_process[i][j].get_TIME_calculated(), Task_process[i][j].get_TASK_end(), temp_CPU/Server[i].get_CPU_total());
                    for (int k = j+1; k<Task_process[i].size(); k++)
                    {
                        Task_process[i][k].set_TIME_calculated(Task_process[i][j].get_TASK_end());
                    }
                    task.set_TASK_start(Task_process[i][j].get_TASK_end());
                    task.set_TASK_end(Task_process[i][j].get_TASK_end() + task.get_TASK_end() - task.get_TASK_end());
                    task.set_TIME_calculated(task.get_TASK_start());
                    Task_process[i].erase(Task_process[i].begin(), Task_process[i].begin() + j + 1);//pop tasks
                    Task_process[i].push_back(task);
                    i++;
                    i%=num_server;
                    
                    this_task[0] = price_cal;
                    this_task[1] = 1;
                    
                    return this_task;
                    //return price_cal;
                }
                //finally find that it is not suitable to place the task in th queue
                else
                {
                    price_cal += price.calculate_price(Task_process[i][j].get_TIME_calculated(), Task_process[i][j].get_TASK_end(), (temp_CPU-task.get_CPU_request())/Server[i].get_CPU_total());
                    for (int k = j+1; k<Task_process[i].size(); k++)
                    {
                        Task_process[i][k].set_TIME_calculated(Task_process[i][j].get_TASK_end());
                    }
                    
                }
            }
        }
        else{
            this_task[0] = 0;
            this_task[1] = 2;
            return this_task;
        }
        //move to next server
        count_step++;
        i++;
        i%=num_server;
    }
    this_task[0] = 0;
    this_task[1] = 0;
    
    return this_task;
    //return 0;
}

