//
// Created by Albert Yu on 2019-03-14.
//

#ifndef LAB_9_SEVER_H
#define LAB_9_SEVER_H

#include <string>
#include <fstream>
using namespace std;

class Server{
private:
    int ID;
    double CPU_total;
    double RAM_total;
public:
    int get_ID();
    double get_CPU_total();
    double get_RAM_total();
    void Readfrom(istream & infile);
    Server();
};


#endif //LAB_9_SEVER_H
