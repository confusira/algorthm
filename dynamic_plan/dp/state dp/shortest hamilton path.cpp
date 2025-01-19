#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 20, M=1<<N;

int n;
int w[N][N];
int f[M][N];

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> w[i][j];
        }
    }

    memset(f,0x3f,sizeof f);
    f[1][0]=0;

    return 0;
}