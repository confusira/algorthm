#include<iostream>

using namespace std;

const int N = 1010;

int v[5]={0,10,20,50,100};
int f[5][N];

int main(){
    int m;
    cin >> m;

    f[0][0]=1;

    for(int i=1;i<=4;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=f[i-1][j];
            if(j>=v[i]){
                f[i][j]+=f[i][j-v[i]];
            }
        }
    }

    cout << f[4][m] << endl;

    return 0;
}