# 数学知识

## 数论

### 质数

###### 简介

定义：在大于1的整数中，如果只包含1和本身这两个约数，就被称为质数，或者叫素数



#### 质数的判定

方法：试除法

时间复杂度：O(n^(0.5))

###### 模板代码

```c++
bool is_prime(int n){
    if(n<2) return false;
    for(int i=2;i<=n/i;i++){
        if(n%i==0){
            return false;
        }
    }

    return true;
}
```



#### 分解质因数

试除法

n中最多只包含一个大于等于sqrt(n)的质因子

时间复杂度：O(logn)-O(sqrt(n))



###### 模板代码

```c++
void divide(int x){
    for(int i=2;i<=x/i;i++){
        if(x%i==0){
            int s=0;
            while(x%i==0){
                x/=i;
                s++;
            }

            printf("%d %d\n",i,s);
        }
    }

    if(x>1) printf("%d %d\n",x,1);  //唯一大于sqrt(n)的质因数
    puts(""); 
}
```



#### 质数筛

##### 朴素质数筛和埃氏筛

###### 原理

每找到一个（埃氏筛：质）数，将它的倍数从数表中删去（打上标记）

时间复杂度：O(nloglogn)<O(nlogn)

质数定理：1-n中有（n/lnn）个质数



###### 模板代码

```c++
const int N=1e5+10;
int primes[N],cnt;
bool st[N];

void get_primes(int n){
    for(int i=2;i<=n;i++){
        if(!st[i]){
            primes[cnt++]=i;
            for(int j=i*i;j<=n;j+=i) st[j]=true;
        }
    }
}
```



##### 线性筛

###### 原理

n只会被他的最小质因子筛掉

时间复杂度：O(n)

n越大，线性筛比埃氏筛的效率可以快大致两倍



###### 模板代码

```c++
void get_primes2(int n){
    for(int i=2;i<=n;i++){
        if(!st[i]){
            primes[cnt++]=i;
        }
        for(int j=0;primes[j]<=n/i;j++){
            st[primes[j]*i]=true;
            if(i%primes[j]==0) break; //primes[j]一定是i的最小质因数
        }
    }
}
```



### 约数

##### 求所有约数

###### 原理

试除法



###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> get_divisors(int n){
    vector<int> res;

    for(int i=1;i<=n/i;i++){
        if(n%i==0){
            res.push_back(i);
            if(i!=n/i) res.push_back(n/i);
        }
    }

    sort(res.begin(),res.end());

    return res;
}

int main(){
    int n;
    cin >> n;

    while(n--){
        int x;
        cin >> x;
        auto res=get_divisors(x);
        for(auto t:res) cout << t << ' ';
        cout << endl;
    }

    return 0;
}
```



算数基本定理
$$
N=p_1^{\alpha_1}*p_2^{\alpha_2}*...*p_k^{\alpha_k}
$$


##### 求约数个数

###### 原理

$$
N=(\alpha_1+1)(\alpha_2+1)...(\alpha_k+1)
$$



###### 模板代码

```c++
typedef long long ll;
const int MOD=1e9+7;

int main(){
    int n;
    cin >> n;

    unordered_map<int,int> primes; 

    while(n--){
        int x;
        cin >> x;

        for(int i=2;i<=x/i;i++){
            while(x%i==0){
                x/=i;
                primes[i]++;
            }
        }

        if(x>1) primes[x]++;
    }

    ll res=1;
    for(auto prime:primes) res=res*(prime.second+1)%MOD;

    cout << res << endl;

    return 0;
}
```



##### 求约数之和

###### 原理

$$
sum=(p_1^{0}+p_1^1+...+p_1^{\alpha_1})...(p_k^0+p_k^1+...+p_k^{\alpha_k})
$$



###### 模板代码

```c++
typedef long long ll;
const int MOD=1e9+7;

int main(){
    int n;
    cin >> n;

    unordered_map<int,int> primes; 

    while(n--){
        int x;
        cin >> x;

        for(int i=2;i<=x/i;i++){
            while(x%i==0){
                x/=i;
                primes[i]++;
            }
        }

        if(x>1) primes[x]++;
    }

    ll res=1;
    for(auto prime:primes){
        int p=prime.first,a=prime.second;
        ll t=1;
        while(a--){
            t=(p*t+1)%MOD;
        }

        res=res*t%MOD;
    } 

    cout << res << endl;

    return 0;
}
```



##### GCD（欧几里得算法）

又称辗转相除法

###### 原理

$$
d|a,d|b~则d|(a+b),d|(ax+by)\\
(a,b)=(a,a~mod~b)\\
a~mod~b=a-int(a/b)*b=a-c*b
$$

时间复杂度：O(logn)



###### 模板代码

```c++
int gcd(int a,int b){
    return b ? gcd(b,a%b) : a;
}
```



##### 扩展欧几里得算法

###### 原理

裴蜀定理
$$
对于任意正整数a,b，那么一定存在非零整数x，y,使得\\
ax+by=(a,b)
$$
求解x与y

求解线性同余方程
$$
ax \equiv b(mod~m)\\
ax+my=b\\
(a,m)~|~b
$$


###### 模板代码

```c++
#include<iostream>

using namespace std;

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;

    return d;
}

int main(){
    int n;
    scanf("%d",&n);

    while(n--){
        int a,b,x,y;
        scanf("%d%d%d%d",&a,&b,&x,&y);

        exgcd(a,b,x,y);

        printf("%d %d\n",x,y);
    }

    return 0;
}
```



##### 中国剩余定理

###### 原理

$$
存在k个两两互质的数，有如下同余方程组\\
x\equiv a_1 (mod~m_1)\\
x\equiv a_2 (mod~m_2)\\
...\\
x\equiv a_k (mod~m_k)\\
令M=m_1*m_2*...*m_k\\
M_i=M/m_i ~~M_i^{-1}表示M_i模m_i的逆\\
x=a_1*M_1*M_1^{-1}+a_2*M_2*M_2^{-1}+...+a_k*M_k*M_k^{-1}
$$

求解线性方程组的解



###### 模板代码



### 欧拉函数

###### 原理

欧拉函数：1-n中与n互质的数的个数
$$
\phi(n)=n*(1-p_1^{-1})(1-p_2^{-1})...(1-p_k^{-1})
$$
方法：

（1）分解质数求欧拉函数 

适合单个求解，时间复杂度：O(sqrt(n))

（2）筛法求欧拉函数

适合多个求解，时间复杂度：O(n)



###### 模板代码

分解质数求法

```c++
#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;

    while(n--){
        int a;
        cin >> a;
        
        int res=a;
        for(int i=2;i<=a/i;i++){
            if(a%i==0){
                res=res/i*(i-1);
                while(a%i==0) a/=i;
            }
        }
        if(a>1) res=res/a*(a-1);

        cout << res << endl;
    }

    return 0;
}
```



筛法求法

```c++
const int N=1e6+10;

typedef long long ll;

int primes[N],cnt;
int phi[N];
bool st[N];

ll get_eulers(int n){
    phi[1]=1;

    for(int i=2;i<=n;i++){
        if(!st[i]){
            primes[cnt++]=i;
            phi[i]=i-1;
        }

        for(int j=0;primes[j]<=n/i;j++){
            st[primes[j]*i]=true;
            if(i%primes[j]==0){
                phi[primes[j]*i]=phi[i]*primes[j]; //phi[primes[j]*i]和phi[i]质因数相同，仅原数不同
                break;
            }
            phi[primes[j]*i]=phi[i]*(primes[j]-1);
        }
    }

    ll res=0;
    for(int i=1;i<=n;i++) res+=phi[i];
    return res;
}

int main(){
    int n;
    cin >> n;

    cout << get_eulers(n) << endl;

    return 0;
}
```



欧拉定理与费马定理
$$
若a与n互质，则a^{\phi(n)} \equiv 1(mod~n)\\
若p为质数，a^{\phi(p)}=a^{p-1} \equiv 1(mod~p)
$$



### 快速幂

###### 原理

$$
a^k~mod~p \\
a^k=a^{2^{x_1}+2^{x_2}+...+2^{x_t}}
$$

时间复杂度：O(logk)



###### 模板代码

```c++
int qmi(int a,int k,int p){
    int res=1;
    while(k){
        if(k & 1) res=(LL)res*a%p;
        k>>=1;
        a=(LL)a*a%p;
    }
    return res;
}
```



## 组合计数



## 高斯消元

###### 原理

求解线性方程组
$$
a_{11}x_1+a_{12}x_2+...+a_{1n}x_n=b_1\\
a_{21}x_1+a_{22}x_2+...+a_{2n}x_n=b_2\\
...\\
a_{m1}x_1+a_{m2}x_2+...+a_{mn}x_n=b_m
$$
1、解的可能性：

（1）无解：1=0

（2）无穷组解：0=0

（3）唯一解：标准阶梯形

2、对系数矩阵的三种操作

（1）把某一行乘一个非零的数

（2）交换某两行

（3）把某一行的若干倍加到另一行上去

3、步骤：枚举每一列c

（1）找到绝对值最大的那一行

（2）将该行换到最上面

（3）将该行第一个数变成1

（4）将下面所有行的第c列消成0

4、时间复杂度：O(n^3)



###### 模板代码

```c++
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

const int N=110;
const double eps=1e-6;

int n;
double a[N][N];

int gauss(){
    int c,r;
    for(c=0,r=0;c<n;c++){
        int t=r;
        for(int i=r;i<n;i++){
            if(fabs(a[i][c])>fabs(a[t][c])){
                t=i;
            }
        }
        if(fabs(a[t][c])<eps) continue;

        for(int i=c;i<=n;i++) swap(a[t][i],a[r][i]);

        for(int i=n;i>=c;i--) a[r][i]/=a[r][c];

        for(int i=r+1;i<n;i++){
            if(fabs(a[i][c])>eps)
                for(int j=n;j>=c;j--)
                    a[i][j]-=a[r][j]*a[i][c];
        }

        r++;
    }

    if(r<n){
        for(int i=r;i<n;i++){
            if(fabs(a[i][n])>eps) return 2;
        }
        return 1;
    }

    for(int i=n-1;i>=0;i--)
        for(int j=i+1;j<n;j++)
            a[i][n]-=a[i][j]*a[j][n];

    return 0;
}

int main(){
    cin >> n;

    for(int i=0;i<n;i++)
        for(int j=0;j<n+1;j++)
            cin >> a[i][j];

    int t=gauss();

    if(t==0){
        for(int i=0;i<n;i++) printf("%.2f\n",a[i][n]);
    }
    else if(t==1) printf("infinite");
    else printf("no solution");

    return 0;
}
```



## 简单博弈论