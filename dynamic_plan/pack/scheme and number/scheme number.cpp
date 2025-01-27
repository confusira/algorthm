#include<iostream>
#include<cstring>

using namespace std;

const int N = 1010,MOD = 1e9+7;

int n,m;
int f[N],g[N];

int main(){
    cin >> n >> m;

    memset(f,-0x3f,sizeof f);

    f[0]=0;

    g[0]=1;

    for(int i=0;i<n;i++){
        int v,w;
        cin >> v >> w;

        for(int j=m;j>=v;j--){
            int maxv=max(f[j],f[j-v]+w);
            int cnt=0;
            if(maxv==f[j]) cnt+=g[j];
            if(maxv==f[j-v]+w) cnt+=g[j-v];
            g[j]=cnt % MOD;
            f[j]=maxv;
        }
    }

    int res=0;
    for(int i=0;i<=m;i++) res=max(res,f[i]);
    int cnt=0;
    for(int i=0;i<=m;i++) if(f[i]==res) cnt=(cnt+g[i])%MOD;

    cout << cnt << endl;

    return 0;
}