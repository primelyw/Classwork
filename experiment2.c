#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int count_inversion(int *nums,int l,int r,int*nmb);
void cal_sim();

int main(){
    cal_sim();
    return 0;
}

void cal_sim(){
    int N=10;
    puts("How many song?");
    scanf("%d",&N);
    puts("songs idx according likes");
    int songs[N+1],tmp[N+1];
    for(int i = 0; i<N; i++) scanf("%d",songs+i),tmp[i]=songs[i];

    int res=count_inversion(songs,0,N,tmp); //count inversion in array num[l,r)
    
    printf("similarity : %d\n",res);

}

int count_inversion(int *nums,int l,int r ,int*nmb){
    if(r-l<=1)
        return 0;
    int cnt=0,lf_cnt,rt_cnt,mid;
    mid=(l+r)/2;
    cnt+=count_inversion(nums,l,mid,nmb)+count_inversion(nums,mid,r,nmb);
    int *tmp=(int*)malloc(sizeof(int)*(r-l));
    int *p1,*p2,*cur;
    p1=nmb+l,p2=nmb+mid,cur=tmp;
    int sub_cnt=0;
    while(p1<nmb+mid&&p2<nmb+r){
        if(*p1<*p2) 
            *(cur++)=*(p1++),cnt+=sub_cnt;
        else
            *(cur++)=*(p2++),++sub_cnt;
    }
    while(p1<nmb+mid)
        *(cur++)=*(p1++),cnt+=sub_cnt;
    
    while(p2<nmb+r)
        *(cur++)=*(p2++),++sub_cnt;

    for(int i=0; i<r-l; i++)
        nmb[l+i]=tmp[i];

    free(tmp);
   
    return cnt;
    
}
