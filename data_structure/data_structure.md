# 数据结构



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



## 单调栈

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



## 单调队列

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

