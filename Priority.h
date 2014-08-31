//
//  Priority.h
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/29.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//
#ifndef Boolean         /* Boolean が定義されていなかったら */
#define Boolean short
#endif

#ifndef TRUE            /* TRUE が定義されていなかったら */
#define TRUE 1
#endif

#ifndef FALSE           /* FALSE が定義されていなかったら */
#define FALSE 0
#endif
#ifndef __Repair__Priority__
#define __Repair__Priority__

#include <stdio.h>
#include <stdlib.h>

#endif /* defined(__Repair__Priority__) */
#ifndef PRIORITY
#define PRIORITY

typedef struct priority_data{
    u_int left,right;
    u_long index;
    u_int count;
    struct priority_data *next;
    struct priority_data *pre;
    struct priority_queue *parent;
}PData;
typedef struct priority_queue {
    PData *list;
    struct priority_queue *next;
    struct priority_queue *pre;
} Priority;

PData *_pdata_search(int left,int right,PData *data);
PData *_pdata_getLast(PData *data);
PData *_pdata_create(u_int left,u_int right,u_long,Priority *priority);
void _pdata_remove(PData *pdata);
Priority *_priority_get(int count,Priority *priority);
Priority *_priority_getLast(Priority *priority);
void _priority_push(Priority *new_pdata,Priority *source_priority);
Priority *_priority_create(Priority *pre);
Boolean _priority_isEmpty(Priority *priority);
void _pdata_push(PData *new_pdata,PData *source_pdata);
void _priority_forward(PData *pdata,Priority *priority,u_long index);
u_int _priority_getMaxCount(Priority *priority);
Boolean _pdata_backward(PData *pdata, u_long index);
Priority *_priority_getMax(Priority *priority);
void _pdata_disp(PData *pdata);
void _priority_disp(Priority *priority);
#endif