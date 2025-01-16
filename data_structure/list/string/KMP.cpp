//
// Created by lenovo on 2024/12/30.
//
#include<iostream>

using namespace std;

const int N=1e4+10,M=1e5+10;

int n,m;

char p[N],s[M];

int ne[N];

int main(){
    cin >> n >> p+1 >> m >> s+1;

    //求next过程
    for(int i=2,j=0;i<=m;i++){
        while(j && p[i]!=p[j+1]) j=ne[j];
        if(p[i]==p[j+1]) j++;
        ne[i]=j;
    }

    //匹配过程
    for(int i=1,j=0;i<=m;i++){
        while(j && s[i] != p[j+1]) j=ne[j];
        if(s[i]==p[j+1]) j++;
        if(j==n){
            //匹配成功
            j=ne[j];
        }
    }

    return 0;
}