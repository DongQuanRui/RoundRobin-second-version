//
//  pricemodel.hpp
//  EE599project
//
//  Created by zhendong ju on 3/14/19.
//  Copyright © 2019 zhendong ju. All rights reserved.
//

#ifndef pricemodel_hpp
#define pricemodel_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class pricemodel{
//    double price[24] = {0.12, 0.156, 0.165, 0.117, 0.194, 0.192, 0.318, 0.266, 0.326, 0.293, 0.388, 0.359, 0.447, 0.478, 0.513, 0.491, 0.457, 0.506, 0.640, 0.544, 0.592, 0.486, 0.499, 0.292};
public:
    double calculate_price(double time_start, double time_end);
    //double get_price(int time); //time is the index of price array
};

#endif /* pricemodel_hpp */
