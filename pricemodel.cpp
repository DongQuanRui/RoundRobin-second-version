//
//  pricemodel.cpp
//  EE599project
//
//  Created by zhendong ju on 3/14/19.
//  Copyright © 2019 zhendong ju. All rights reserved.
//

#include "pricemodel.h"

//double pricemodel::get_price(int time){
//    return price[time];
//}

double pricemodel::calculate_price(double time_start, double time_end){
    double price[24] = {0.12, 0.156, 0.165, 0.117, 0.194, 0.192, 0.318, 0.266, 0.326, 0.293, 0.388, 0.359, 0.447, 0.478, 0.513, 0.491, 0.457, 0.506, 0.640, 0.544, 0.592, 0.486, 0.499, 0.292};
    double total_price = 0;
    int time_start_24 = int(time_start) % 24;
    int time_end_24 = int(time_end) % 24;
    
    total_price += ((time_start_24 + 1 - time_start) / 1) * price[time_start_24];
    total_price += ((time_end - time_end_24) / 1) * price[time_end_24];
    
    for (int i=int(time_start) + 1; i<=int(time_end); i++) {
        total_price += price[(i%24)];
    }
    
    return total_price;
}


