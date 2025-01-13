#include<iostream>
#include<algorithm>

using namespace std;

/*分解质数求法
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
*/

//筛法求法
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