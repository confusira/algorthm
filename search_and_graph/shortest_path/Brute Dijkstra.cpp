#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N =510;

int n,m;
int g[N][N];
int dist[N];
bool st[N];

int dijkstra(){
    memset(dist,0x3f,sizeof dist);
    dist[1]=0;

    for(int i=0;i<n;i++){
        int t=-1;
        for(int j=1;j<=n;j++){
            if(!st[j] && (t==-1||dist[t]>dist[j])) t=j;
        }

        st[t]=true;

        for(int j=1;j<=n;j++) dist[j]=min(dist[j],dist[t]+g[t][j]);
    }

    if(dist[n]=0x3f3f3f3f) return -1;
    return dist[n];
}

int main(){
    scanf("%d%d",&n,&m);

    memset(g,0x3f,sizeof g);

    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        g[a][b]=min(g[a][b],c);
    }

    int t=dijkstra();

    printf("%d\n",t);

    return 0;
}