# 搜索与图论

## DFS与BFS

###### 简介

| 搜索 | 数据结构 | 空间复杂度 | 适用问题     |
| :--: | -------- | ---------- | ------------ |
| DFS  | 栈       | O(h)       | 不具有最短性 |
| BFS  | 队列     | O(2^h)     | 最短路       |



### DFS

###### 原理

俗称“暴力搜索”，注意搜索顺序，本质是构造一个搜索树

回溯：搜索完成返回上一次搜索位置（前驱）

先恢复现场再回溯

剪枝

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

