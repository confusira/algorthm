//
// Created by lenovo on 2024/12/23.
//
#include<iostream>

using namespace std;

//const int N=1e6+10;
//int n,m;
//
//int a[N],s[N];
//
//int main(){
//    //ios::sync_with_stdio(0) 取消cin与标准输入输出的同步
//    //优点 传输更快
//    //缺点 不允许使用scanf,printf
//
//    scanf("%d%d",&n,&m);
//
//    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
//
//    s[0]=0;
//    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
//
//    while(m--){
//        int l,r;
//        scanf("%d%d",&l,&r);
//
//        printf("%d\n",s[r]-s[l-1]);
//    }
//
//    return 0;
//}

const int N=1010;

int n,m,q;

int a[N][N],s[N][N];

int main(){
    scanf("%d%d%d",&n,&m,&q);

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    s[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+a[i][j];
        }
    }

    while(q--){
        int x1,y1,x2,y2;

        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

        printf("%d\n",s[x2][y2]-s[x2][y1-1]-s[x1-1][y2]+s[x1-1][y1-1]);
    }

    return 0;
}

