//
//  Priority.c
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/29.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//
#include "Priority.h"
#include <limits.h>
#define NIL ULONG_MAX
Boolean _pdata_isSame(int left,int right,PData *data){
    if(left == data->left && right == data->right){
        return TRUE;
    }else{
        return FALSE;
    }
}
PData *_pdata_search(int left,int right,PData *data){
    if(_pdata_isSame(left,right,data)){
        return data;
    }
    if(data->next != NULL){
        return _pdata_search(left, right, data->next);
    }else{
        return NULL;
    }
}
PData *_pdata_getLast(PData *data){
    //getchar();
    if(data->next == NULL){
        return data;
    }
    return _pdata_getLast(data->next);
}
Priority *_priority_get(int count,Priority *priority){
    if(count == 1){
        return priority;
    }else{
        return _priority_get(count-1, priority);
    }
}
Priority *_priority_getLast(Priority *priority){
    if(priority->next == NULL){
        return priority;
    }
    return _priority_getLast(priority->next);
}
Priority *_priority_getMax(Priority *priority){
    if(priority->list != NULL){
        return priority;
    }
    if(priority->pre == NULL){
        return NULL;
    }
    return _priority_getMax(priority->pre);
    
}
void _priority_push(Priority *new_priority,Priority *source_priority){
    Priority *last_priority = _priority_getLast(source_priority);
    last_priority->next = new_priority;
    new_priority->pre = last_priority;
}
void _pdata_push(PData *new_pdata,PData *source_pdata){
    PData *last_pdata = _pdata_getLast(source_pdata);
    last_pdata->next = new_pdata;
    new_pdata->pre = last_pdata;
    new_pdata->parent = last_pdata->parent;
}
Boolean _priority_isEmpty(Priority *priority){
    if(priority->list == NULL){
        return TRUE;
    }else{
        return FALSE;
    }
}
PData *_pdata_create(u_int left,u_int right,u_long index,Priority *priority){
    PData *data = (PData*)malloc(sizeof(PData));
    data->left = left;
    data->right = right;
    data->index = index;
    data->parent = priority;
    data->next = NULL;
    data->pre = NULL;
    data->count = 1;
    return data;
}
void _pdata_remove(PData *pdata){
    if(pdata->next != NULL){
        pdata->next->pre = pdata->pre;
        if(pdata->parent->list == pdata){
            pdata->parent->list = NULL;
        }
    }else{
        if(pdata->parent->list == pdata){
            pdata->parent->list = pdata->next;
        }
    }
    if(pdata->pre != NULL){
        pdata->pre->next = pdata->next;
    }
    pdata->next = NULL;
    pdata->pre = NULL;
}
void _priority_forward(PData *pdata,Priority *priority, u_long index){
    pdata->count += 1;
    pdata->index = index;
    Priority *now_parent = pdata->parent;
    Priority *next_parent = now_parent->next;
    _pdata_remove(pdata);
    //自分が先頭だったら
    if(now_parent->list == pdata){
        now_parent->list = pdata->next;
    }
    if(next_parent == NULL){
        next_parent = _priority_create(pdata->parent);
        now_parent->next = next_parent;
    }
    pdata->parent = next_parent;
    if(next_parent->list == NULL){
        next_parent->list = pdata;
    }else{
        _pdata_push(pdata, next_parent->list);
    }
}
Priority *_priority_create(Priority *pre){
    Priority *priority = (Priority*)malloc(sizeof(Priority));
    priority->pre = pre;
    priority->list = NULL;
    priority->next = NULL;
    return priority;
}
u_int _priority_getMaxCount(Priority *priority){
    Priority *p = _priority_getLast(priority);
    p = _priority_getMax(p);
    return p->list->count;
}
Boolean _pdata_backward(PData *pdata,u_long index){
    printf("back  %c%c  ward",pdata->left,pdata->right);
    pdata->count -= 1;
    if(pdata->count != 0){
        if(index != NIL){
            pdata->index = index;
        }else{
            printf("inedexそのまんま");
        }
        Priority *now_parent = pdata->parent;
        Priority *pre_parent = now_parent->pre;
        //自分が先頭だったら
        if(now_parent->list == pdata){
            now_parent->list = pdata->next;
        }
        _pdata_remove(pdata);
        pdata->parent = pre_parent;
        if(pre_parent->list == NULL){
            pre_parent->list = pdata;
        }else{
            
            printf("ぷっしゅだぜ  %p    ",pre_parent->list);
            //getchar();
            _pdata_push(pdata, pre_parent->list);
        }
        return TRUE;
    }else{
        //カウントが０になったので完全に消す
        _pdata_remove(pdata);
        free(pdata);
        return FALSE;
    }
}
void _priority_disp(Priority *priority){
        printf("priority disp==>");
    if(priority->list != NULL){
        _pdata_disp(priority->list);
    }else{
        printf(" no data ");
    }
    printf("<======");
    if(priority->next != NULL){
        _priority_disp(priority->next);
    }
}
void _pdata_disp(PData *pdata){
    printf("%d%d----->",pdata->left,pdata->right);
    if(pdata->next == NULL){
        return;
    }
    _pdata_disp(pdata->next);
}