//
//  Hash.c
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/29.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//

#include "Hash.h"
Hash *_hash_getLast(Hash *hash){
    
    if(hash == NULL){
        printf("its NULL!!!!!!!!!");
        return NULL;
    }
    if(hash->next == NULL){
        return hash;
    }
    return _hash_getLast(hash->next);
}
void _hash_push(Hash *new_hash,Hash *source_hash){
    Hash *last_hash;
    last_hash = _hash_getLast(source_hash);
    last_hash->next = new_hash;
    new_hash->pre = last_hash;
}
Hash *_hash_search(int left,int right,Hash *hash){
    if(hash == NULL){
        
        return NULL;
    }

    if(_hash_isSame(left,right,hash) == TRUE){
        printf("~~~its same~~~ ''%p''  ",hash);
        printf(" ''%d%d''  ",hash->left,hash->right);
        printf(" ''%d%d''  ",left,right);
        printf("~~~~~~~~~~~~~~~~~ ");
        printf("~~~~~~~~%p~~~~~~ ",&hash->left);
        return hash;
    }
    if(left == 'g' && right == ';'){
    
    }
    return _hash_search(left,right,hash->next);
}
void _hash_search2(int left,int right,Hash *hash,Hash **p){
    if(hash == NULL){
        *p = NULL;
        return;
    }
    if(_hash_isSame(left,right,hash) == TRUE){
        *p = hash;
        printf(" ''%p''  ",*p);
        return;
    }
    _hash_search2(left,right,hash->next,p);
}
Boolean _hash_isSame(int left,int right,Hash *hash){
    if(hash == NULL){
        return FALSE;
    }
    printf("#ojfsh");
    if(left == 'g' && right == ';'){
        if(hash->pre != NULL){
            printf("TTTTT %c%c TTTTT",hash->pre->left,hash->pre->right);
            //getchar();
        
        }
    }
    
    if(left == hash->left && right == hash->right){
        printf("|  ( %c%c )  ( %c%c )  |",left,right,hash->left,hash->right);
        return TRUE;
    }else{
        return FALSE;
    }
}
Hash *_hash_create(u_int left,u_int right,PData *pdata,Hash *parent){
    Hash *hash;
    hash = (Hash*)malloc(sizeof(Hash));
    hash->left = left;
    hash->right = right;
    hash->priority = pdata;
    hash->parent = parent;
    hash->next = NULL;
    hash->pre = NULL;
    return hash;
}
void _hash_remove(Hash *hash){
    if(hash == NULL){
        printf("NULLですわよん");
        getchar();
        return;
    }
    if(hash->pre == NULL){
        //自分が先頭の場合
        hash->parent = hash->next;
        if(hash->next != NULL){
            hash->next->pre = NULL;
        }
    }else{
        //先頭でない場合
        //if(hash->pre){
            hash->pre->next = hash->next;
        //jj}
        if(hash->next){
            hash->next->pre = hash->pre;
        }
    }
}
void _hash_disp(Hash *hash){
    if(hash == NULL){
        printf("its NULL!!!!!!!!");
        return;
    }
    printf("%d %d--->",hash->left,hash->right);
    if(hash->next == NULL){
        printf("NULL!");
        return;
    }
    _hash_disp(hash->next);
}
void _hash_dispRe(Hash *hash){
    if(hash == NULL){
        printf("its null!!");
    }
    printf("%c%c--->",hash->left,hash->right);
    if(hash->pre == NULL){
        printf("NULL!");
        return;
    }
    _hash_dispRe(hash->pre);
}