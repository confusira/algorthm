#include<iostream>
#include<algorithm>

using namespace std;

bool is_prime(int n){
    if(n<2) return false;
    for(int i=2;i<=n/i;i++){
        if(n%i==0){
            return false;
        }
    }

    return true;
}

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

    if(x>1) printf("%d %d\n",x,1);
    puts(""); 
}

const int N=1e5+10;
int primes[N],cnt;
bool st[N];

void get_primes1(int n){
    for(int i=2;i<=n;i++){
        if(!st[i]){
            primes[cnt++]=i;
            for(int j=i*i;j<=n;j+=i) st[j]=true;
        }
    }
}

void get_primes2(int n){
    for(int i=2;i<=n;i++){
        if(!st[i]){
            primes[cnt++]=i;
        }
        for(int j=0;primes[j]<=n/i;j++){
            st[primes[j]*i]=true;
            if(i%primes[j]==0) break; //primes[j]一定是i（primes[j]*i）的最小质因数
        }
    }
}

int main(){


    return 0;
}