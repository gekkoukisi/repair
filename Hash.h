//
//  Hash.h
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

#ifndef __Repair__Hash__
#define __Repair__Hash__

#include <stdio.h>
#include <stdlib.h>
#include "Priority.h"
#include "Pair.h"

#endif

/* defined(__Repair__Hash__) */
#ifndef HASH
#define HASH
typedef struct hashtable{
    int left,right;
    struct hashtable *next;
    struct hashtable *pre;
    PData *priority;
    struct hashtable *parent;

} Hash;

void _hash_push(Hash *new_hash,Hash *source_hash);
Hash *_hash_getLast(Hash *hash);
Boolean _hash_isSame(int left,int right,Hash *hash);
Hash *_hash_search(int left,int right,Hash *hash);
void _hash_search2(int left,int right,Hash *hash,Hash **p);
Hash *_hash_create(u_int left,u_int right,PData *pdata,Hash *parent);
void _hash_remove(Hash *hash);
void _hash_disp(Hash *hash);
void _hash_dispRe(Hash *hash);
#endif
