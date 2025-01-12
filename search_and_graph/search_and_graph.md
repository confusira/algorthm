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
    st[u]==true;

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

有向无环图一定存在一个拓扑序列（拓扑图）

入度和出度