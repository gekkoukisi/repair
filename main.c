//  main.c
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/29.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"
#include "Repair.h"

#define u_int unsigned int
#define u_long unsigned long

int main(int argc, const char * argv[]) {
    
    
    char *str = "hdjkhfkjhskfhjdkhgljdskhgjklshgjkdshgjkhxzjkghjkshgjkdshgjkhsfdjkghdfjksghjkdfshgjfdkslhg;dfshiof;dsjgiosdfhguiasdhklgfo;dsghufdsihgjkfdlshgio;dhfsuoghjio;fdhgoufdshgdfshgufdhsughdjsfkhgufshdgujfdshgjhdfuogdfsughifdsjhgi;dfsjgfdsjhgifosdjgioegjourehguisfndiuvnsvnidfnshjkslhgusiehfgofhsg;jfdsl;jgiofdhgufdjshgjkfds;hgjdfshgjkfdshnguoidfsuoignfudsingudfisnfdjshndfshgufsdlhgfsdjkhgfdusluhgidfshgudsfnbufdslghuifdshguifdunvfudsgousfhguodsjgov;sfehgnfd;shgoufdsjhdhsfudfhsgfvifofhjskdfhksdhkshgjdhgjkshgjkshk";
    u_long i,len;    Hash hash[7] ,*hash_p;
    
    Priority *priority = _priority_create(NULL);
    len = strlen(str);
    u_int datas[len];
    u_long front[len],back[len];
    _repair_initArray(front,len);
    _repair_initArray(back,len);
    _repair_initHash(hash,7);
    hash_p = hash;
    _repair_inputData(datas,str,len);
    for(i=0;i<len;i++){
        printf("%d ",datas[i]);
    }
    hash_p = hash;
    _repair_read(datas, len, front, back, hash, priority);
    printf("%d   <-------    ",_priority_getMaxCount(priority));
    printf("%c%c   <-------    ",_priority_getLast(priority)->list->left,_priority_getLast(priority)->list->right);
    if(_priority_getLast(priority)->list->next != NULL){
        printf("あるよ");
    }
    _hash_disp(&hash[0]);
    printf("0000000000");
    _hash_disp(&hash[1]);
    printf("0000000000");
    _hash_disp(&hash[2]);
    printf("0000000000");
    _hash_disp(&hash[3]);
    printf("0000000000");
    _hash_disp(&hash[4]);
    printf("0000000000");
    _hash_disp(&hash[5]);
    printf("0000000000");
    _hash_disp(&hash[6]);
    printf("0000000000");
    //getchar();
    Rule *rule;
    rule = _repair_compress(datas, len,front, back, hash, priority);
    _rule_disp(rule);
    _repair_initData(datas,len);
    datas[0] = _rule_getLast(rule)->parent;
    _rule_thaw(rule, datas, len);
    dispData(datas,len);
    
    
    return 0;
}
