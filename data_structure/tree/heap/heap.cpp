#include<iostream>
#include<algorithm>

using namespace std;

const int N=1e5+10;

/*
int n,m;
int h[N],size;

void down(int u){
    int t=u;
    if(u*2<=size && h[u*2]<h[t]) t=2*u;
    if(u*2+1<=size && h[u*2+1]<h[t]) t=2*u+1;
    if(u!=t){
        swap(h[u],h[t]);
        down(t);
    }
}

void up(int u){
    while(u/2 && h[u/2] > h[u]){
        swap(h[u/2],h[u]);
        u/=2;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    size=n;
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);

    for(int i=n/2;i;i--) down(i);  //建堆 O(nlogn)->O(n)

    while(m--){
        printf("%d ",h[1]);
        h[1]=h[size--];down(1);
    }
    return 0;
}
*/

//模拟堆的五种操作
//Acwing 839
#include<string.h>

int n,m;
int h[N],size;
int ph[N]; //插入顺序到堆内属性（位置）的映射
int hp[N]; //堆内属性（位置）到插入顺序的映射

void heap_swap(int a,int b){
    swap(ph[hp[a]],ph[hp[b]]);
    swap(hp[a],hp[b]);
    swap(h[a],h[b]);
}

void down(int u){
    int t=u;
    if(u*2<=size && h[u*2]<h[t]) t=2*u;
    if(u*2+1<=size && h[u*2+1]<h[t]) t=2*u+1;
    if(u!=t){
        heap_swap(u,t);
        down(t);
    }
}

void up(int u){
    while(u/2 && h[u/2] > h[u]){
        heap_swap(u/2,u);
        u/=2;
    }
}

int main(){
    int n,m=0;
    scanf("%d",&n);

    while(n--){
        char op[10];
        int k,x;

        scanf("%s",op);
        if(!strcmp(op,"I")){
            scanf("%d",&x);
            size++;
            m++;
            ph[m]=size,hp[size]=m;
            h[size]=x;up(size);
        }
        else if(!strcmp(op,"PM")) printf("%d\n",h[1]);
        else if(!strcmp(op,"DM")){
            heap_swap(1,size);
            size--;
            down(1);
        }  
        else if(!strcmp(op,"D")){
            scanf("%d",&k);
            k=ph[k];
            heap_swap(k,size);size--;down(k);up(k);
        }else{
            scanf("%d%d",&k,&x);
            k=ph[k];
            h[k]=x;down(k);up(k);
        }
    }

    return 0;
}