#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 110, M = 25010;

int n;
int a[N];
int f[M];

int main(){
    int T;
    cin >> T;

    while(T--){
        cin >> n;

        for(int i=0;i<n;i++) cin >> a[i];

        sort(a,a+n);

        int m=a[n-1];

        memset(f,0,sizeof f);

        f[0] = 1;

        int res=0;

        for(int i=0;i<n;i++){
            if(!f[a[i]]){
                res++;
            }
            for(int j=a[i];j<=m;j++){
                    f[j] += f[j-a[i]];
                }
        }

        cout << res << endl;
    }

    return 0;
}