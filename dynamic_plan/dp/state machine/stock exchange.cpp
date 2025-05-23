#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010, M=110, INF=0x3f3f3f3f;

int n,m;
int w[N];
int f[N][M][2];

int main(){
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++) scanf("%d",&w[i]);

    memset(f,-0x3f,sizeof f);
    for(int i=0;i<=n;i++) f[i][0][0]=0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]+w[i]);
            f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][0]-w[i]);
        }
    }

    int res = 0;
    for(int i=1;i<=m;i++) res = max(res,f[n][i][0]);

    printf("%d\n",res);

    return 0;
}