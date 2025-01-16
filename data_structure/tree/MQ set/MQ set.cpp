#include<iostream>

using namespace std;

const int N=1e5+10;

/*
int n,m;
int p[N];

int find(int x){ //返回x所在集合的编号+路径压缩
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++) p[i]=i;

    while(m--){
        char op[2];
        int a,b;
        scanf("%s%d%d",op,&a,&b);

        if(op[0]=='M') p[find(a)]=find(b);
        else{
            if(find(a)==find(b)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
*/

//维护连通块的额外信息
int n,m;
int p[N],size[N];

int find(int x){ 
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++){
        p[i]=i;
        size[i]=1;
    } 

    while(m--){
        char op[2];
        int a,b;
        if(op[0]=='C'){
            scanf("%s%d%d",op,&a,&b);
            if(find(a)==find(b)) continue;
            size[find(b)]+=size[find(a)];
            p[find(a)]=find(b);
        } 
        else if(op[1]=='1'){
            scanf("%s%d%d",op,&a,&b);
            if(find(a)==find(b)) puts("Yes");
            else puts("No");
        }else{
            scanf("%s%d",op,&a);
            printf("%d\n",size[find(a)]);
        }
    }

    return 0;
}