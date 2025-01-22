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



## DP模型

### 线性DP

###### 描述

枚举顺序是一个线性的顺序

包括背包问题，数字三角形问题



###### 原理

**1、数字三角形**

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



**2、最长上升子序列（LIS）**

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





- **导弹防御系统**

拦截导弹+DFS





- **最长公共上升子序列**

LIS+LCS





**3、最长公共子序列（LCS）**

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



### 状态压缩DP

###### 描述

将状态的整数表示看成是二进制数表示

###### 原理

蒙德里安的梦想
$$
f[i][j]+=f[i-1][k]\\
j \& k==0~~且~~j|k不存在连续奇数个0
$$
最短Hamilton路径

（1）状态表示 `f[i,j]`

集合：所有从0走到`j`，走过的所有点是`i`的所有路径

属性：最小值

（2）状态计算

划分为倒数第二点的路径长度

`0-k-j,k=0,1,..,n-1`
$$
f[i][j]=min(f[i-\{j\}][k]+a[k][j])~~k=0,1,...,n-1
$$


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

