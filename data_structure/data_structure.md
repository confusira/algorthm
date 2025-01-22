# 数据结构

[TOC]



## 链表

###### 作用

1、单链表——>邻接表（存储树和图）

2、双链表——>优化某些问题



###### 原理

用两个数组模拟e[N],ne[N]

head表示头节点下标,e[N]装值，ne[N]装下标(,idx当前存储用到节点的位置)



###### 模板代码

单链表

```c++
const int N=1e6+10;

int head,e[N],ne[N],idx;

//初始化
void init(){
    head=-1;
    idx=0;
}

//将X插到头节点
void add_to_head(int x){
    e[idx]=x,ne[idx]=head,head=idx,idx++;
}

//将X插到下标为k的数后面
void add(int k,int x){
    e[idx]=x,ne[idx]=ne[k],ne[k]=idx,idx++;
}

//将k后面的点删除
void remove(int k){
    ne[k]=ne[ne[k]];
}

//遍历链表
for(int i=head;i!=-1;i=ne[i]) cout << e[i] << " ";
    
```



双链表

```c++
int e[N],l[N],r[N],idx;

//初始化
void init(){
    //0表示最左边节点，1表示最右边节点
    r[0]=1,l[1]=0;
    idx=2;
}

//在下标为K的右边插入X
void add(int k,int x){
    e[idx]=x,l[idx]=k,r[idx]=r[k],l[r[k]]=idx,r[k]=idx;
}

//在下标为K的左边插入X add(l[k],x)

//删除下标为K的点
void remove(int k){
    r[l[k]]=r[k],l[r[k]]=l[k];
}
```



## 栈

###### 模板代码

```c++
int stk[N],tt;

//入栈
int x;
stk[++tt]=x;

//出栈
tt--;

//判定栈空
if(tt>0){}
else{}

//栈顶
stk[tt];
```



### 单调栈

###### 模型

找左（右）最近的比它小（大）的数



###### 原理

与双指针思考方式类似(暴力->单调性优化)  缩小解空间

暴力：

for(i:0-n):for(j:i-0)

单调栈：

模拟栈

栈顶元素比当前元素大，绝对不可能是答案，将他推出栈中

每个元素只会进栈一次，出栈一次

O(n^2)->O(n)



###### 模板代码

```c++
const int N = 1e6+10;

int n;
int stk[N],tt;

int main(){
    cin >> n;
    
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        
        while(tt && stk[tt]>=x) tt--;
        if(tt) cout << stk[tt] << ' ';
        else cout << -1 << ' ';
        
        stk[++tt]=x;
    }
    
    cout << endl;
    
    return 0;
}
```



## 队列

###### 模板代码

```c++
int q[N],hh,tt=-1;

//插入
int x;
q[++tt]=x;
    
//弹出
hh++;
    
//判断为空
if(hh<=tt){}
else{}
    
//取队头元素
q[tt];
```



### 单调队列

###### 模型

求滑动窗口里的最小值（最大值）



###### 原理

与双指针思考方式类似

暴力->单调队列

O(n^2)->O(n)



###### 模板代码

```c++
const int N=1e6+10;

int n,k;

int a[N],q[N];

int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);

    int hh=0,tt=-1;
    for(int i=0;i<n;i++){
        if(hh<=tt && i-k+1> q[hh]) hh++;
        while(hh<=tt && a[q[tt]]>=a[i]) tt--;
        q[++tt]=i;
        if(i>=k-1) printf("%d ",a[q[hh]]);
    }
    printf("\n");

    return 0;
}
```



## 串

### KMP算法

###### 原理

与双指针思考方式类似

S[N],p[M]

暴力

for(i:1-n):for(j:1-m)

KMP

模式串自身的一个匹配性质

next[i]=j  等价于  p[1,j]=p[i-j+1,i]

O(mn)->O(m)



###### 模板代码

```c++
const int N=1e4+10,M=1e5+10;

int n,m;

char p[N],s[M];

int ne[N];

int main(){
    cin >> n >> p+1 >> m >> s+1;
    
    //求next过程
    for(int i=2,j=0;i<=m;i++){
        while(j && p[i]!=p[j+1]) j=ne[j];
        if(p[i]==p[j+1]) j++;
        ne[i]=j;
    }
    
    //匹配过程
    for(int i=1,j=0;i<=m;i++){
        while(j && s[i] != p[j+1]) j=ne[j];
        if(s[i]==p[j+1]) j++;
        if(j==n){
            //匹配成功
            j=ne[j];
        }
    }
    
    return 0;
}
```



## 树



### Trie树

###### 作用

高效地存储和查找字符串集合的数据结构



###### 原理

建立一个前缀树



###### 模板代码

```c++
#include<iostream>

using namespace std;

const int N=1e5+10;

int son[N][26],cnt[N],idx; //下标为0的点既是空节点，又是根节点
char str[N];

void insert(char str[]){
    int p=0;
    for(int i=0;str[i];i++){
        int u=str[i]-'a';
        if(!son[p][u]) son[p][u]=++idx;
        p=son[p][u];
    }

    cnt[p]++;
}

int query(char str[]){
    int p=0;
    for(int i=0;str[i];i++){
        int u=str[i]-'a';
        if(!son[p][u]) return 0;
        p=son[p][u];
    }

    return cnt[p];
}

int main(){
    int n;
    scanf("%d",&n);

    while(n--){
        char op[2];
        scanf("%s%s",op,str);
        if(op[0]=='I') insert(str);
        else printf("%d\n",query(str));
    }

    return 0;
}
```



### 并查集

###### 作用

（1）将两个集合合并

（2）询问两个元素是否在一个集合当中



###### 原理

暴力做法

belong[x]=a  O(n)   比较耗时

if(belong[x]==belong[y])  O(1)

优化方法：

用树的结构去维护集合，树根的编号就是集合的编号

一个集合内每一个节点都配备一个父节点 p[x]

（1）判断树根：if(p[x]==x)

（2）如何求x的集合编号：while(p[x]!=x)

（3）如何合并两个集合：p[x]=y

优化：

（1）求集合编号的时候，让搜索路径上的所有点指向根节点（路径压缩）

（2）按值合并

维护额外信息方法：

增加更新额外变量（连通块问题）



###### 模板代码

重点

p[x]及初始化、find函数、合并与查询

```c++
#include<iostream>

using namespace std;

const int N=1e5+10;

int n,m;
int p[N];

int find(int x){ //返回x所在集合的编号+路径压缩
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++) p[i]=i;

    while(m--){
        char op[2];
        int a,b;
        scanf("%s%d%d",op,&a,&b);

        if(op[0]=='M') p[find(a)]=find(b);
        else{
            if(find(a)==find(b)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
```





### 堆

###### 作用

维护一个数据集合（堆排序等）

（1）插入一个数                           heap[++size]=x; up(size);

（2）求集合当中的最小值           heap[1];

（3）删除最小值                           heap[1]=heap[size--]; down(1);

（4）删除任意一个元素			   heap[k]=heap[size--]; down(k); up(k);

（5）修改任意一个元素			   heap[k]=x; down(k); up(k);



###### 原理

小根堆：根节点小于等于子节点  （大根堆完全相反）

（1）存储方式：一维数组->完全二叉树

根节点 x   左子节点 2*x  右子节点 2*x+1

（2）操作方式

down(x)：堆中某个值变大了（向下调整）

up(x)：堆中某个值变小了（向上调整）

（3）带映射关系的堆操作

ph:插入顺序到堆内属性（位置）的映射关系              hp:堆内属性（位置）到插入顺序的映射关系

heap_swap(a,b)



###### 模板代码

普通堆

```c++
#include<iostream>
#include<algorithm>

using namespace std;

const int N=1e5+10;

int n,m;
int h[N],size;

void down(int u){
    int t=u;
    if(u*2<=size && h[u*2]<h[t]) t=2*u;
    if(u*2+1<=size && h[u*2+1]<h[t]) t=2*u+1;
    if(u!=t){
        swap(h[u],h[t]);
        down(t);
    }
}

void up(int u){
    while(u/2 && h[u/2] > h[u]){
        swap(h[u/2],h[u]);
        u/=2;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    size=n;
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);

    for(int i=n/2;i;i--) down(i);  //建堆 O(nlogn)->O(n)

    while(m--){
        printf("%d ",h[1]);
        h[1]=h[size--];down(1);
    }
    return 0;
}
```

带映射关系的堆

```c++
int n,m;
int h[N],size;
int ph[N]; //插入顺序到堆内属性（位置）的映射
int hp[N]; //堆内属性（位置）到插入顺序的映射

void heap_swap(int a,int b){
    swap(ph[hp[a]],ph[hp[b]]);
    swap(hp[a],hp[b]);
    swap(h[a],h[b]);
}

void down(int u){
    int t=u;
    if(u*2<=size && h[u*2]<h[t]) t=2*u;
    if(u*2+1<=size && h[u*2+1]<h[t]) t=2*u+1;
    if(u!=t){
        heap_swap(u,t);
        down(t);
    }
}

void up(int u){
    while(u/2 && h[u/2] > h[u]){
        heap_swap(u/2,u);
        u/=2;
    }
}

int main(){
    int n,m=0;
    scanf("%d",&n);

    while(n--){
        char op[10];
        int k,x;

        scanf("%s",op);
        if(!strcmp(op,"I")){
            scanf("%d",&x);
            size++;
            m++;
            ph[m]=size,hp[size]=m;
            h[size]=x;up(size);
        }
        else if(!strcmp(op,"PM")) printf("%d\n",h[1]);
        else if(!strcmp(op,"DM")){
            heap_swap(1,size);size--;down(1);
        }  
        else if(!strcmp(op,"D")){
            scanf("%d",&k);
            k=ph[k];
            heap_swap(k,size);size--;down(k);up(k);
        }else{
            scanf("%d%d",&k,&x);
            k=ph[k];
            h[k]=x;down(k);up(k);
        }
    }

    return 0;
}
```

## Hash表

###### 原理

（1）Hash函数

x在1-1e9之间，hash(x)在1-1e5之间

hash(x)=x mod 1e5 在1-1e5之间

冲突解决：拉链法和开放寻址法

操作：插入、查找和删除（往往是打标记）

（2）存储结构分为开放寻址法和拉链法

（3）常用方法：字符串哈希方式



### 拉链法

###### 模板代码

```c++
#include<iostream>
#include<cstring>

using namespace std;

const int N=1e5+3;

int h[N],e[N],ne[N],idx;

void insert(int x){
    int k=(x%N+N)%N;  //正整数

    e[idx]=x;ne[idx]=h[k];h[k]=idx++;
}

bool find(int x){
    int k=(x%N+N)%N;
    for(int i=h[k];i!=-1;i=ne[i])
        if(e[i]==x) return true;
    
    return false;
}

int main(){
    int n;
    scanf("%d",&n);

    memset(h,-1,sizeof(h));

    while(n--){
        char op[2];
        int x;
        scanf("%s%d",op,&x);

        if(*op=='i') insert(x);
        else{
            if(find(x)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
```



### 开放寻址法

往往数组大小要开到题目要求的两到三倍

###### 模板代码

```c++
const int N=2*1e5+3,null=0x3f3f3f3f;
int h[N];

int find(int x){
    int k=(x%N+N)%N;
    
    while(h[k]!=null && h[k]!=x){
        k++;
        if(k==N) k=0;
    }

    return k;
}

int main(){
    int n;
    scanf("%d",&n);

    memset(h,0x3f,sizeof(h));  //按字节memset 整数有四个字节，0x3f3f3f3f

    while(n--){
        char op[2];
        int x;
        scanf("%s%d",op,&x);

        int k=find(x);
        if(*op=='i') h[k]=x;
        else{
            if(h[k]!=null) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
```



### 字符串哈希方式

###### 原理

字符串前缀哈希方法

将字符串所有的前缀转换成对应的哈希值（类似求前缀和）

字符串的哈希值计算：将字符串看成一个P进制数，转换成一个十进制的数，然后通过取余将其映射到一个较小的区间

注意：（1）不能映射到0  （2）不考虑冲突（p取131或13331，则q取2^64->用unsigned long long 去存储哈希值）
$$
h[i]=h[i-1]*p+str[i]
$$
然后，我们可以得到任意区间的字符串哈希值

已知h[R],h[L-1],求h[L-R]
$$
h[L-R]=h[R]-h[L-1] * p^{R-L+1}
$$


###### 模板代码

```c++
#include<iostream>

using namespace std;

typedef unsigned long long ULL;

const int N=1e5+10,P=131;

int n,m;
char str[N];
ULL h[N],p[N];

ULL get(int l,int r){
    return h[r]-h[l-1]*p[r-l+1];
}

int main(){
    scanf("%d%d%s",&n,&m,str+1);

    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*P;
        h[i]=h[i-1]*P+str[i];
    }

    while(m--){
        int l1,l2,r1,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);

        if(get(l1,r1)==get(l2,r2)) puts("Yes");
        else puts("No");
    }

    return 0;
}
```



## STL容器

### vector容器

变长数组

倍增的思想

###### 模板代码

```

```





### pair容器

二元组

###### 模板代码

```

```



### string容器

字符串

###### 模板代码

```
substr() c_str()
```



### deque类容器

#### deque容器

双端队列

###### 模板代码

```

```



#### queue容器

队列

###### 模板代码

```

```



#### priority_queue容器

优先队列（堆）

###### 模板代码

```

```



### stack容器

栈

模板代码

```

```



### set 和 map类容器

#### set和map容器

基于平衡二叉树（红黑树），动态维护有序序列



#### multiset和multimap容器





#### unordered_set和unordered_map容器

基于哈希表



#### unordered_multiset和unordered_multimap容器





#### bitset容器

压位