#include<iostream>
#include<algorithm>

using namespace std;

const int N =3010;

int n;
int a[N],b[N];
int f[N][N];

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);

    for(int i=1;i<=n;i++){
        int maxv=1;
        for(int j=1;j<=n;j++){
            f[i][j]=f[i-1][j];
            if(a[i]==b[j]){
                // f[i][j]=max(f[i][j],1);
                // for(int k=1;k<j;k++){
                //     if(b[k]<a[i]) f[i][j]=max(f[i][j],f[i][k]+1);
                // }
                f[i][j]=max(f[i][j],maxv);
            }
            if(b[j]<a[i]) maxv=max(maxv,f[i][j]+1);
            
        }
    }

    int res=0;
    for(int i=1;i<=n;i++) res=max(res,f[n][i]);

    printf("%d\n",res);

    return 0;
}
