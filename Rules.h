//
//  Rules.h
//  Repair
//
//  Created by 坂本 時緒 on 2014/09/01.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//

#ifndef __Repair__Rules__
#define __Repair__Rules__

#include <stdio.h>
#include <stdlib.h>


typedef struct _rule{
    u_int parent,left,right;
    struct _rule *next;
    struct _rule *pre;
}Rule;

void _rule_push(Rule *new_rule,Rule *source_rule);
Rule *_rule_create(u_int parent,u_int left,u_int right);
void _rule_thaw(Rule *rule,u_int *data,u_long len);
void _rule_disp(Rule *rule);
Rule *_rule_getLast(Rule *rule);
void _rule_replace(Rule *rule,u_int *data,u_long len);
void _rule_shiftData(u_long index,u_int c,u_int *data,u_long len);
#endif /* defined(__Repair__Rules__) */