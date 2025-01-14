#include<iostream>
#include<algorithm>

using namespace std;

//(1)递推式预处理
// const int N=2010,mod=1e9+7;

// int C[N][N];

// void init(){
//     for(int i=0;i<N;i++){
//         for(int j=0;j<=i;j++){
//             if(!j) C[i][j]=1;
//             else C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
//         }
//     }
// }

// int main(){
//     init();

//     int n;
//     scanf("%d",&n);

//     while(n--){
//         int a,b;
//         scanf("%d%d",&a,&b);
//         printf("%d\n",C[a][b]);
//     }

//     return 0;
// }


//（2）阶乘式预处理

// typedef long long LL;
// const int N=1e5+10,mod=1e9+7;

// int fact[N],infact[N];

// int qmi(int a,int k,int p){
//     int res=1;
//     while(k){
//         if(k&1) res=(LL)res*a%p;
//         a=(LL)a*a%p;
//         k>>=1;
//     }
//     return res;
// }

// int main(){
//     fact[0]=infact[0]=1;

//     for(int i=1;i<N;i++){
//         fact[i]=(LL)fact[i-1]*i%mod;
//         infact[i]=(LL)infact[i-1]*qmi(i,mod-2,mod)%mod;
//     }

//     int n;
//     scanf("%d",&n);

//     while(n--){
//         int a,b;
//         scanf("%d%d",&a,&b);
//         printf("%d\n",(LL)fact[a]*infact[a-b]%mod*infact[b]%mod);
//     }

//     return 0;
// }

//(3)lucas定理

// typedef long long LL;

// int p;

// int qmi(int a,int k){
//     int res=1;
//     while(k){
//         if(k&1) res=(LL)res*a%p;
//         a=(LL)a*a%p;
//         k>>=1;
//     }
//     return res;
// }

// int C(int a,int b){
//     int res=1;
//     for(int i=1,j=a;i<=b;i++,j--){
//         res=(LL)res*j%p;
//         res=(LL)res*qmi(i,p-2)%p;
//     }
//     return res;
// }

// int lucas(LL a,LL b){
//     if(a<p && b<p) return C(a,b);
//     return (LL)C(a%p,b%p)*lucas(a/p,b/p)%p;
// }

// int main(){
//     int n;
//     cin >> n;

//     while(n--){
//         LL a,b;
//         cin >> a >> b >> p;
//         cout << lucas(a,b) << endl;
//     }

//     return 0;
// }

//(4)高精度模拟
#include<vector>

const int N=5010;
int primes[N],cnt;
int sum[N];
bool st[N];

void get_primes(int n){
    for(int i=2;i<=n;i++){
        if(!st[i]) primes[cnt++]=i;
        for(int j=0;primes[j]<=n/i;j++){
            st[primes[j]*i]=true;
            if(i%primes[j]==0) break;
        }
    }
}

int get(int n,int p){
    int res=0;
    while(n){
        res+=n/p;
        n/=p;
    }
    return res;
}

vector<int> mul(vector<int> a,int b){
    vector<int> c;
    int t=0;
    for(int i=0;i<a.size();i++){
        t+=a[i]*b;
        c.push_back(t%10);
        t/=10;
    }

    while(t){
        c.push_back(t%10);
        t/=10;
    }

    return c;
}

int main(){
    int a,b;
    cin >> a >> b;

    get_primes(a);

    for(int i=0;i<cnt;i++){
        int p=primes[i];
        sum[i]=get(a,p)-get(b,p)-get(a-b,p);
    }

    vector<int> res;
    res.push_back(1);

    for(int i=0;i<cnt;i++){
        for(int j=0;j<sum[i];j++){
            res=mul(res,primes[i]);
        }
    }

    for(int i=res.size()-1;i>=0;i--) printf("%d",res[i]);
    puts("");

    return 0;
}