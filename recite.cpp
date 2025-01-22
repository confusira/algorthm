#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 1e5+10 ;

int p[N];

void init(){
    for(int i=0;i<N;i++) p[i]=i;
}

int find(int x){
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

int merge(int a,int b){
    p[find(a)]=find(b);
}

bool query(int a,int b){
    return find(a)==find(b);
}
