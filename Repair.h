//
//  Repair.h
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/30.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//

#ifndef __Repair__Repair__
#define __Repair__Repair__
#define NAN UINT_MAX
#include <stdio.h>
#include "Hash.h"
#include "Priority.h"
#include "Rules.h"

#endif /* defined(__Repair__Repair__) */

void _repair_inputData(u_int *box,char *data,u_long len);
void _repair_read(u_int *data,u_long len,u_long *front,u_long *back,Hash *hash,Priority *priority);
void _repair_readNewPair(u_int *data,u_long len,u_long *front,u_long *back,Hash *hash,Priority *Priority,u_int target);
u_long _repair_push(u_int left,u_int right,u_long index,Hash *hash,Priority *priority);
Boolean getHash(u_int left,u_int right);
void _repair_initArray(u_long *front,u_long len);
void _repair_initData(u_int *front,u_long len);
void _repair_initHash(Hash *hash,u_long len);
Rule *_repair_compress(u_int *data,u_long len,u_long *front,u_long *back,Hash *hash,Priority *priority);
u_long _repair_getDataCount(u_int *data,u_long len);
Rule * _repair_replace(u_int *data,u_long len,u_long *front,u_long *back,Priority *priority,Hash *hash,u_int replacement);
u_long _repair_getPreDataIndex(u_int *data,u_long index);
u_long _repair_getNextDataIndex(u_int *data,u_long index,u_long len);
void checkIndex(u_int left,u_int right,u_int *data,u_long *front,u_long *back,u_long index,u_long len);
Boolean isNil(u_long val);
void dispData(u_int *data,u_long len);