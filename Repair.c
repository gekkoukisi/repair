//
//  Repair.c
//  Repair
//
//  Created by 坂本 時緒 on 2014/08/30.
//  Copyright (c) 2014年 坂本 時緒. All rights reserved.
//

#include "Repair.h"
#include "Rules.h"
#include <stdlib.h>
#include <limits.h>
#define NIL ULONG_MAX
void _repair_inputData(u_int *box,char *data,u_long len){
    short i;
    for(i=0;i<len;i++){
        *box = data[i];
        box++;
    }
}
void _repair_read(u_int *data,u_long len,u_long *front,u_long *back,Hash *hash,Priority *priority){
    printf("read head    ");
    u_long i;
    u_int pre_c = 0;
    for(i=0;i<len;i++){
        if(i!=0){
            u_long pre_index = _repair_push(pre_c,data[i],i-1,hash,priority);
            if(i-1 != pre_index){
                printf("update");
                //printf("    %p    ",priority->next);
                //既出のペアだったため、front,backを更新
                front[pre_index] = i-1;
                back[i-1] = pre_index;
                if(pre_index == NAN)
                    printf("found!!!!!!");
                printf(" 2backccheck=>%lu<==>%d<=",pre_index,data[pre_index]);
            }
        }
        pre_c = data[i];
    }
}
void _repair_readNewPair(u_int *data,u_long len,u_long *front,u_long *back,Hash *hash,Priority *Priority,u_int target){
    u_int pre_c = NAN;
    u_long i,index = 0;
    printf("---------target %d  更新開始--------------",target);
    for(i=0;i<len;i++){
 //           printf("now item is ----->>>>>>%lu<<<<<<<<<-----",data[i]);
        if(data[i] == NAN){
            continue;
        }
        if(pre_c != NAN){
            if(pre_c == target || data[i] == target){
                u_long pre_index = _repair_push(pre_c, data[i], index, hash, Priority);
                if(pre_c == 257 && data[i] == 115){
                    printf("special--->%lu",pre_index);
                }
                if(data[pre_index] == data[index] && data[_repair_getNextDataIndex(data, pre_index, len)] == data[i]){
                    printf("success!!!!!!!!!!");
                }else{
                    printf("no!!look!!!!!!!!!!");
                }
                if(pre_index != index){
                    //既出
                    front[pre_index] = index;
                    printf("frontcheck =>%lu<=",index);
                    back[index] = pre_index;
                    printf(" 3backccheck=>%lu<=",pre_index);
                }
            }
        }
        pre_c = data[i];
        index = i;
    }
    
}
u_long _repair_push(u_int left,u_int right,u_long index,Hash *hash,Priority *priority){
    //printf("--------%d   %d----------",left,right);
    //getchar();
    short hash_index = getHash(left,right);
    //既出ペアの場合にこの変数に前のインデックスを入れて返す(デフォルトで現在のインデックス)
    u_long ret_index = index;
    Hash *target_hash;
    if(hash[hash_index].priority == NULL){//------------------------
        
        //該当のハッシュに何もない時
            printf("_______hashに初___%d %c%c______",hash_index,left,right);
       // _hash_disp(&hash[hash_index]);
        
        /*target_hash = &hash[hash_index];*/
        PData *new_pdata = _pdata_create(left, right, index,priority);
        /*target_hash->left = left;
        target_hash->right = right;
        target_hash->priority = new_pdata;
        target_hash->parent = &hash[hash_index];*/
        hash[hash_index].left = left;
        hash[hash_index].right = right;
        hash[hash_index].priority = new_pdata;
        hash[hash_index].parent = &hash[hash_index];
        
        if(_priority_isEmpty(priority)){
            priority->list = new_pdata;
        }else{
            _pdata_push(new_pdata, priority->list);
        }
        
      //  _hash_disp(&hash[hash_index]);
    }else{//-------------------------------------------------------
        target_hash = _hash_search(left, right, &hash[hash_index]);
        if(target_hash == NULL){//---------------------------------
            
            printf("_______hashに追加______%d %c%c____",hash_index,left,right);
           // _hash_disp(&hash[hash_index]);
            //該当のハッシュに同じモノがない時
            
            PData *pdata = _pdata_create(left, right, index,priority);
            //printf("###########  %d  #############",hash_index);
            Hash *new_hash = _hash_create(left, right, pdata,&hash[hash_index]);
            _hash_disp(&hash[hash_index]);
            target_hash = _hash_getLast(&hash[hash_index]);
            target_hash->next = new_hash;
            new_hash->pre = target_hash;
            if(_priority_isEmpty(priority)){
                priority->list = pdata;
            }else{
                _pdata_push(pdata, priority->list);
            }
    //        _hash_disp(&hash[hash_index]);
        }else{//--------------------------------------------------
            
            //該当ハッシュに同じモノが合った場合
            
            ret_index = target_hash->priority->index;
            _priority_forward(target_hash->priority,priority,index);
            
        }
    }
    /*if(hash_index == 4){
        _hash_disp(&hash[hash_index]);
        getchar();
    }*/
    return ret_index;
}
Rule *_repair_compress(u_int *data,u_long len,u_long *front,u_long *back,Hash *hash,Priority *priority){
    u_long i=0;
    u_int replacement = 256;
    
    //while(_repair_getDataCount(data, len) != 1){
    Rule *rule = NULL;
    while(i < 500){
        //置き換え
        Rule *new_rule = _repair_replace(data,len,front,back,priority,hash,replacement);
        if(new_rule == NULL){
            break;
        }
        if(rule != NULL){
            _rule_push(new_rule, rule);
        }else{
            rule = new_rule;
        }
        
        //データチェック
        short j;
        u_long count=0;
        printf("データチェック--------  %d-------",j);
        for(j=0;j<len;j++){
            if(data[j] != NAN){
                count++;
                printf("%d ",data[j]);
            }
        }
        if(count == 1){
            break;
        }
        //データ構造に新しいペアを反映
        
        //ハッシュ確認
        for(j=0;j<7;j++){
            printf("checkcheck--------  %d-------",j);
            _hash_disp(&hash[j]);
        }
        for(j=0;j<7;j++){
            printf("rererecheckcheck--------  %d-------",j);
            Hash *
            last_hash = _hash_getLast(&hash[j]);
            _hash_dispRe(last_hash);
        }
        _repair_readNewPair(data, len, front,back,hash, priority, replacement);
        
        printf("　　　　%lu週目　終　",i);
        for(j=0;j<7;j++){
            printf("checkaftercheck--------  %d-------",j);
            _hash_disp(&hash[j]);
        }
        replacement++;
        i++;
    }
    return rule;
    
    
}
Rule * _repair_replace(u_int *data,u_long len,u_long *front,u_long *back,Priority *priority,Hash *hash,u_int replacement){
    _priority_disp(priority);
    //getchar();
    printf("===========%d==============",replacement);
    //getchar();
    Priority *last_priority = _priority_getLast(priority);
    PData *target_pdata = _priority_getMax(last_priority)->list;
    if(target_pdata == NULL){
        //全て終了
        return NULL;
    }
    printf("  maxmax-=====> %d  %d%d  index:%lu<=====   ",_priority_getMaxCount(priority),target_pdata->left,target_pdata->right,target_pdata->index);
    //getchar();
    u_long index = target_pdata->index,i;
    u_long next_index = _repair_getNextDataIndex(data, index,len);
    printf("now==>%lu   next==>%lu  ",index,next_index);
    //getchar();
    u_int left = data[index];
    u_int right = data[next_index];
    i = index;
    
    printf("checkcheckbackcheckcheck->%d %d<-  ",left,right);
    
    checkIndex(left,right,data,front,back,index,len);
    
    do{
        printf(" %d %dリプレイス",left,right);
        //置き換え
        data[i] = replacement;
        //next_index = _repair_getNextDataIndex(data, i,len);
        data[next_index] = NAN;
        u_long right_index = _repair_getNextDataIndex(data, next_index,len);
        printf("next index id -->%lu    right index is -->%lu    ",next_index,right_index);
            printf("ooooooooooo  while head  oooooooooooooo");
            //getchar();
        if(right_index != NIL && data[right_index] != NAN){
            //右となりのペアが崩れたので、データ構造に反映
            u_int r_left = right,r_right = data[right_index];
            printf("こいつ=>%d%d<= %lu  ",r_left,r_right,right_index);
            u_long latest_index = back[next_index];
            if(next_index != NIL && front[next_index] != NIL && back[next_index]){
                printf("front   =======>>>>>>%lu    ",front[next_index]);
                //次のインデックスがある場合、変更
                latest_index = NIL;
                back[front[next_index]] = back[next_index];
                printf(" 4backccheck=>%lu<==>%d<=",back[next_index],data[back[next_index]]);
            }
            if(front[next_index] != NIL && next_index != NIL && back[next_index] != NIL){
                printf("back   =======>>>>>>%lu    ",back[next_index]);
                //前のインデックスがある場合、変更
                front[back[next_index]] = front[next_index];
                printf("frontcheck =>%lu<=",front[next_index]);
            }
            
            //frontとbackにNILを。
            front[next_index] = NIL;
            back[next_index] = NIL;
                
            //ペアの出現回数を変更
            short r_hash_index = getHash(r_left, r_right);
            Hash *p,*r_hash;
            p = _hash_search(r_left,r_right,&hash[r_hash_index]);
            r_hash = p;
            _hash_disp(&hash[r_hash_index]);
            printf("RIGHT  i will search  %d %d    ",r_left,r_right);
            //getchar();
            printf("     ' %p '      ",r_hash);
            //printf("     ' %d %d '      ",r_hash->left,r_hash->right);
            //getchar();
            _hash_disp(&hash[r_hash_index]);
            //getchar();
            PData *r_pdata = r_hash->priority;
            if(!_pdata_backward(r_pdata,latest_index)){
                //カウント０になったのでハッシュからも削除
                printf("rmrmrmrmrmrmrmrmrmr/mrmrmrmrmrm right (%d%d)  ",r_left,r_right);
                _priority_disp(priority);
                //getchar();
                _hash_remove(r_hash);
                //free(r_hash);
            }

        }
        u_long pre_index = _repair_getPreDataIndex(data,i);
        printf("index is -->%lu      pre_index is -->%lu      ",i,pre_index);
        if(pre_index != NIL && data[pre_index] != NAN && front[pre_index]){
            //printf("NILNILNILNIL==>%lu",NIL);
            //左となりのペアが崩れたので、データ構造に反映
            u_int l_left = data[pre_index],l_right = left;
            printf("left is! ===>%c<====|||",data[pre_index]);
            u_long l_latest_index = back[pre_index];
            if(front[pre_index] != NIL && pre_index != NIL){
                //次のインデックスがある場合、変更
                l_latest_index = NIL;
                back[front[pre_index]] = back[pre_index];
                printf(" 1backccheck=>%lu<=",back[pre_index]);
            }
            if(pre_index != NIL && back[pre_index] != NIL){
                //前のインデックスがある場合、変更
                if(pre_index != NIL && back[pre_index] != NIL){
                    front[back[pre_index]] = front[pre_index];
                }else{
                    //front[back[pre_index]] = front[pre_index];
                }
                printf("frontcheck =>%lu<=",front[pre_index]);
            }
            //frontとbackにNILを。
            front[pre_index] = NIL;
            back[pre_index] = NIL;
            
            //ペアの出現回数を変更
            short l_hash_index = getHash(l_left, l_right);
            //Hash *p;
            //p = _hash_search(l_left,l_right,&hash[l_hash_index]);
            //printf("-%d-",p->left);
            Hash *l_hash =_hash_search(l_left,l_right,&hash[l_hash_index]);
            printf("LEFT  i will search %d%d    ",l_left,l_right);
            printf("     ' %p '      ",l_hash);
            _hash_disp(&hash[l_hash_index]);
            //getchar();
            
            PData *l_pdata = l_hash->priority;
            if(!_pdata_backward(l_pdata,l_latest_index)){
                //カウント０になったのでハッシュからも削除
                _hash_remove(l_hash);
                printf("rmrmrmrmrmrmrmrmrmrmrmrmrmrmrm  (%d%d)  ",l_left,l_right);
                //free(l_hash);
            }

        }
        //インデックスを後ろに
        u_long tmp = i;
        i = back[i];
        front[i] = NIL;
        back[tmp] = NIL;
        next_index = _repair_getNextDataIndex(data, i, len);
        /* printf("word is %d%d",data[i],data[next_index]);
        printf("いっしょじゃなきゃあかん %d%d",left,right);*/
        if(i == NIL){
            printf("脱出！！！！！！");
        }
    }while(i < len && i != NIL);
    
    
    //getchar();
    //元のプライオリティとハッシュを削除
    Hash *target_hash;
    target_hash = _hash_search(left, right, &hash[getHash(left,right)]);
    _pdata_remove(target_pdata);
    /*if(target_pdata == target_pdata->parent->list){
        target_pdata->parent->pre->next = NULL;
        //getchar();
        free(target_pdata->parent);
    }*/
    _hash_remove(target_hash);
    
    //free(target_pdata);
    //free(target_hash);
    Rule *rule = _rule_create(replacement, left, right);
    return rule;
}
short getHash(u_int left,u_int right){
    return ((left+right)%7);
}
void _repair_initArray(u_long *array,u_long len){
    u_long i;
    for(i=0;i<len;i++){
        array[i] = NIL;
    }
}
void _repair_initData(u_int *array,u_long len){
    u_long i;
    for(i=0;i<len;i++){
        array[i] = NAN;
    }
}
void _repair_initHash(Hash *hash,u_long len){
    u_long i;
    for(i=0;i<len;i++){
        hash->left = 0;
        hash->right = 0;
        hash->next = NULL;
        hash->pre = NULL;
        hash->priority = NULL;
        hash->parent = NULL;
        hash++;
    }
}
u_long _repair_getDataCount(u_int *data,u_long len){
    u_long i,count=0;
    for(i=0;i<len;i++){
        if(data[i] != NAN)
            count++;
    }
    return count;
}
u_long _repair_getPreDataIndex(u_int *data,u_long index){
    u_long i;
    for(i=index-1;i!=0;i--){
        if(data[i] != NAN){
            return i;
        }
    }
    return NIL;
}
u_long _repair_getNextDataIndex(u_int *data,u_long index,u_long len){
    u_long i;
    for(i=index+1;i<len;i++){
        if(data[i] != NAN){
            return i;
        }
    }
    return NIL;
}
Boolean isNil(u_long val){
    return (NIL-val) < 10;
}
void checkIndex(u_int left,u_int right,u_int *data,u_long *front,u_long *back,u_long index,u_long len){
    if(left!=data[index] || right!=data[_repair_getNextDataIndex(data,index, len)]){
        printf("変だよ！！！front===>%lu %lu<=",front[index],_repair_getNextDataIndex(data, front[index], len));
    }
    printf("-||%lu %lu||-",index,_repair_getNextDataIndex(data, index, len));
    if(back[index] != NIL){
        checkIndex(left,right,data,front,back,back[index],len);
    }
}
void dispData(u_int *data,u_long len){
    u_long i;
    for(i=0;i<len;i++){
        printf("%c",data[i]);
    }
}