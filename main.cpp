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
    //cout << servers[0].get_CPU_total() << endl;
    
    infile.open("task.csv");
    getline(infile,title);
    while(!infile.eof()){
        Task task;
        task.Readfrom(infile);
        //cout << task.get_CPU_request() << endl;
        RRM M;
        total_price += M.RR_M(task, Task_process, servers,i);
    }

    for(int i=0;i<num_server;i++){
        RRM M;
        Task task=M.cal_end(Task_process,i);
        total_price += M.RR_M(task,Task_process,servers,i);
    }

    cout<<"Total cost: "<<total_price<<endl;

    infile.close();



    return 0;
}
