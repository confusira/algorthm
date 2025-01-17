# 动态规划

###### 原理

动态规划问题可以从状态表示和状态计算来入手

（1）状态表示：状态用几个变量来表示（集合的表示）

集合

属性

（2）状态计算：每一个状态怎么计算出来（集合的划分）

（3）动态规划的优化问题：

往往是对动态规划的代码或者方程做一个等价变形



## 背包问题

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

每件物品允许使用有限次



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



###### 模板代码

```

```



## DP模型

### 线性DP





### 区间DP





### 计数类DP





### 数位统计DP



### 状态压缩DP



### 树形DP



### 记忆化搜索