# 搜索与图论

## DFS与BFS

###### 简介

| 搜索 | 数据结构 | 空间复杂度 | 适用问题     |
| :--: | -------- | ---------- | ------------ |
| DFS  | 栈       | O(h)       | 不具有最短性 |
| BFS  | 队列     | O(2^h)     | 最短路       |



### DFS

###### 原理

俗称“暴力搜索”，注意搜索顺序，本质是构造一个DFS搜索树

回溯：搜索完成返回上一次搜索位置（前驱）

先恢复现场再回溯

剪枝：如果当前状态没有搜索的必要，就不在搜索当前状态，而是直接回溯

全排列问题、N皇后问题



###### 模板代码

全排列问题

```c++
#include<iostream>

using namespace std;

const int N=10;

int n;
int path[N];
bool st[N];

void dfs(int u){
    if(u==n){
        for(int i=0;i<n;i++){
            cout << path[i] << ' ';
        }
        cout << endl;
        return;
    }

    for(int i=1;i<=n;i++){
        if(!st[i]){
            path[u]=i;
            st[i]=true;
            dfs(u+1);
            st[i]=false;//恢复现场
        }
    }
}

int main(){
    cin >> n;

    dfs(0);

    return 0;
}
```

N皇后

```c++
const int N=20;

int n;
char g[N][N];
bool row[N],col[N],dg[N],udg[N];

//第一种搜索顺序
void dfs1(int u){
    if(u==n){
        for(int i=0;i<n;i++) puts(g[i]);
        puts("");
        return;
    }

    for(int i=0;i<n;i++){
        if(!col[i] && !dg[u+i] && !udg[n-u+i]){
            g[u][i]='Q';
            col[i]=dg[u+i]=udg[n-u+i]=true;
            dfs1(u+1);
            col[i]=dg[u+i]=udg[n-u+i]=false;
            g[u][i]='.';
        }
    }
}

//第二种搜索顺序
void dfs2(int x,int y,int s){
    if(y==n) y=0,x++;
    if(x==n){
        if(s==n){
            for(int i=0;i<n;i++) puts(g[i]);
            puts("");
        }
        return ;
    }

    dfs2(x,y+1,s);

    if(!row[x] && !col[y] && !dg[x+y] && !udg[x-y+n]){
        g[x][y]='Q';
        row[x]=col[y]=dg[x+y]=udg[x-y+n]=true;
        dfs2(x,y+1,s+1);
        row[x]=col[y]=dg[x+y]=udg[x-y+n]=false;
        g[x][y]='.';
    }
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) g[i][j]='.';

    dfs2(0,0,0);

    return 0;
}

```

### BFS

###### 原理

根据距离起点的长度，构建一个BFS搜索树

最短路问题：边权都为1

用一个队列维护BFS搜索顺序

迷宫问题，八数码问题



###### 模板代码

```c++
queue.push(初始状态);

while(!q.empty()){
	type t=q.front();
	q.push(t.next())
}
```

迷宫问题

```c++
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

typedef pair<int,int> PII;

const int N=110;

int n,m;
int g[N][N];
int d[N][N];
PII q[N*N];

int bfs(){
    int hh=0,tt=0;
    q[0]={0,0};

    int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};

    memset(d,-1,sizeof d);
    d[0][0]=0;
    while(hh<=tt){
        auto t=q[hh++];

        for(int i=0;i<4;i++){
            int x=t.first+dx[i],y=t.second+dy[i];

            if(x>=0 && x<n && y>=0 && y<m && g[x][y]==0 && d[x][y]==-1){
                d[x][y]=d[t.first][t.second]+1;
                q[++tt]={x,y};
            }
        }
    }

    return d[n-1][m-1];
}

int main(){
    cin >> n >> m;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> g[i][j];
        }
    }

    cout << bfs() << endl;

    return 0;
}
```

八数码问题

```

```



### 树和图

###### 简介

树是一种特殊的图（无环连通图）

图分为有向图和无向图

无向图是一种特殊的有向图，即双向图

故只需要考虑有向图



#### 树和图的存储

###### 有向图的存储

（1）邻接矩阵  g [a] [b] : a->b的bool值或权值  O(n^2)

（2）邻接表



###### 模板代码

```c++
#include<iostream>
#include<cstring>

using namespace std;

const int N=1e5+10,M=2*N;

int h[N],e[M],ne[M],idx;

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

int main(){
    memset(h,-1,sizeof h);

    return 0;
}
```



#### 树与图的遍历

树与图的遍历包括DFS和BFS

###### 模板代码

DFS

```c++
void dfs(int u){
    st[u]=true;

    for(int i=h[u];i!=-1;i=ne[i]){
        int j=e[i];
        if(!st[j]) dfs(j);
    }

}
```

BFS

```c++
int n,m;
int h[N],e[N],ne[N],idx;
int d[N],q[N];

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

int bfs(){
    int hh=0,tt=0;

    q[0]=1;

    memset(d,-1,sizeof d);

    d[1]=0;

    while(hh<=tt){
        int t=q[hh++];

        for(int i=h[t];i!=-1;i=ne[i]){
            int j=e[i];
            if(d[j]==-1){
                d[j]=d[t]+1;
                q[++tt]=j;
            }
        }
    }

    return d[n];
}

int main(){
    cin >> n >> m;

    memset(h,-1,sizeof h);

    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        add(a,b),add(b,a);
    }

    cout << bfs() << endl;

    return 0;
}
```



#### 有向图的拓扑排序

###### 原理

有向无环图一定存在一个拓扑序列（拓扑图）

入度和出度

不停找入度为零的点，删边



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N =1e5+10;

int n,m;
int h[N],e[N],ne[N],idx;
int q[N],d[N];

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

bool toposort(){
    int hh=0,tt=-1;
    for(int i=1;i<=n;i++){
        if(d[i]==0) q[++tt]=i;
    }

    while(hh<=tt){
        int t=q[hh++];

        for(int i=h[t];i!=-1;i=ne[i]){
            int j=e[i];
            d[j]--;
            if(d[j]==0) q[++tt]=j;
        }
    }
    return tt==n-1;
}

int main(){
    cin >> n >> m;

    memset(h,-1,sizeof h);

    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        add(a,b);
        d[b]++;
    }

    if(toposort()){
        for(int i=0;i<n;i++){
            printf("%d ",q[i]);
            puts("");
        }
    }else puts("-1");

    return 0;
}
```



## 最短路

可以分为单源最短路和多源汇最短路

单源最短路分为所有边权均为正数和边权存在负数两种类型

难点在于建图，将实际问题抽象成一个最短路问题

### 单源最短路

#### 所有边权均为正数

##### 朴素Dijkstra算法

###### 原理

时间复杂度：O(n^2)

适合稠密图，m与n^2相差不大  用邻接矩阵来存储



###### 模板代码

```c++
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
```



##### 堆优化版的Dijkstra算法

###### 原理

时间复杂度：O(mlogn)

适合稀疏图，即边数与点数差不多，m<=n   用邻接表来存储

用堆来优化每次找寻最短边



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

typedef pair<int,int> PII;

const int N=1e5+10;

int n,m;
int h[N],w[N],e[N],ne[N],idx;
int dist[N];
bool st[N];

void add(int a,int b,int c){
    e[idx]=b;w[idx]=c;ne[idx]=h[a];h[a]=idx++;
}

int dijkstra(){
    memset(dist,0x3f,sizeof dist);
    dist[1]=0;

    priority_queue<PII,vector<PII>,greater<PII>> heap;
    heap.push({0,1});

    while(heap.size()){
        auto t=heap.top();
        heap.pop();

        int ver=t.second,distance=t.first;
        if(st[ver]) continue;

        for(int i=h[ver];i!=-1;i=ne[i]){
            int j=e[i];
            if(dist[j] > distance+w[i]){
                dist[j]=distance+w[i];
                heap.push({dist[j],j});
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
	
    int t=dijkstra();

    printf("%d\n",t);

    return 0;
}
```



#### 存在负边权

##### Bellman-Ford算法

###### 原理

时间复杂度：O(nm)

负权环：存在负边且负边权和大于正边权和的环

存在负权环不一定存在最短路

迭代k次，能够找到边数不大于k的最短路



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=510,M=1e4+10;

int n,m,k;
int dist[N],backup[N];

struct Edge{
    int a,b,w;
}edges[M];

int bellman_ford(){
    memset(dist,0x3f,sizeof dist);
    dist[1]=0;

    for(int i=0;i<k;i++){
        memcpy(backup,dist,sizeof dist);
        for(int j=0;j<m;j++){
            int a=edges[j].a,b=edges[j].b,w=edges[j].w;
            dist[b]=min(dist[b],backup[a]+w);
        }
    }

    if(dist[n]>0x3f3f3f3f/2) return -1;
    return dist[n];
}

int main(){
    scanf("%d%d%d",&n,&m,&k);

    for(int i=0;i<m;i++){
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        edges[i]={a,b,w};
    }

    int t=bellman_ford();

    if(t==-1) puts("impossible");
    else printf("%d\n",t);

    return 0;
}
```



##### SPFA算法

###### 原理

时间复杂度：一般 O(m)  最坏O(nm)

优化方法：用宽度搜索方法去选择需要更新的边

不适用场景：k边最短路、有负权环的图问题

优化方法：用一个cnt数组去记录边数，当cnt>=n,说明存在负权环



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

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
```



### 多源汇最短路

#### Floyd算法

###### 原理

时间复杂度：O(n^3)

用邻接矩阵存储

不适用场景：不允许有负权环



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=210,INF=1e9;

int n,m,Q;
int d[N][N];

void floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&Q);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) d[i][j]=0;
            else d[i][j]=INF;
        }
    }

    while(m--){
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);

        if(d[a][b] > INF/2) puts("impossible");
        else d[a][b]=min(d[a][b],w);
    }

    floyd();

    while(Q--){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",d[a][b]);
    }

    return 0;
}
```



## 最小生成树

主要应用场景：无向图，城市铺路问题

### 普利姆算法（Prim）

#### 朴素普利姆算法

###### 原理

时间复杂度：O(n^2)  适合稠密图



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=510,INF=0x3f3f3f3f;

int n,m;
int g[N][N];
int dist[N];
bool st[N];

int prim(){
    memset(dist,0x3f,sizeof dist);

    int res=0;
    for(int i=0;i<n;i++){
        int t=-1;
        for(int j=1;j<=n;j++){
            if(!st[j] && (t==-1 || dist[t]>dist[j])){
                t=j;
            }
        }

        if(i && dist[t]==INF) return INF;
        if(i) res+=dist[t];

        for(int j=1;j<=n;j++) dist[j]=min(dist[j],g[t][j]);

        st[t]=true;
    }

    return res;
}

int main(){
    scanf("%d%d",&n,&m);

    memset(g,0x3f,sizeof g);

    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        g[a][b]=g[b][a]=min(g[a][b],c);
    }

    int t=prim();

    if(t==INF) puts("impossible");
    else printf("%d\n",t);

    return 0;
}
```



#### 堆优化版的普利姆算法

###### 原理

时间复杂度：O(mlogn)  适合稀疏图

### 克鲁斯卡尔算法（Kruskal）

###### 原理

时间复杂度：O(mlogm)  适合稀疏图



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =2e4+5;

int n,m;
int p[N];

struct Edge{
    int a,b,w;

    bool operator< (const Edge &W)const{
        return w<W.w;
    }
}edges[N];

int find(int x){
    if(p[x]!=x) p[x]=find(p[x]);

    return p[x];
}

int main(){
    scanf("%d%d",&n,&m);

    for(int i=0;i<m;i++){
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        edges[i]={a,b,w};
    }

    sort(edges,edges+m);

    for(int i=1;i<=m;i++) p[i]=i;

    int res=0,cnt=0;
    for(int i=0;i<m;i++){
        int a=edges[i].a,b=edges[i].b,w=edges[i].w;

        a=find(a),b=find(b);

        if(a!=b){
            p[a]=b;
            res+=w;
            cnt++;
        }
    }

    if(cnt<n-1) puts("impossible");
    else printf("%d\n",res);

    return 0;
}
```

## 二分图

###### 简介

图中的点可以被划分为两个集合，集合内的点不存在边，边仅存在于集合之间

### 染色法

###### 原理

判断一个图是否是二分图

一个图是二分图当且仅当图中不含奇数环（环中边的个数为奇数）

时间复杂度：O(n+m)



###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=1e5+10,M=2e5+10;

int n,m;
int h[N],e[M],ne[M],idx;
int color[N];
bool st[N];

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

bool dfs(int u,int c){
    color[u]=c;

    for(int i=h[u];i!=-1;i=ne[i]){
        int j=e[i];
        if(!color[j]){
            if(!dfs(j,3-c)) return false;
        }
        else if(color[j]==c) return false;
    }

    return true;
}

int main(){
    scanf("%d%d",&n,&m);

    memset(h,-1,sizeof h);

    while(m--){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);
    }

    bool flag=true;
    for(int i=1;i<=n;i++) {
        if(!color[i]){
            if(!dfs(i,1)){
                flag=false;
                break;
            }
        }
    }

    if(flag) puts("YES");
    else puts("NO");

    return 0;
}
```

### 匈牙利算法

###### 原理

二分图匹配

时间复杂度：O(mn) 实际运行时间远远小于这个





###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N =510,M=1e5+10;

int n1,n2,m;
int h[N],e[M],ne[M],idx;
int match[N];
bool st[N];

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

bool find(int x){
    for(int i=h[x];i!=-1;i=ne[i]){
        int j=e[i];
        if(!st[j]){
            st[j]=true;
            if(match[j]==0 || find(match[j])){
                match[j]=x;
                return true;
            }
        }
    }
    return false;
}

int main(){
    scanf("%d%d%d",&n1,&n2,&m);

    memset(h,-1,sizeof h);

    while(m--){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
    }

    int res=0;
    for(int i=1;i<=n1;i++){
        memset(st,false,sizeof st);
        if(find(i)) res++;
    }

    printf("%d\n",res);

    return 0;
}
```

