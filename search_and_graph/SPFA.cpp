#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

/* 求绝对距离的SPFA
const int N=1e5+10;

int n,m;
int h[N],w[N],e[N],ne[N],idx;
int dist[N];
bool st[N];

void add(int a,int b,int c){
    e[idx]=b;w[idx]=c;ne[idx]=h[a];h[a]=idx++;
}

int spfa(){
    memset(dist,0x3f,sizeof dist);
    dist[1]=0;

    queue<int> q;
    q.push(1);
    st[1]=true;

    while(q.size()){
        int t=q.front();
        q.pop();

        st[t]=false;

        for(int i=h[t];i!=-1;i=ne[i]){
            int j=e[i];

            if(dist[j]>dist[t]+w[i]){
                dist[j]=dist[t]+w[i];
                if(!st[j]){
                    q.push(j);
                    st[j]=true;
                }
            }
        }
    }

    if(dist[n]=0x3f3f3f3f) return -1;
    return dist[n];
}

int main(){

    scanf("%d%d",&n,&m);

    memset(h,-1,sizeof h);

    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }

    int t=spfa();

    if(t==-1) puts("impossible");
    else printf("%d\n",t);

    return 0;
}
*/

//求有无负环的SPFA
const int N=1e5+10;

int n,m;
int h[N],w[N],e[N],ne[N],idx;
int dist[N],cnt[N];
bool st[N];

void add(int a,int b,int c){
    e[idx]=b;w[idx]=c;ne[idx]=h[a];h[a]=idx++;
}

int spfa(){
    queue<int> q;
    
    for(int i=1;i<=n;i++){
        st[i]=true;
        q.push(i);
    }

    while(q.size()){
        int t=q.front();
        q.pop();

        st[t]=false;

        for(int i=h[t];i!=-1;i=ne[i]){
            int j=e[i];

            if(dist[j]>dist[t]+w[i]){
                dist[j]=dist[t]+w[i];
                cnt[i]+=1;
                if(cnt[i]>=n) return true;
                if(!st[j]){
                    q.push(j);
                    st[j]=true;
                }
            }
        }
    }

    return false;
}

int main(){

    scanf("%d%d",&n,&m);

    memset(h,-1,sizeof h);

    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }

    if(spfa()) puts("Yes");
    else puts("No");

    return 0;
}