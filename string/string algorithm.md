# 字符串算法

### 为了解决字符串的匹配问题



![](C:\Users\lenovo\Desktop\c primer plus\algorthm\string\字符串算法.png)



## 哈希算法

#### Q：有n个长度为m的字符串，要查找相同的字符串

Brute Forces: O(n^2 m)

Hash 算法: 将每个字符串转换成数字，比较数字的大小

###### BKDRHash 算法 ：将字符串看成K进制数，每个字符乘以权值的和作为字符串的值



###### 代码

```c++
ll BKDRHash(char *s){
    ll sum=0;
    for(int i=0;s[i];i++){
        sum=sum*k+s[i];
    }
    return sum;
}
```



## KMP算法

#### Q：查找某个字符串中是否包含另一个字符串

Brute Forces: O(nm)

###### KMP算法：i指向目标串，j指向模式串，匹配失败时，在控制j的回溯位置的同时，消除i的回溯

时间复杂度：O(n+m)

###### 前缀

模式串除去末位字符

###### 后缀

模式串除去首位字符

###### 最长公共字串

能够读取的长度最长的子串



###### 难点：Next数组的求解



###### 代码

```c++
int Next[20];

void getnext(char *t){
    int j=0,k=-1;
    Next[0]=-1;

    while(j<strlen(t)){
        if(k==-1 || t[j]==t[k]){
            j++;
            k++;

            if(t[j]==t[k]){
                Next[j]=Next[k];
            }else{
                Next[j]=k;
            }
        }else{
            k=Next[k];
        }
    }

}

int KMP(char *s,char *t){
    int sum=0,j=-1;

    for(int i=0;i<strlen(s);i++){
        while(j!=-1 && s[i]!=t[j+1]) j=Next[j];

        if(s[i]==t[j+1]){
            j++;
        }

        if(j+i==strlen(t)){
            sum++;
            j=Next[j];
        }

    }

    return sum;
}
```



## Trie树

#### 词频的统计、前缀的匹配以及去重操作



###### 代码

```c++
const int MAX=10000;

//构造字典树
struct Trie{
    int child[26];
}T[MAX];

int q=0;

void insert(char *s){
    int len=strlen(s);

    int p=0;

    for(int i=0;i<len;i++){
        if(T[p].child[s[i]-'a']==0){
            T[p].child[s[i]-'a']=++q;
        }

        p=T[p].child[s[i]-'a'];
    }
}

//查找
bool search(char *s){
    int len=strlen(s);

    int p=0;

    for(int i=0;i<len;i++){
        if(T[p].child[s[i]-'a']==0){
            return false;
        }

        p=T[p].child[s[i]-'a'];
    }

    return true;
}
```



## Manacher算法

#### 查找字符串中的最长回文子串

###### 步骤

（1）加#，变成奇数串

（2）加$和^辨别首尾

（3）计算长度p[i]



###### 难点：p数组的求解



###### 代码

```c++
const int M=2000;

char s1[M];

char s2[M<<1];

int p[M<<1];

void init(){
    s2[0]='$';
    s2[1]='#';

    int j=2;
    for(int i=0;i<strlen(s1);i++){
        s2[j++]=s1[i];
        s2[j++]='#';
    }

    s2[j++]='^';
    s2[j++]='\0';
}

int Manacher(){
    int len=-1;

    int max_i=0;

    int id=0;

    p[0]=0;

    for(int i=1;i<strlen(s2);i++){
        if(i<max_i){
            p[i]=min(p[2*id-i],max_i-i);
        }else{
            p[i]=1;
        }

        while(s2[i-p[i]]==s2[i+p[i]]){
            p[i]++;
        }

        if(max_i<i+p[i]) {
            id = i;
            max_i = i + p[i];
        }

        len=max(len,p[i-1]);
    }

    return len;
}
```



## AC自动机

#### 多模匹配问题：多个模式串匹配一个目标串

###### 步骤

（1）构建Trie树

（2）fail指针的查找

（3）根据目标串进行多模匹配



###### 难点：fail指针的求法



###### 代码

```c++
const int MAX=1000;

struct Trie{
    int child[26];
    int fail;
    int count;
}T[MAX];

int cnt=1;

queue<int> q;

void insert(char *s){
    int len=strlen(s);
    
    int p=1;
    
    for(int i=0;i<len;i++){
        if(T[p].child[s[i]-'a']==0){
            T[p].child[s[i]-'a']=++cnt;
        }
        p=T[p].child[s[i]-'a'];
    }
    
    T[p].count++;
}

void setFail(){
    for(int i=0;i<26;i++){
        T[0].child[i]=1;
    }
    
    q.push(1);
    T[1].fail=0;
    
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
        for(int i=0;i<26;i++){
            int v=T[u].child[i];
            int f=T[u].fail;
            
            if(v==0){
                T[u].child[i]=T[f].child[i];
                continue;
            }else{
                T[v].fail=T[f].child[i];
                q.push(v);
            }
        }
    }
}

int search(char *s){
    int len=strlen(s);
    
    int p=1;
    
    int num=0;
    
    for(int i=0;i<len;i++){
        int v=s[i]-'a';
        int k=T[p].child[v];
        
        while(k>1 && T[k].count!=-1){
            num+=T[k].count;
            T[k].count=-1;
            k=T[k].fail;
        }
        
        p=T[p].child[v];
    }
    
    return num;
}
```

