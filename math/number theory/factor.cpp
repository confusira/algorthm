#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*求所有约数
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
*/

#include<unordered_map>

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
        // res=res*(prime.second+1)%MOD; 求约数个数
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