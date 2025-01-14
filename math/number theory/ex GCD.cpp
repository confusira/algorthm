#include<iostream>

using namespace std;

typedef long long LL;

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;

    return d;
}

// int main(){
//     int n;
//     scanf("%d",&n);

//     while(n--){
//         int a,b,x,y;
//         scanf("%d%d%d%d",&a,&b,&x,&y);

//         exgcd(a,b,x,y);

//         printf("%d %d\n",x,y);
//     }

//     return 0;
// }

//求解线性同余方程
int main(){
    int n;
    scanf("%d",&n);

    while(n--){
        int a,b,m;
        scanf("%d%d%d",&a,&b,&m);
        int x,y;
        int d=exgcd(a,m,x,y);
        if(b%d) puts("impossible");
        else printf("%d\n",(LL)x*(b/d)%m);
    }

    return 0;
}