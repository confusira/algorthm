#include<iostream>
#include<cstring>

using namespace std;

const int N =22,M =80;

int n,m,K;
int f[N][M];

int main(){
    cin >> n >> m >> K;

    memset(f,0x3f,sizeof f);

    f[0][0]=0;

    while(K--){
        int v1,v2,w;
        cin >> v1 >> v2 >> w;

        for(int j=n;j>=0;j--){
            for(int k=m;k>=0;k--){
                f[j][k]=min(f[j][k],f[max(0,j-v1)][max(0,k-v2)]+w);
            }
        }
    }

    cout << f[n][m] << endl;

    return 0;
}