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

bool RRM::sort_task_start(Task &t1,Task &t2){
    return t1.get_TASK_start() > t2.get_TASK_start();//???????
}

bool RRM::sort_task_end(Task &t1,Task &t2){
    return t1.get_TASK_end() < t2.get_TASK_end();
}

double RRM::RR_M(Task task,vector< vector< Task > > &Task_process, vector< Server > Server)
{
    pricemodel price;
    int num_server = Server.size();
    //cout << "numnumnum" << num_server << endl;
    for(int i = 0; i < num_server; i++)
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
                CPU_used -= Task_process[i][j].get_CPU_request();
                for (int k = j+1; k<Task_process[i].size(); k++) {
                    Task_process[i][k].set_TIME_calculated(Task_process[i][j].get_TASK_end());
                }
            }
        }
        //pop those has finished before the task coming
        Task_process[i].erase(Task_process[i].begin(), Task_process[i].begin() + count);//pop those have finished
        //smaller than 70%
        if (CPU_used + task.get_CPU_request() <= 0.7*Server[i].get_CPU_total() &&
            RAM_used + task.get_RAM_request() < Server[i].get_RAM_total())
        {
            for (int j = 0; j < Task_process[i].size(); i++)
            {
                price_cal += price.calculate_price(Task_process[i][j].get_TIME_calculated(), task.get_TASK_start(), CPU_used/Server[i].get_CPU_total());
            }
            Task_process[i].push_back(task);
            //Task::set_TASK_start(task.get_TIME_start());
            //Task::set_TASK_end(task.get_TIME_end());
            return price_cal;
        }
        //bigger than 70%
        else if(CPU_used+task.get_CPU_request() > 0.7*Server[i].get_CPU_total() &&
                CPU_used+task.get_CPU_request() < Server[i].get_CPU_total() &&
                RAM_used+task.get_RAM_request() < Server[i].get_RAM_total())
        {
            int flag = 0;//used to check whether it can be placed in the queue
            //check special example
            //sort based on task_start
            sort(Task_process[i].begin(), Task_process[i].end(), sort_task_start);
            if(Task_process[i][0].get_TASK_start() < task.get_TIME_start()){
                task.set_TASK_start(Task_process[i][0].get_TASK_start());
                task.set_TASK_end(Task_process[i][0].get_TASK_start() + task.get_TIME_end() - task.get_TASK_start());
                task.set_TIME_calculated(task.get_TASK_start());
            }
            
            //sort based on task_end
            sort(Task_process[i].begin(), Task_process[i].end(), sort_task_end);
            //check
            
            price_cal += price.calculate_price(Task_process[i][0].get_TIME_calculated(), task.get_TIME_start(), CPU_used/Server[i].get_CPU_total());
            for (int j = 0; j < Task_process[i].size(); j++)
            {
                Task_process[i][j].set_TIME_calculated(task.get_TIME_start());
            }
            
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
                        Task_process[i][k].set_TIME_calculated(Task_process[i][j].get_TIME_end());
                    }
                    task.set_TASK_start(Task_process[i][j].get_TASK_end());
                    task.set_TASK_end(Task_process[i][j].get_TASK_end() + task.get_TASK_end() - task.get_TASK_end());
                    task.set_TIME_calculated(task.get_TASK_start());
                    Task_process[i].erase(Task_process[i].begin(), Task_process[i].begin() + j + 1);//pop tasks
                    Task_process[i].push_back(task);
                    flag = 1;
                    return price_cal;
                }
                else
                {
                    price_cal += price.calculate_price(Task_process[i][j].get_TIME_calculated(), Task_process[i][j].get_TASK_end(), temp_CPU/Server[i].get_CPU_total());
                    for (int k = j+1; k<Task_process[i].size(); k++)
                    {
                        Task_process[i][k].set_TIME_calculated(Task_process[i][j].get_TIME_end());
                    }
                }
            }
            /*if (flag==1)
            {
                break;
            }*/
            
        }
    }
    return 0;
}

