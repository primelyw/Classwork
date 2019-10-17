#include <stdio.h>

void reverse(char *s,int n){
    for(int i=0; i<n/2; i++){
        char tmp=s[i];
        s[i]=s[n-1-i];
        s[n-1-i]=tmp;
    }
}

int to_N(char *des,long long num,int n){
    // success return 0
    // failed return -1
    int pos=0;
    if(!(n==10||n==2||n==16||n==8)){
        return -1;
    }
    while(num){
        if(n!=16){
            des[pos++]=0x30+num%n;
        }
        else{
            char l=num%16;
            if(l<10){
                des[pos++]=0x30+l;
            }
            else{
                des[pos++]=l-10+'a';
            }
        }
        num/=n;
    }
    des[pos]='\x00';
    reverse(des,pos);
    return 0;
    
}

int main(){
    unsigned long long num;
    int opt;
    puts("An INTEGER?");
    scanf("%llu",&num);
    puts("Number System?");
    scanf("%d",&opt);
    char des[100];
    int res=to_N(des,num,opt);
    if(res==0){
        switch (opt)
        {
        case 10:
        case 2:
            printf("%s",des);
            break;
        
        case 8:
            printf("0%s",des);
            break;
        
        case 16:
            printf("0x%s",des);
            break;
        }
    }
    else if(res==-1){
        puts("Not valid number system(10,8,16,2)");
    }
    return 0;
}