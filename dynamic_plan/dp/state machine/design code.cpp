#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 55, M =1e9+7;

int n,m;
char str[N];
int f[N][N];

int main(){
    cin >> n >> str+1;
    m=strlen(str+1);

    int next[N]={0};

    for(int i=2,j=0;i<=n;i++){
        while(j&&str[j+1]!=str[i]) j=next[j];
        if(str[j+1]==str[i]) j++;
        next[i]=j;
    }

    f[0][0]=1;

    for(int i=0;i<n;i++){
        for(int j=0;j<=m;j++){
            for(char k='a';k<='z';k++){
                int u=j;
                while(u&&str[u+1]!=k) u=next[u];
                if(str[u+1]==k) u++;
                if(u<m) f[i+1][u]=(f[i+1][u]+f[i][j])%M;
            }
        }
    }

    int res=0;
    for(int i=0;i<m;i++) res=(res+f[n][i])%M;

    cout << res << endl;

    return 0;
}