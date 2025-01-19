# 动态规划

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

1、数字三角形

（1）状态表示 `f[i,j]`

集合：所有从起点走到`（i，j）`的路径

属性：最大值

（2）状态计算

状态可以划分为来自左上方`f[i-1,j-1]+a[i,j]`和右上方`f[i-1,j]+a[i,j]`
$$
f[i,j]=max(f[i-1,j-1]+a[i,j],f[i-1,j]+a[i,j])
$$


2、最长上升子序列

（1）状态表示 `f[i]`

集合：所有以第i个数结尾的上升子序列

属性：最大值

（2）状态计算

状态可以划分为来自以第k个数结尾的子序列的长度`f[k]`加上1的最大值
$$
f[i]=max(f[k]+1)~~,k=0,1,...,i-1
$$


3、最长公共子序列

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

`1<=xxx1yyy<=abcdefg`

（1）`xxx=000-abc-1,yyy=000-999,abc*1000`

（2）`xxx=abc`

​			（2.1）`d<1,abc1yyy>abc0efg,0`

​			（2.2）`d=1,yyy=000-efg,efg+1`

​			（2.3）`d>1,yyy=000-999,1000`



###### 模板代码

```

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



### 树形DP

###### 描述



###### 原理





###### 模板代码

```

```



### 记忆化搜索

###### 描述



###### 原理



###### 模板代码

```

```

