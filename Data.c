//
//  Data.c
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/29.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//
#include "Data.h"
Data *_data_create(int c){
    Data *data = (Data*)malloc(sizeof(Data));
    data->c = c;
    return data;
}