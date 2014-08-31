//
//  Rules.c
//  Repair
//
//  Created by 坂本 時緒 on 2014/09/01.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//
#include "Rules.h"
#include <limits.h>
#define NAN UINT_MAX

void _rule_push(Rule *new_rule,Rule *source_rule){
    if(source_rule->next == NULL){
        source_rule->next = new_rule;
        new_rule->pre = source_rule;
    }else{
        _rule_push(new_rule, source_rule->next);
    }
}
void _rule_disp(Rule *rule){
    printf("%d ====> %d %d ||",rule->parent,rule->left,rule->right);
    if(rule->next != NULL){
        _rule_disp(rule->next);
    }
}
Rule *_rule_create(u_int parent,u_int left,u_int right){
    Rule *rule = (Rule*)malloc(sizeof(Rule));
    rule->parent = parent;
    rule->left = left;
    rule->right = right;
    rule->next = NULL;
    rule->pre = NULL;
    return rule;
}
Rule *_rule_getLast(Rule *rule){
    if(rule->next == NULL){
        return rule;
    }
    return _rule_getLast(rule->next);
}
void _rule_thaw(Rule* rule,u_int *data,u_long len){
    Rule *last_rule = _rule_getLast(rule);
    /*------------前処理あとでいらなくなるかも-----*/
    /*----------------------------------------*/
    _rule_replace(last_rule, data, len);
}
void _rule_replace(Rule *rule,u_int *data,u_long len){
    u_long i=0;
    while(i<len-1){
        if(data[i]==NAN) break;
        if(rule->parent == data[i]){
            data[i] = rule->left;
            _rule_shiftData(i+1, data[i+1],data, len);
            data[i+1] = rule->right;
        }else{
            i++;
        }
    }
    if(rule->pre != NULL)
        _rule_replace(rule->pre, data, len);
}
void _rule_shiftData(u_long index,u_int c,u_int *data,u_long len){
    u_int next_c = data[index+1];
    data[index+1] = c;
    if(next_c != NAN && index+1 != len){
        _rule_shiftData(index+1, next_c,data, len);
    }
}

