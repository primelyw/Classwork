#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e4;
int d[maxn];
int prevt[maxn+10]; //pre vertex;
int path[maxn+10];
typedef pair<int,int>P;
const int oo = 1e9;
typedef struct edge{
    int to,cost;
    edge(int x = 0,int y = 0):to(x),cost(y){}
}edge;



int N,M,source,distination;
vector<edge> G[100];

void dijkstra(int s){
    fill(d,d+maxn+1,oo);
    d[s] = 0;
    priority_queue<P,vector<P>,greater<P> > que;
    que.push(P(0,s));
    while(!que.empty()){
        P p = que.top();
        que.pop();
        int v = p.second;
		if(d[v]<p.first) continue;
        for(int i = 0; i<G[v].size(); i++){
            edge e = G[v][i];
            if(d[e.to]>d[v]+e.cost){
                prevt[e.to] = v;
                d[e.to] = d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}

void initial(){
    // 邻接表;
    fill(prevt,prevt+maxn+1,-1);
    fill(path,path+maxn+1,-1);
    scanf("%d %d %d %d",&N,&M,&source,&distination);
    for(int i = 1; i<=M; i++){
        int from,to,cost;
        scanf("%d %d %d",&from,&to,&cost);
        G[from].push_back(edge(to,cost));
    }
}

void show_build_path(int cur){
    if(prevt[cur]==-1){
        printf("%d ",cur);
    }
    else{
        show_build_path(prevt[cur]);
        printf("%d ",cur);
    }
}

int main(){
    initial();
    dijkstra(source);
    printf("Shortest path length is %d \nThe path is:",d[distination]);   
    show_build_path(distination);
    printf("\n");
    return 0;
}