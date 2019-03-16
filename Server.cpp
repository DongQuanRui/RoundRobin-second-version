//
// Created by Albert Yu on 2019-03-15.
//

#include "Server.h"
Server::Server(){
    ID = 0;
    CPU_total = 0;
    RAM_total = 0;
}

int Server::get_ID(){
    return ID;
}

double Server::get_CPU_total(){
    return CPU_total;
}

double Server::get_RAM_total(){
    return RAM_total;
}

void Server::Readfrom(istream & infile){
    char comma;
    infile>>ID>>comma>>CPU_total>>comma>>RAM_total;
}

