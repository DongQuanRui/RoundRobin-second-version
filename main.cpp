//
//  main.cpp
//  EE599project
//
//  Created by zhendong ju on 2/27/19.
//  Copyright © 2019 zhendong ju. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Task.h"
#include "Server.h"
#include "RRM.h"

using namespace std;

int main() {
    int i=0;
    string title;
    double total_price = 0;
    vector<vector <Task> > Task_process;
    vector<Task>::iterator T;
    vector<Server> servers;
    vector<Server>::iterator S;
    ifstream infile;
    infile.open("server.csv");
    getline(infile,title);
    //loading server information
    while(!infile.eof()){
        Server server;
        server.Readfrom(infile);
        servers.push_back(server);
    }
    int num_server = servers.size();
    for (int i=0; i<num_server; i++) {
        Task_process.push_back(vector<Task>());
    }
    infile.close();
    infile.open("task.csv");
    getline(infile,title);
    //loading data and do RRM
    vector<double> this_task(2);
    while(!infile.eof()){
        vector<Task> task;
        int line=0;
        while(!infile.eof()){
            Task temp_task;
            temp_task.Readfrom(infile);
            task.push_back(temp_task);
            line++;
            if (line == 10000) {
                break;
            }
        }
        //Task task;
        //task.Readfrom(infile);
        
        RRM M;
        //vector<double, double> this_task;
        while (task.size()!=0) {
            Task trans;
            trans = task.front();
            task.erase(task.begin());
            this_task = M.RR_M(trans, Task_process, servers,i);
            total_price += this_task[0];
            if(this_task[1]==0){
                task.push_back(trans);
                //this_task.clear();
            }else if(this_task[1]==2){
                continue;
            }
        }
        //total_price += M.RR_M(task, Task_process, servers,i);
    }
    for(int i=0;i<num_server;i++){
        RRM M;
        Task task=M.cal_end(Task_process,i);
        vector<double> this_task(2);
        this_task = M.RR_M(task,Task_process,servers,i);
        total_price += this_task[0];
        //total_price += M.RR_M(task,Task_process,servers,i);
    }
    cout<<"Total cost: "<<total_price<<endl;
    infile.close();
    return 0;
}
