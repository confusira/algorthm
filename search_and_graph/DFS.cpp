#include<iostream>

using namespace std;

/* 全排列问题
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
            st[i]=false;
        }
    }
}

int main(){
    cin >> n;

    dfs(0);

    return 0;
}
*/

//N皇后
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
