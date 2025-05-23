# 动态规划

[TOC]

###### 原理

动态规划问题可以从状态表示和状态计算来入手

（1）状态表示：状态用几个变量来表示（集合的表示）

集合

属性

（2）状态计算：每一个状态怎么计算出来（集合的划分）

（3）动态规划的优化问题：

往往是对动态规划的代码或者方程做一个等价变形

（4）时间复杂度计算：状态量乘转移数量



## 背包问题（组合DP）

###### 简介

N个物品和容量为V的背包，物品有容量和价值两个属性，挑一些物品，使总容量小于背包容量的同时，价值最大



###### 原理

（1）状态表示：状态用几个变量来表示 `f(i,j)`（集合的表示）

集合：满足所有选法，只从前`i`个物品中选，总体积小于等于`j`

属性：**价值的最大值**，价值的最小值，数量

（2）状态计算：每一个状态怎么计算出来（集合的划分）

`f(i,j)`可以划分为不含`i`的集合`f(i-1,j)`和含`i`的集合`f(i-1,j-vi)+wi`
$$
f(i,j)=max(f(i-1,j),f(i-1,j-v_i)+w_i)
$$

### 01背包

###### 描述

每件物品只允许使用一次



###### 原理

（1）状态表示：状态用几个变量来表示 `f(i,j)`（集合的表示）

集合：满足所有选法，只从前`i`个物品中选，总体积小于等于`j`

属性：**价值的最大值**，价值的最小值，数量

（2）状态计算：每一个状态怎么计算出来（集合的划分）

`f(i,j)`可以划分为不含`i`的集合`f(i-1,j)`和含`i`的集合`f(i-1,j-vi)+wi`
$$
f(i,j)=max(f(i-1,j),f(i-1,j-v_i)+w_i)
$$
（3）优化：滚动数组降维



- **采药**

01背包



- **装箱问题**

01背包

同时将体积也看成价值



- **开心的金明**

01背包



- **能量石**

01背包+贪心



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =1010;

int n,m;
int v[N],w[N];
int f[N][N];

int main(){
    cin >> n >> m;

    for(int i=1;i<=n;i++){
        cin >> v[i] >> w[i];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j]=f[i-1][j];
            if(j>=v[i]) f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);
        }
    }

    cout << f[n][m] << endl;

    return 0;
}
```

优化后

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =1010;

int n,m;
int v[N],w[N];
int f[N];

int main(){
    cin >> n >> m;

    for(int i=1;i<=n;i++){
        cin >> v[i] >> w[i];
    }

    for(int i=1;i<=n;i++){
        for(int j=m;j>=v[i];j--){
            f[j]=max(f[j],f[j-v[i]]+w[i]);
        }
    }

    cout << f[m] << endl;

    return 0;
}
```



### 完全背包

###### 描述

01背包

每件物品允许使用无限次



###### 原理

（1）状态表示：状态用几个变量来表示 `f(i,j)`（集合的表示）

集合：满足所有选法，只从前`i`个物品中选，总体积小于等于`j`

属性：**价值的最大值**，价值的最小值，数量

（2）状态计算：每一个状态怎么计算出来（集合的划分）

`f(i,j)`可以划分为含k个`i`的集合（k=0,1,...,V/v[i]）

曲线救国：

1、去掉k个物品i

2、求max   `f(i-1,j-k*v[i])`

3、再加回来k个物品i的价值 `f(i-1,j-k*v[i])+k*w[i]`

$$
f(i,j)=max(f(i-1,j-k*v_i)+k*w_i)
$$
（3）优化：展开方程优化多余项，优化多余条件
$$
f(i.j)=max(f(i-1,j),f(i,j-v_i)+w_i)
$$


###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =1010;

int n,m;
int v[N],w[N];
int f[N][N];

int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> v[i] >> w[i];

    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k*v[i]<=j;k++){
                f[i][j]=max(f[i][j],f[i-1][j-k*v[i]]+k*w[i]);
            }
        }
    }

    cout << f[n][m] << endl;

    return 0;
}
```

优化后

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =1010;

int n,m;
int v[N],w[N];
int f[N];

int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> v[i] >> w[i];

    for(int i=1;i<=n;i++){
        for(int j=v[i];j<=m;j++){
            f[j]=max(f[j],f[j-v[i]]+w[i]);
        }
    }

    cout << f[m] << endl;

    return 0;
}
```



### 多重背包

###### 描述

完全背包

每件物品允许使用有限次



完全背包：求所有前缀的最大值

多重背包：求滑动窗口内的最大值



###### 原理

（1）状态表示：状态用几个变量来表示 `f(i,j)`（集合的表示）

集合：满足所有选法，只从前`i`个物品中选，总体积小于等于`j`

属性：**价值的最大值**，价值的最小值，数量

（2）状态计算：每一个状态怎么计算出来（集合的划分）

`f(i,j)`可以划分为含k个`i`的集合（k=0,1,...,s[i]）

曲线救国：

1、去掉k个物品i

2、求max   `f(i-1,j-k*v[i])`

3、再加回来k个物品i的价值 `f(i-1,j-k*v[i])+k*w[i]`


$$
f(i,j)=max(f(i-1,j-k*v_i)+k*w_i)
$$
（3）优化

二进制优化     时间复杂度（O(NVs)->O(NVlogs)）

s=1023        0,1,2,...,1023

1 , 2 , 4 , 8 ,... , 512

0 - 1 - 3 - 7 - ... - 1023

s=200

1,2,4,8,16,32,64,73

给定s

1,2,4,8,16,...,2^k,c

c<2^(k+1)

0-2^(k+1)-1

c-s



- **多重背包（2）**

二进制优化



- **多重背包（3）**

单调队列优化（滑动窗口求最值）



- **庆功会**

简单多重背包



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =110;

int n,m;
int v[N],w[N],s[N];
int f[N][N];

int main(){
    cin >> n >> m;

    for(int i=1;i<=n;i++) cin >> v[i] >> w[i] >> s[i];

    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=s[i] && k*v[i]<=j;k++){
                f[i][j]=max(f[i][j],f[i-1][j-k*v[i]]+k*w[i]);
            }
        }
    }

    cout << f[n][m] << endl;

    return 0;
}
```

优化后

```c++
const int N = 25000,M=2010;

int n,m;
int v[N],w[N];
int f[N];

int main(){
    cin >> n >> m;

    int cnt=0;

    for(int i=1;i<=n;i++){
        int a,b,s;
        cin >> a >> b >> s;
        int k=1;
        while(k<=s){
            cnt++;
            v[cnt]=a*k;
            w[cnt]=b*k;
            s-=k;
            k*=2;
        }
        if(s>0){
            cnt++;
            v[cnt]=a*s;
            w[cnt]=b*s;
        }
    }

    n=cnt;

    for(int i=1;i<=n;i++){
        for(int j=m;j>=v[i];j--){
            f[j]=max(f[j],f[j-v[i]]+w[i]);
        }
    }

    cout << f[m] << endl;

    return 0;
}
```



### 分组背包

###### 描述

几种不同物品被分为一组，每组只允许用一次

多重背包



###### 原理

（1）状态表示：状态用几个变量来表示 `f(i,j)`（集合的表示）

集合：满足所有选法，只从前`i`组物品中选，总体积小于等于`j`

属性：**价值的最大值**，价值的最小值，数量

（2）状态计算：每一个状态怎么计算出来（集合的划分）

`f(i,j)`可以划分为不含`i`组物品的集合`f(i-1,j)`和含`i`组某一物品的集合`f(i-1,j-v[i,k])+w[i,k]`
$$
f(i,j)=max(f(i-1,j),f(i-1,j-v_{i,k})+w_{i,k})
$$
（3）优化：滚动数组降维



- **金明的预算方案**

开心的金明

将每一种互斥的决策看成是一组中的成员



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =110;

int n,m;
int v[N][N],w[N][N],s[N];
int f[N];

int main(){
    cin >> n >> m;

    for(int i=1;i<=n;i++){
        cin >> s[i];
        for(int j=0;j<s[i];j++){
            cin >> v[i][j] >> w[i][j];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=m;j>=0;j--){
            for(int k=0;k<s[i];k++){
                if(v[i][k]<=j){
                    f[j]=max(f[j],f[j-v[i][k]]+w[i][k]);
                }
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
```



### 混合背包

###### 描述

01背包+完全背包+多重背包



###### 原理

（1）状态表示  `f[i,j]`

集合：只从前`i`件物品中选，且总体积不超过`j`的选法

属性：最大值

（2）状态计算

01背包，完全背包，多重背包分别计算
$$
01背包~~f[i][j]=max(f[i-1][j],f[i-1][j-v_i]+w_i)\\
完全背包~~f[i][j]=max(f[i-1][j],f[i][j-v_i]+w_i)\\
多重背包~~f[i][j]=max(f[i-1][j],f[i-1][j-v_i]+w_i,f[i-1][j-2*v_i]+2*w_i,...)
$$


###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 1010;

int n,m;
int f[N];

int main(){
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        int v,w,s;
        cin >> v >> w >> s;
        if(s==0){
            for(int j=v;j<=m;j++) f[j] = max(f[j],f[j-v]+w);
        }
        else{
            if(s==-1) s=1;
            for(int k=1;k<=s;k*=2){
                for(int j=m;j>=k*v;j--){
                    f[j] = max(f[j],f[j-k*v]+k*w);
                }
                s-=k;
            }
            if(s){
                for(int j=m;j>=s*v;j--){
                    f[j] = max(f[j],f[j-s*v]+s*w);
                }
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
```

### 依赖背包

###### 描述

分组背包+树形DP



###### 原理

（1）状态表示  `f[u,j]`

集合：所有以`u`为根的子树中选，且总体积不超过`j`的方案

属性：最大值

（2）状态计算

递归方法



- **选课**





###### 模板代码

```c++
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 110;

int n,m;
int v[N],w[N];
int h[N],e[N],ne[N],idx;
int f[N][N];

void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

int dfs(int u){
    for(int i=h[u];i!=-1;i=ne[i]){
        int son = e[i];
        dfs(son);

        for(int j=m-v[u];j>=0;j--){
            for(int k=0;k<=j;k++){
                f[u][j] = max(f[u][j],f[u][j-k]+f[son][k]);
            }
        }
    }

    for(int i=m;i>=v[u];i--) f[u][i]=f[u][i-v[u]]+w[u];
    for(int i=0;i<v[u];i++) f[u][i] = 0;
}

int main(){
    cin >> n >> m;

    memset(h,-1,sizeof h);
    int root;

    for(int i = 1;i <= n;i++){
        int p;
        cin >> v[i] >> w[i] >> p;
        if(p==-1) root = i;
        else add(p,i);
    }

    dfs(root);

    cout << f[root][m] << endl;

    return 0;
}
```

### 二维费用背包

###### 描述

01背包，完全背包，多重背包，分组背包再加一层费用



###### 原理

（1）状态表示  `f[i,j,k]`

集合：所有只从前`i`个物品中选，并且总体积不超过`j`，总重量不超过`k`的选法

属性：最大值

（2）状态计算

分解为所有包含物品`i`的选法和不包含`i`的选法
$$
f[i][j][k]=max(f[i-1][j][k],f[i-1][j-v_i][k-m_i]+w_i)
$$


- **小精灵**

01背包+二维费用

花费1：精灵球的数量

花费2：皮卡丘的体力值

价值：小精灵的数量



（1）状态表示  `f[i,j,k]`

集合：表示只从前`i`个物品中选，且花费1不超过`j`，花费2不超过`k`的选法的集合

属性：最大价值

（2）状态计算
$$
f[i][j][k]=max(f[i-1][j][k],f[i-1][j-v_1[i]][k-v_2[i]]+1)
$$
最多收服的小精灵数量 `f[K][N][M]`

最少耗费体力 `f[K][N][m]=f[K][N][M]`



- **潜水员**

费用至少达到最小值

求价值的最小值



不超过

`f[0,j,k]=0`

恰好

`f[0,0,0]=0`

`f[0,j,k]=INF/-INF` 不合法



（1）状态表示   `f[i,j,k]`

集合：所有从前`i`个物品中选，且氧气含量至少是`j`，氮气含量至少是`k`的所有选法

属性：最小值

（2）状态计算
$$
f[i][j][k]=min(f[i-1][j][k],f[i-1][j-v_1][k-v_2]+w_i)
$$


动态规划的体积（代价）表述

（1）体积最多是`j`

全部初始化成0，`V>=0`

（2）体积恰好是`j`

`f[0]=0`，`f[i]=INF`，`V>=0`

（3）体积至少是`j`

`f[0]=0`，`f[i]=INF`



###### 模板代码

```c++
#include<iostream>

using namespace std;

const int N = 110;

int n,V,M;
int f[N][N];

int main(){
    cin >> n >> V >> M;

    for(int i=0;i<n;i++){
        int v,m,w;
        cin >> v >> m >> w;
        for(int j=V;j>=v;j--){
            for(int k=M;k>=m;k--){
                f[j][k]=max(f[j][k],f[j-v][k-m]+w);
            }
        }
    }

    cout << f[V][M] << endl;

    return 0;
}
```



### 具体方案问题

###### 描述

求具体方案和方案数



###### 原理

**1、求方案数**
$$
f[i][j]=max(f[i-1][j],f[i-1][j-v_i]+w_i)\\
g[i][j] 表示f[i][j]取最大值的方案数\\
左边大~~g[i][j]=g[i-1][j]\\
右边大~~g[i][j]=g[i-1][j-v_i]\\
左右一样大~~g[i][j]=g[i-1][j]+g[i-1][j-v_i]
$$


- **数字组合**

01背包

把每个数看成是一个物品，`Ai`看成是体积

目标：求出总体积恰好为`M`的方案数

（1）状态表示  `f[i,j]`

集合：所有只从前`i`个物品中选，且总体积恰好是`j`的方案的集合

属性：数量

（2）状态计算
$$
f[i][j]=f[i-1][j]+f[i-1][j-v_i]
$$


- **买书**

完全背包

（1）状态表示  `f[i,j]`

集合：所有只从前`i`个物品中选，且总体积恰好是`j`的方案的集合

属性：数量

（2）状态计算
$$
f[i][j]=f[i-1][j]+\Sigma_{k=1}^{s_i} f[i-1][j-v_i*k]\\
=f[i-1][j]+f[i][j-v]
$$




- **货币系统**

完全背包



- **货币系统（harder）**

完全背包+贪心

性质1：`a1,a2,...,an`一定都可以被表达出来

性质2：在最优解中，`b1,b2,..,bm`，一定都是从`a1,a2,...,an`中选择的

性质3：`b1,b2,...,bm`一定不能被其他`bi`表示出来



**2、求具体方案**

对应图论的最短路问题求最短路径

1、不能状态压缩

2、反推状态来源（只取一个，还是多个都行）



字典序最小--->贪心

某个物品

只能选----->必选

只能不选----->必不选

可选，可不选----->必选



- **机器分配**

多重背包



###### 模板代码

求方案数

```c++
#include<iostream>
#include<cstring>

using namespace std;

const int N = 1010,MOD = 1e9+7;

int n,m;
int f[N],g[N];

int main(){
    cin >> n >> m;

    memset(f,-0x3f,sizeof f);

    f[0]=0;

    g[0]=1;

    for(int i=0;i<n;i++){
        int v,w;
        cin >> v >> w;

        for(int j=m;j>=v;j--){
            int maxv=max(f[j],f[j-v]+w);
            int cnt=0;
            if(maxv==f[j]) cnt+=g[j];
            if(maxv==f[j-v]+w) cnt+=g[j-v];
            g[j]=cnt % MOD;
            f[j]=maxv;
        }
    }

    int res=0;
    for(int i=0;i<=m;i++) res=max(res,f[i]);
    int cnt=0;
    for(int i=0;i<=m;i++) if(f[i]==res) cnt=(cnt+g[i])%MOD;

    cout << cnt << endl;

    return 0;
}
```



求具体方案

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1010;

int n,m;
int f[N][N];
int v[N],w[N];

int main(){
    cin >> n >> m;

    for(int i=1;i<=n;i++){
        cin >> v[i] >> w[i];
    }

    for(int i=n;i>=1;i--){
        for(int j=0;j<=m;j++){
            f[i][j]=f[i+1][j];
            if(j>=v[i]){
                f[i][j]=max(f[i][j],f[i+1][j-v[i]]+w[i]);
            }
        }
    }

    int j=m;

    for(int i=1;i<=n;i++){
        if(j>=v[i] && f[i][j]==f[i+1][j-v[i]]+w[i]){
            cout << i << " ";
            j-=v[i];
        }
    }

    return 0;
}
```



## DP模型

### 线性DP

###### 描述

枚举顺序是一个线性的顺序

包括背包问题，数字三角形问题



###### 原理

**1、数字三角形（路径DP）**

（1）状态表示 `f[i,j]`

集合：所有从起点走到`（i，j）`的路径

属性：最大值

（2）状态计算

状态可以划分为来自左上方`f[i-1,j-1]+a[i,j]`和右上方`f[i-1,j]+a[i,j]`
$$
f[i,j]=max(f[i-1,j-1]+a[i,j],f[i-1,j]+a[i,j])
$$



- **摘花生**

数字三角形

（1）状态表示  `f[i,j]`

集合：所有从`(1,1)`走到`(i,j)`的路线

属性：最大值

（2）状态计算

划分依据————“最后”
$$
f[i][j]=max(f[i-1][j],f[i][j-1])+w[i][j]
$$


- **最低通行费**

数字三角形

（1）状态表示  `f[i,j]`

集合：所有从`(1,1)`走到`(i,j)`的路线

属性：最小值

（2）状态计算

划分依据————“最后”
$$
f[i][j]=min(f[i-1][j],f[i][j-1])+w[i][j]
$$


- **方格取数**

摘花生

走两次

（1）状态表示  `f[i1,j1,i2,j2]--->f[k,i1,i2]`（只有i1+j1=i2+j2=k时，路线才可能重合）

集合：所有从`(1,1),(1,1)`走到`(i1,k-i1),(i2,k-i2)`的路线

属性：最大值

（2）状态计算

划分依据————“最后”

`f[k,i1,i2]`可以被划分为四种状态，同下，同右，一下一右

同时还需要检查`i1==i2`是否成立，成立，则只用加一次`w[i][j]`
$$
f[k][i_1][i_2]=max(f[k-1][i_1-1][i_2-1],f[k-1][i_1][i_2],f[k-1][i_1-1][i_2],f[i_1][i_2-1])+w[i_1][j_1]+(w[i_2][j_2],i_1!=i_2)
$$


- **k取方格数**

方格取数

最小费用流

DP可以转换为最短路问题

当图是拓扑图时（有向无环图DAG），最短路问题也可以转换为DP



**2、最长上升子序列（LIS）（序列DP）**

（1）状态表示 `f[i]`

集合：所有以第i个数结尾的上升子序列

属性：最大值

（2）状态计算

状态可以划分为来自以第k个数结尾的子序列的长度`f[k]`加上1的最大值
$$
f[i]=max(f[k]+1)~~,k=0,1,...,i-1
$$





- **怪盗基德的滑翔翼**

LIS

选定点和方向后，问题转化为了一个双向LIS问题



- **登山**

怪盗基德

条件1：按照编号递增的顺序来浏览 ---->必须是子序列

条件2：相邻两个景点不能相同

条件3：一旦开始下降，就不能上升了

目标：求最多能浏览多少景点

选定一个点，将双向LIS相加求最值



- **合唱队形**

登山

登山问题的对偶问题



- **友好城市**

LIS

条件1：每个城市上只能建立一座桥
条件2：所有的桥与桥之间不能相交

排序一端，求另一端的LIS



- **最大上升子序列和**

LIS

LIS属性变成和的最大值



- **拦截导弹**

LIS+贪心

反链定理、`Dilworth`定理

贪心流程：

从前往后扫描每一个数，对于每个数

情况1：如果现有的子序列的结尾都小于当前数，则创建新子序列

情况2：将当前数放到结尾大于等于它的最小的子序列后面

1、如何证明两个数相等？ A>=B,B>=A

A表示贪心算法得到的序列个数；B表示最优解

B<=A

A<=B  调整法 



- **导弹防御系统**

拦截导弹+DFS

贪心流程：

从前往后扫描每一个数，对于每个数

上升防御系统

情况1：如果现有的子序列的结尾都小于当前数，则创建新子序列

情况2：将当前数放到结尾大于等于它的最小的子序列后面

下降防御系统

情况1：如果现有的子序列的结尾都小于当前数，则创建新子序列

情况2：将当前数放到结尾大于等于它的最小的子序列后面

涉及决策（暴搜/DP）

DFS+DP

DFS求最小步数（记一个全局最小值/迭代加深）



- **最长公共上升子序列**

LIS+LCS

（1）状态表示  `f[i,j]`

集合：所有由第一个序列的前i个字母，第二个序列的前j个字母构成，且以`b[j]`结尾的公共上升子序列

属性：最大值

（2）状态计算

所有包含`a[i]`的公共上升子序列`f[i,k]+1`和所有不包含`a[i]`的公共上升子序列`f[i-1,j]`



**3、最长公共子序列（LCS）（序列DP）**

（1）状态表示  `f[i,j]`

集合：所有由第一个序列的前`i`个字母出现的，且第二个序列的前`j`个字母出现的公共子序列

属性：最大值

（2）状态计算

可以划分为第i个字母和第j个字母是否包含在最长公共子序列中

包括00，01，10，11四种可能

`f[i-1,j-1],f[i-1,j],f[i,j-1],f[i-1,j-1]+1`
$$
f[i][j]=max(f[i][j-1],f[i-1][j],(f[i-1][j-1]+1~~a[i]==b[j]))
$$




###### 模板代码

数字三角形

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N=510,INF=1e9;

int n;
int a[N][N];
int f[N][N];

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            scanf("%d",&a[i][j]);
        }
    }

    for(int i=0;i<=n;i++){
        for(int j=0;j<=i+1;j++){
            f[i][j]=-INF;
        }
    }

    f[1][1]=a[1][1];

    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            f[i][j]=max(f[i-1][j-1]+a[i][j],f[i-1][j]+a[i][j]);
        }
    }

    int res=-INF;
    for(int i=1;i<=n;i++){
        res=max(res,f[n][i]);
    }

    printf("%d\n",res);

    return 0;
}
```

最长上升子序列

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;

int n;
int a[N],f[N];

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    for(int i=1;i<=n;i++){
        f[i]=1;
        for(int j=1;j<i;j++){
            if(a[j]<a[i]) f[i]=max(f[i],f[j]+1);
        }
    }

    int res=0;

    for(int i=1;i<=n;i++) res=max(res,f[i]);

    printf("%d\n",res);

    return 0;
}
```

最长公共子序列

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;

int n,m;
char a[N],b[N];
int f[N][N];

int main(){
    scanf("%d%d",&n,&m);

    scanf("%s%s",a+1,b+1);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j]=max(f[i-1][j],f[i][j-1]);
            if(a[i]==b[j]) f[i][j]=max(f[i][j],f[i-1][j-1]+1);
        }
    }

    printf("%d\n",f[n][m]);

    return 0;
}
```



### 区间DP

###### 描述

状态表示的是一个区间

###### 原理

合并石子

（1）状态表示 `f[i,j]`

集合：所有将从第`i`堆石子到第`j`堆石子合并成一堆石子的合并方式

属性：最小值

（2）状态计算

可以以最后一次合并的分界线进行划分`f[i,k]+f[k+1,j]`
$$
f[i][j]=min(f[i][k]+f[k+1][j]+sum[j]-sum[i-1])~~k=i,i+1,...,j-1
$$


###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =310;

int n;
int s[N];
int f[N][N];

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&s[i]);

    for(int i=1;i<=n;i++) s[i]=s[i-1]+s[i];

    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int l=i,r=i+len-1;
            f[l][r]=1e8;
            for(int k=l;k<r;k++){
                f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]+s[r]-s[l-1]);
            }
        }
    }

    printf("%d\n",f[1][n]);

    return 0;
}
```



### 计数类DP

###### 描述



###### 原理



###### 模板代码

```

```



### 数位统计DP

###### 描述

统计某个数字出现了多少次（不同位数出现算两次）

###### 原理

分情况讨论

``[a,b],0-9`

`count(n,x)` ，`1-n`中`x`出现的次数
$$
res=count(b,x)-count(a-1,x)
$$
以1为例

`n=abcdefg`

枚举1在每一位上出现的次数

枚举1在第四位上出现的次数

`1<=xxx1yyy<=abcdefg`

（1）`xxx=000-abc-1,yyy=000-999,abc*1000`

（2）`xxx=abc`

​			（2.1）`d<1,abc1yyy>abc0efg,0`

​			（2.2）`d=1,yyy=000-efg,efg+1`

​			（2.3）`d>1,yyy=000-999,1000`



枚举0在第四位上出现的次数

`1<=xxx0yyy<=abcdefg`

（1）`xxx=001-abc-1,yyy=000-999,abc*1000`

（2）`xxx=abc`

​			（2.1）`d<1,abc1yyy>abc0efg,0`

​			（2.2）`d=1,yyy=000-efg,efg+1`

​			（2.3）`d>1,yyy=000-999,1000`



###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int get(vector<int> num,int l,int r){
    int res=0;
    for(int i=l;i>=r;i--){
        res=res*10+num[i];
    }
    return res;
}

int power10(int x){
    int res=1;
    while(x--) res*=10;
    return res;
}

int count(int n,int x){
    if(!n) return 0;

    vector<int> num;

    while(n){
        num.push_back(n%10);
        n/=10;
    }

    n=num.size();

    int res=0;

    for(int i=n-1-!x;i>=0;i--){
        if(i<n-1){
            res+=get(num,n-1,i+1)*power10(i);
            if(!x) res-=power10(i);
        }

        if(num[i]==x) res+=get(num,i-1,0)+1;
        else if(num[i]>x) res+=power10(i);
    }

    return res;
}

int main(){
    int a,b;

    while(cin >> a >> b,a||b){
        if(a>b) swap(a,b);
        for(int i=0;i<10;i++){
            cout << count(b,i)-count(a-1,i) << ' ';
        }
        cout << endl;
    }

    return 0;
}
```



### 状态机模型

###### 描述

描述一系列有序的状态转换

###### 原理

- **大盗阿福**

（1）状态表示   `f[i][0/1]`

集合：抢劫前`i`个店铺的选法（0表示没抢，1表示抢了）

属性：最大值

（2）状态计算
$$
f[i]=max(f[i-1],f[i-2]+w_i)\\
----------------\\
f[i][0]=max(f[i-1][0],f[i-1][1])\\
f[i][1]=f[i-1][0]+w_i
$$


- **股票买卖**

（1）状态表示   `f[i][j][0/1]`

集合：前`i`天完成了`j`次交易的选法（0表示无货，1表示有货）

属性：最大值

（2）状态计算
$$
f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]+w_i)\\
f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][0]-w_i)
$$


- **股票买卖（harder）**

（1）状态表示   `f[i][0/1/2]`

集合：前`i`天完成交易的选法（0表示有货，1表示无货且经过1天，2表示无货且经过大于等于2天）

属性：最大值

（2）状态计算
$$
f[i][0]=max(f[i-1][0],f[i-1][2]-w_i)\\
f[i][1]=f[i-1][0]+w_i\\
f[i][2]=max(f[i-1][1],f[i-1][2])
$$


- **设计密码**

KMP+状态机



###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 100010, INF=0x3f3f3f3f ;

int n;
int w[N],f[N][2];

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i=1;i<=n;i++) scanf("%d",&w[i]);

        f[0][0]=0,f[0][1]=-INF;

        for(int i=1;i<=n;i++){
            f[i][0]=max(f[i-1][0],f[i-1][1]);
            f[i][1]=f[i-1][0]+w[i];
        }

        printf("%d\n",max(f[n][0],f[n][1]));
            
    }

    return 0;
}
```



### 状态压缩DP

###### 描述

将状态用二进制数表示



###### 原理

**1、棋盘式（基于连通性）DP**

- **蒙德里安的梦想**

$$
f[i][j]+=f[i-1][k]\\
j \& k==0~~且~~j|k不存在连续奇数个0
$$




- **骑士**

九宫格形状

（1）状态表示   `f[i,j,s]`

集合：所有只摆在前`i`行，已经摆了`j`个国王，并且第`i`行摆放状态是`s`的所有方案的集合

属性：数量

（2）状态计算

1、第`i-1`行内部不能有两个`1`相邻

2、第`i-1`行和第`i`行之间也不能相互攻击到

`a`表示第`i-1`行状态，`b`表示第`i`行状态

（1）`(a&b)==0`

（2）`(a|b)`不能有相邻`1`

已经摆完前`i`行，并且第`i`排状态是`a`，第`i-1`排状态是`b`，已经摆了`j`个国王的所有方案   `f[i,j,a]`

已经摆完前`i-1`行，并且第`i-1`排状态是`b`，已经摆了`j-cnt(a)`个国王的所有方案   `f[i-1,j-count(a),b]`
$$
f[i][j][a]=\Sigma_{b合法} f[i-1][j-count(a)][b]
$$




- **玉米田**

十字形状

（1）状态表示  `f[i,s]`

集合：所有摆完前`i`行，并且第`i`行摆放状态是`s`的所有方案的集合

属性：数量

（2）状态计算

`a`表示第`i-1`行状态，`b`表示第`i`行状态

（1）`(a&b)==0`

（2）`a,b`不能有相邻`1`

已经摆完前`i`行，并且第`i`排状态是`a`，第`i-1`排状态是`b`的所有方案   `f[i,a]`

已经摆完前`i-1`行，并且第`i-1`排状态是`b`的所有方案   `f[i-1,b]`
$$
f[i][a]=\Sigma_{b合法} f[i-1][b]
$$




- **炮兵阵地**

加长十字形状

（1）状态表示  `f[i,j,k]`

集合：所有摆完前`i`行，并且第`i-1`行摆放状态是`j`，第`i`行摆放状态是`k`的所有方案的集合

属性：最大值

（2）状态计算

`a`表示第`i-2`行状态

`b`表示第`i-1`行状态

`c`表示第`i`行状态

（1）`((a&b)|(a&c)|(b&c))==0`

（2）`((g[i-1]&a)|(g[i]&b))==0`

已经摆完前`i`行，并且第`i`排状态是`a`，第`i-1`排状态是`b`的所有方案   `f[i,a]`

已经摆完前`i-1`行，并且第`i-1`排状态是`b`的所有方案   `f[i-1,b]`



**2、集合式DP**

- **最短Hamilton路径**

（1）状态表示 `f[i,j]`

集合：所有从0走到`j`，走过的所有点是`i`的所有路径

属性：最小值

（2）状态计算

划分为倒数第二点的路径长度

`0-k-j,k=0,1,..,n-1`
$$
f[i][j]=min(f[i-\{j\}][k]+a[k][j])~~k=0,1,...,n-1
$$



- **愤怒的小鸟**

由题中抛物线性质可知两个点便可确定一条抛物线

`n`个点可以确定`n^2`个抛物线

重复覆盖问题：愤怒的小鸟

精确覆盖问题：`N`皇后，数独问题

`Dancing Links`可以极大地优化这两个问题的`DFS`过程

```c++
void dfs(int state,int cnt) //state存储当前哪些列已被覆盖
{
	if(state已经包含所有列了) ans=min(ans,cnt),return;
    
    int res=INF;
	
	任选没有被覆盖的一列x
	枚举所有能覆盖x的抛物线
		更新一下state--->new_state
		dfs(new_state,cnt+1);
		还原state
}

//f[state]  存一下已计算的state，dp优化方案
//x,path[x][j],new_state=state|path[x][j]
```



###### 模板代码

蒙德里安的梦想

```c++
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N =12,M=1<<N;

int n,m;
int f[N][M];
bool st[M];

int main(){
    while(cin >> n >>m,n||m){
        memset(f,0,sizeof f);

        for(int i=0;i<1<<n;i++){
            st[i]=true;
            int cnt=0;
            for(int j=0;j<n;j++){
                if(i>>j&1){
                    if(cnt&1)st[i]=false;
                    cnt=0;
                }
                else cnt++;
            }

            if(cnt&1)st[i]=false;
        }

        f[0][0]=1;
        for(int i=1;i<=m;i++){
            for(int j=0;j<1<<n;j++){
                for(int k=0;k<1<<n;k++){
                    if((j&k)==0 && st[j|k]){
                        f[i][j]+=f[i-1][k];
                    }
                }
            }
        }

        cout << f[m][0] << endl;
    }

    return 0;
}
```

最短Hamilton路径

```c++
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 20, M=1<<N;

int n;
int w[N][N];
int f[M][N];

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> w[i][j];
        }
    }

    memset(f,0x3f,sizeof f);
    f[1][0]=0;

    for(int i=0;i<1<<n;i++){
        for(int j=0;j<n;j++){
            if(i>>j&1){
                for(int k=0;k<n;k++){
                    if((i-(1<<j))>>k&1){
                        f[i][j]=min(f[i][j],f[i-(1<<j)][k]+w[k][j]);
                    }
                }
            }
        }
    }

    cout << f[(1<<n)-1][n-1] << endl;

    return 0;
}
```



### 树形DP

###### 描述

在树形结构（非线性结构）中进行动态规划

###### 原理

没有上司的舞会

（1）状态表示  `f[u,0/1]`

集合：所有以`u`为根的子树中选择，并不选`u`这个点的方案

​			所有以`u`为根的子树中选择，并选`u`这个点的方案

属性：最大值

（2）状态计算
$$
s_i是u的子节点\\
f[u][0]+=max(f[s_i][0],f[s_i][1])\\
f[u][1]+=f[s_i][0]
$$


###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N =6010;

int n;
int happy[N];
int h[N],e[N],ne[N],idx;
int f[N][2];
bool has_father[N];

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

void dfs(int u){
    f[u][1]=happy[u];

    for(int i=h[u];i!=-1;i=ne[i]){
        int j=e[i];
        dfs(j);

        f[u][0]+=max(f[j][0],f[j][1]);
        f[u][1]+=f[j][0];
    }
}

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&happy[i]);

    memset(h,-1,sizeof h);

    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);

        has_father[a]=true;
        add(b,a);
    }

    int root=1;
    while(has_father[root]) root++;

    dfs(root);

    printf("%d\n",max(f[root][0],f[root][1]));

    return 0;
}
```



### 记忆化搜索

###### 描述

递归实现的动态规划（好想，好写，比循环运行的慢些，可能会栈溢出）

###### 原理

滑雪

（1）状态表示  `f[i,j]`

集合：所有从`(i,j)`开始滑的路径

属性：最大值

（2）状态计算

状态来源于四个方向



###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=310;

int n,m;
int h[N][N];
int f[N][N];

int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};

int dp(int x,int y){
    int &v=f[x][y];
    if(v!=-1) return v;

    v=1;
    for(int i=0;i<4;i++){
        int a=x+dx[i],b=y+dy[i];
        if(a>=1 && a<-n && b>=1 && b<= m && h[a][b]<h[x][y]){
            v=max(v,dp(a,b)+1);
        }
    }

    return v;
}

int main(){
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&h[i][j]);
        }
    }

    memset(f,-1,sizeof f);

    int res=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            res=max(res,dp(i,j));
        }
    }

    printf("%d\n",res);

    return 0;
}
```

