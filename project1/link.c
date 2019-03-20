#include <stdio.h>
#include <stdlib.h>
typedef struct stuff{
    struct stuff* nxt;
    char num;
}stuff;

int main(){
    //initial;
    stuff* ship[30];
    for(int i = 0; i<30; i++) ship[i] = (stuff*)malloc(sizeof(stuff));
    for(int i = 0; i<30; i++){
        ship[i]->num = i;
        if(i<29){
            ship[i]->nxt = ship[i+1];
        }
        else{
            ship[i]->nxt = ship[0];
        }
    }

    //core;
    int ans[15];
    stuff* cur = ship[0];
    stuff* pre = ship[29];
    for(int cnt = 0; cnt<15; cnt++){
        for(int i = 0; i<8; i++){
            cur = cur->nxt;
            pre = pre->nxt;
        }
        ans[cnt] = cur->num;
        pre->nxt = cur->nxt;
        stuff* tmp = cur;
        free(tmp);
        cur = pre->nxt;
    }
    for(int i = 0; i<15; i++){
        printf("%d ",ans[i]);
    }printf("\n");
    return 0;
}
