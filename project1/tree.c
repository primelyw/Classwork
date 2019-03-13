#include <stdlib.h>
#include <stdio.h>
typedef struct tree{
    struct tree* lf;
    struct tree* rt;
    char ch; //value;
    char ck; //check;
}tree;

char s[55];

void fly_me(tree* cur,int *leaf,int *dep,int depth);
void build_pre_tree(tree* cur,int * pos);
void refresh_tree(tree* cur);
void build_tree(tree* root,int *pos);
void fly_middle(tree* cur);
void fly_later(tree* cur);

int main(){
    tree* t[55];
    scanf("%50s",s); //abc,,de,g,,f,,,
    tree* root = (tree*)malloc(sizeof(tree));
    int pos = 0;
    build_tree(root,&pos);
    int leaf;
    int depth = 0;
    fly_me(root,&leaf,&depth,1);
    fly_middle(root);
    printf("\n");
    fly_later(root);
    printf("\n");
    printf("The number of leaves:%d\nDepth:%d\n",leaf,depth);
    return 0;
}


//look over whole tree and calculate the number of leaves and depth;
void fly_me(tree* cur,int *leaf,int *dep,int depth){
    //printf("%c\n",cur->ch);
    if(cur->lf == NULL && cur->rt == NULL){
        *leaf += 1;
        if(*dep<depth) *dep = depth;
    }
    if(cur->lf!=NULL) fly_me(cur->lf,leaf,dep,depth+1);
    if(cur->rt!=NULL) fly_me(cur->rt,leaf,dep,depth+1);
}

void build_pre_tree(tree* cur,int * pos){
    if(s[*pos]==','||s[*pos]=='\0'){
        cur->lf = NULL;
        cur->rt = NULL;
        cur->ch = 0;
    }
    else{
        cur->lf = (tree*)malloc(sizeof(tree));
        cur->rt = (tree*)malloc(sizeof(tree));
        cur->ch = s[*pos];
    }
    *pos += 1;
    if(cur->lf!=NULL) build_pre_tree(cur->lf,pos);
    if(cur->rt!=NULL) build_pre_tree(cur->rt,pos);
}

void refresh_tree(tree* cur){
    if(cur->lf->ch == 0) cur->lf = NULL;
    if(cur->rt->ch == 0) cur->rt = NULL;
    if(cur->lf!=NULL) refresh_tree(cur->lf);
    if(cur->rt!=NULL) refresh_tree(cur->rt);
}

void build_tree(tree* root,int *pos){
    build_pre_tree(root,pos);
    refresh_tree(root);
}

void fly_middle(tree* cur){
    if(cur->lf!=NULL) fly_middle(cur->lf);
    printf("%c ",cur->ch);
    if(cur->rt!=NULL) fly_middle(cur->rt);
}

void fly_later(tree* cur){
    if(cur->lf!=NULL) fly_later(cur->lf);
    if(cur->rt!=NULL) fly_later(cur->rt);
    printf("%c ",cur->ch);
}