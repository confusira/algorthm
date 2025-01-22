# 算法思想



[TOC]



## 排序

### 快速排序

###### 基于分治思想

###### 步骤

（1）确定分界点（q[l]、q[(l+r)/2]、q[r]、随机）

**（2）调整区间**

​			暴力做法：

​			1、a[]、b[]

​			2、<= a[]、>b[]

​			3、a[]、b[]放回q[]

​			优美做法：

​			1、双指针i,j

​			2、i左，遇到大于停下、j右，遇到小于等于停下

​			3、交换值、i、j继续前进，直至相遇

（3）递归处理（左右两段）



###### 模板代码

```c++
void quicksort(int q[],int l,int r){
     if(l==r) return;

     int x=q[l],i=l-1,j=r+1;

     while(i<j){
         do i++; while(q[i]<x);
         do j--; while(q[j]>x);
         if(i<j) swap(q[i],q[j]);
     }

     quicksort(q,l,j);
     quicksort(q,j+1,r);
 }
```



### 归并排序

###### 基于分治思想

###### 步骤

（1）确定分界点（mid=(l+r)/2）

（2）递归排序左右

（3）**归并**————合二为一

​				双指针算法



###### 模板代码

```c++
void mergesort(int q[],int l,int r){
    if(l>=r) return;

    int mid=l+r>>1;
    
    mergesort(q,l,mid);
    mergesort(q,mid+1,r);

    int k=0,i=l,j=mid+1;
    while(i<=mid && j<=r){
        if(q[i]<=q[j]) tmp[k++]=q[i++];
        else tmp[k++]=q[j++];
    }

    while(i<=mid) tmp[k++]=q[i++];
    while(j<=r) tmp[k++]=q[j++];

    for(i=l,j=0;i<=r;i++,j++) q[i]=tmp[j];
}
```



## 二分

### 整数二分

###### 本质

左右两区间具有不同的某一性质，可以通过二分去寻找这一性质的边界



###### 特性

有单调性一定可以二分

二分不一定要有单调性



###### 模板代码

```c++
//区间[l,r]划分成[l,mid]和[mid+1,r]
int bsearch_1(int l,int r){
    while(l<r){
        int mid=l+r>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    return 1;
}

//区间[l,r]划分成[l,mid-1]和[mid,r]
int bsearch_2(int l,int r){
    while(l<r){
        int mid=l+r+1>>1;
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    return 1;
}
```



### 浮点数二分

###### 经验技巧

如有保留位数，比保留位数多2

如保留四位小数 取e-6



###### 模板代码

```c++
while(r-l>1e-6){
    double mid=(l+r)/2;
        
    if(check(mid))r=mid;
    else l=mid;
}

for(int i=0;i<100;i++){
    double mid=(l+r)/2;
        
    if(check(mid))r=mid;
    else l=mid;
}
//区间长度为1/(2^100)
```



## 高精度

小整数：n<=1e9

大整数：位数<=1e6



### 大整数加大整数

###### 步骤

（1）反向存储、方便进位

（2）每一位的计算：A[i]+B[i]+进位

（3）反向输出



###### 模板代码

```c++
vector<int> add(vector<int> &A,vector<int> &B){
    vector<int> C;

    int t=0;
    for(int i=0;i<A.size() || i<B.size();i++){
        if(i<A.size()) t+=A[i];
        if(i<B.size()) t+=B[i];
        C.push_back(t % 10);
        t/=10;
    }

    if(t) C.push_back(t);
    return C;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    string a,b;

    cin >> a >> b;

    vector<int> A,B;
    
    //反向存储
    for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');
    for(int i=b.size()-1;i>=0;i--) B.push_back(b[i]-'0');

    auto C=add(A,B);
    
    //反向输出
    for(int i=C.size()-1;i>=0;i--) cout << C[i];
    cout << endl;

    return 0;
}
```



### 大整数减大整数

###### 步骤

（1）反向存储、方便进位

（2）每一位的计算：A[i]-B[i]-借位

（3）反向输出



###### 模板代码

```c++
//比较A、B大小
bool cmp(vector<int> &A,vector<int> &B){
    if(A.size()!=B.size()) return A.size() > B.size();
    for(int i=0;i<A.size();i++) {
        if (A[i] != B[i]) return A[i] > B[i];
    }
    return true;
}

vector<int> sub(vector<int> &A,vector<int> &B){
    vector<int> C;

    for(int i=0,t=0;i<A.size();i++){
        t=A[i]-t;
        if(i<B.size()) t-=B[i];
        C.push_back((t+10)%10);
        if(t<0) t=1;
        else t=0;
    }

    while(C.size()>1 && C.back()==0) C.pop_back();  //去除多余的零

    return C;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    string a,b;

    cin >> a >> b;

    vector<int> A,B;

    for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');
    for(int i=b.size()-1;i>=0;i--) B.push_back(b[i]-'0');

    if(cmp(A,B)){
        auto C=sub(A,B);
        for(int i=C.size()-1;i>=0;i--) cout << C[i];
        cout << endl;
    }else{
        auto C=sub(B,A);
        cout << "-";
        for(int i=C.size()-1;i>=0;i--) cout << C[i];
        cout << endl;
    }

    return 0;
}
```



### 大整数乘小整数



###### 模板代码

```c++
vector<int> mul(vector<int> &A,int b){
    vector<int> C;

    int t=0;
    for(int i=0;i<A.size()||t;i++){
        if(i<A.size()) t+=A[i]*b;
        C.push_back(t%10);
        t/=10;
    }

    return C;
}
```



### 大整数除小整数



###### 模板代码

```c++
vector<int> div(vector<int> &A,int b,int &r){
    vector<int> C;

    r=0;
    for(int i=A.size()-1;i>=0;i--){
        r=r*10+A[i];
        C.push_back(r/b);
        r%=b;
    }

    reverse(C.begin(),C.end());
    while(C.size()>1 && C.back()==0) C.pop_back();

    return C;
}
```



## 前缀和与差分

### 一维前缀和

###### 作用

查询在[l,r]上的和，时间复杂度为O(n)->O(1)



###### 原理

如何求解前缀和：
$$
S_n~=~a_1~+~...~+~a_n\\
S_0=0\\
\\
S_{[l,r]}~=S_r~-~S_{l-1}
$$

###### 模板代码

```c++
int main(){
    //ios::sync_with_stdio(0) 取消cin与标准输入输出的同步
    //优点 传输更快
    //缺点 不允许使用scanf,printf
    
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    s[0]=0;
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];

    while(m--){
        int l,r;
        scanf("%d%d",&l,&r);

        printf("%d\n",s[r]-s[l-1]);
    }

    return 0;
}
```



### 二维前缀和

###### 作用

计算矩阵里的一个小矩形面积

###### 原理

如何求解二维前缀和
$$
S_{i,j}~=S_{i-1,j}~+~S_{i,j-1}~-~S_{i-1,j-1}~+~a_{i,j}\\
S_{0,0}=0\\
S_{[(x_1,y_1),(x_2,y_2)]}~=~S_{x_2,y_2}~-~S_{x_2,y_1-1}~-~S_{x_1-1,y_2}~+~S_{x_1-1,y_1-1}
$$


###### 模板代码

```c++
int main(){
    scanf("%d%d%d",&n,&m,&q);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    s[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+a[i][j];
        }
    }

    while(q--){
        int x1,y1,x2,y2;

        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

        printf("%d\n",s[x2][y2]-s[x2][y1-1]-s[x1-1][y2]+s[x1-1][y1-1]);
    }
    
    return 0;
}

```



### 一维差分

###### 作用

数组在[l,r]上同时加上C O(n)->O(1)



###### 原理

$$
a_0~=~0\\
b_i~=~a_i~-~a_{i-1}\\
[l,r]上+c\\
b_l+c~~and~~ b_{r+1}-c
$$



###### 模板代码

```c++
void insert(int l,int r,int c){
    b[l]+=c;
    b[r+1]-=c;
}

int main(){
    scanf("%d%d",&n,&m);
    
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    
    for(int i=1;i<=n;i++) insert(i,i,a[i]);
    
    while(m--){
        int l,r,c;
        
        scanf("%d%d%d",&l,&r,&c);
        
        insert(l,r,c);
    }
    
    for(int i=1;i<=n;i++) b[i]+=b[i-1];
    
    for(int i=1;i<=n;i++) printf("%d ",b[i]);
    
    return 0;
}
```



### 二维差分

###### 作用

给矩阵中的一个子矩阵范围加上C

###### 原理

$$
(x_1,y_1)~到~(x_2,y_2)\\
b_{x_1,y_1}+=c~and~b_{x_1,y_2+1}-=c~and~b_{x_2+1,y_1}-=c~and~b_{x_2+1,y_2+1}+=c
$$



###### 模板代码

```c++
void insert(int x1,int y1,int x2,int y2,int c){
    b[x1][y1]+=c;
    b[x1][y2+1]-=c;
    b[x2+1][y1]-=c;
    b[x2+1][y2+1]+=c;
}

int main(){
    scanf("%d%d%d",&n,&m,&q);
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            insert(i,j,i,j,a[i][j]);
    
    while(q--){
        int x1,y1,x2,y2,c;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&c);
        
        insert(x1,y1,x2,y2,c);
    }
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            printf("%d ",b[i][j]);
        printf("\n");
    }
    
    return 0;
}
```



## 双指针

###### 核心思想

将暴力算法的全排列限制在特定有序性中

O(n^2)->O(n)

先写暴力算法，观察两个指针之间的移动是否存在一定单调性，如果有，则可以使用双指针算法



###### 代码模板

```c++
for(int i=0,j=0;i<n;i++){
	while(j<i && check(i,j)) j++;
	
	//具体逻辑
}
```



### 双序列双指针



### 单序列双指针



## 位运算

### 求n的二进制表示中第K位数

###### 思路

（1）先把第K位移到最后一位

（2）看个位是几



###### 模板代码

```c++
int res = n >> k & 1;
```



### lowbit(x)

###### 作用

返回x的最后一位1
$$
lowbit(1010)~=~10
$$


###### 模板代码

```c++
int lowbit(int x){
    return x & (-x);
}
```



## 离散化(整数)

###### 原理

值域很大 0-1e9，个数少1e5

需要以这些值作为下标

将1e5个数映射到0-n-1上



###### 注意点

（1）这些值中可能有重复元素（去重）

（2）如何算出离散后的值（二分）



###### 模板代码

```c++
//去重
vector<int> alls;
sort(alls.begin(),alls.end());
alls.erase(unique(alls.begin(),alls.end()),alls.end());

//二分
int find(int x){
    int l=0,r=alls.size()-1;
    while(l<r){
        int mid=l+r>>1;
        if(alls[mid]>=x) r=mid;
        else l=mid+1;
    }
    
    return r+1;//映射到1-n
}
```







## 区间合并





## 贪心算法

### 区间问题

###### 原理

如何证明

`ans=cnt  (1)ans<=cnt  (2)ans>=cnt`

1、区间选点

步骤：

（1）将每个区间按右端点从小到大排序

（2）从前往后依次枚举每个区间

​			如果当前区间中已经包含点，则直接pass

​			否则，选择当前区间的右端点



2、最大不相交区间数量

（1）将每个区间按右端点从小到大排序

（2）从前往后依次枚举每个区间

​			如果当前区间中已经包含点，则直接pass

​			否则，选择当前区间的右端点



3、区间分组

（1）将所有区间按左端点从小到大排序

（2）从前往后处理每个区间

​			判断能否将其放到某个现有的组中  `L[i]>max_r`

​					（2.1）如果不存在这样的组，则开新组，然后再将其放进去

​					（2.2）如果存在这样的组，将其放进去，再更新当前组的`max_r`



4、区间覆盖

（1）将所有区间按左端点从小到大排序

（2）从前往后依次枚举每个区间，在所有能覆盖start的区间中，选择右端点最大的区间，然后将start更新成右端点的最大值



###### 模板代码

区间选点、最大不相交区间数量

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1e5+10;

int n;
struct Range{
    int l,r;
    bool operator< (const Range &W)const{
        return r<W.r;
    } 
}range[N];

int main(){
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        range[i]={l,r};
    }

    sort(range,range+n);

    int res=0,ed=-2e9;

    for(int i=0;i<n;i++){
        if(range[i].l>ed){
            res++;
            ed=range[i].r;
        }
    }

    printf("%d\n",res);

    return 0;
}
```



区间分组

```c++
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int N=100010;

int n;
struct Range{
    int l,r;
    bool operator<(const Range &W)const{
        return l<W.l;
    } 
}range[N];

int main(){
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        range[i]={a,b};
    }

    sort(range,range+n);

    priority_queue<int,vector<int>,greater<int>> heap;

    for(int i=0;i<n;i++){
        auto r=range[i];
        if(heap.empty() || heap.top()>=r.l){
            heap.push(r.r);
        }
        else{
            int t=heap.top();
            heap.pop();
            heap.push(r.r);
        }
    }

    printf("%d\n",heap.size());
    
    return 0;
}
```



区间覆盖

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =100010;

int n;
struct Range{
    int l,r;
    bool operator<(const Range& W)const{
        return l<W.l;
    }
}range[N];

int main(){
    int st,ed;
    scanf("%d%d",&st,&ed);
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        range[i]={l,r};
    }

    sort(range,range+n);

    int res=0;
    bool success=false;
    for(int i=0;i<n;i++){
        int j=i,r=-2e9;
        while(j<n && range[j].l<=st){
            r=max(r,range[j].r);
            j++;
        }

        if(r<st){
            res=-1;
            break;
        }

        res++;

        if(r>=ed){
            success=true;
            break;
        } 

        st=r;

        i=j-1;
    }

    if(!success) res=-1;
    printf("%d\n",res);

    return 0;
}
```



### Huffman树

###### 原理



###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int main(){
    int n;
    scanf("%d",&n);

    priority_queue<int,vector<int>,greater<int>> heap;
    while(n--){
        int x;
        scanf("%d",&x);
        heap.push(x);
    }

    int res=0;
    while(heap.size()>1){
        int a=heap.top();heap.pop();
        int b=heap.top();heap.pop();
        res+=a+b;
        heap.push(a+b);
    }

    printf("%d\n",res);

    return 0;
}
```



### 排序不等式

###### 原理

调整法和反证法
$$
S_{顺}<S_{随意}<S_{逆}
$$
排队打水



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n;
int t[N];

int main(){
    scanf("%d",&n);

    for(int i=0;i<n;i++) scanf("%d",&t[i]);

    sort(t,t+n);

    LL res=0;
    for(int i=0;i<n;i++) res+=t[i]*(n-i-1);

    printf("%lld\n",res);

    return 0;
}
```



### 绝对值不等式

###### 原理

$$
|x_1-x|+|x_2-x|+...+|x_n-x|>=x_n+x_{n-1}+...-x_2-x_1
$$

货仓选址



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N =100010;

int n;
int a[N];

int main(){
    scanf("%d",&n);

    for(int i=0;i<n;i++) scanf("%d",&a[i]);

    sort(a,a+n);

    int res=0;

    for(int i=0;i<n;i++){
        res+=abs(a[i]-a[n/2]);
    }

    printf("%d\n",res);

    return 0;
}
```



### 推公式

###### 原理

牛牛叠罗汉

按照`wi+si`从小到大的顺序排，最大的危险系数一定是最小的



###### 模板代码

```c++
#include<iostream>
#include<algorithm>

using namespace std;

typedef pair<int,int> PII;

const int N =100010;

int n;
PII cow[N];

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int w,s;
        scanf("%d%d",&w,&s);
        cow[i]={w+s,w};
    }

    sort(cow,cow+n);

    int res=-2e9,sum=0;

    for(int i=0;i<n;i++){
        int w=cow[i].second,s=cow[i].first-w;
        res=max(res,sum-s);
        sum+=w;
    } 

    printf("%d\n",res);

    return 0;
}
```

