//
// Created by lenovo on 2024/12/18.
//
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int M=2000;

char s1[M];

char s2[M<<1];

int p[M<<1];

void init(){
    s2[0]='$';
    s2[1]='#';

    int j=2;
    for(int i=0;i<strlen(s1);i++){
        s2[j++]=s1[i];
        s2[j++]='#';
    }

    s2[j++]='^';
    s2[j++]='\0';
}

int Manacher(){
    int len=-1;

    int max_i=0;

    int id=0;

    p[0]=0;

    for(int i=1;i<strlen(s2);i++){
        if(i<max_i){
            p[i]=min(p[2*id-i],max_i-i);
        }else{
            p[i]=1;
        }

        while(s2[i-p[i]]==s2[i+p[i]]){
            p[i]++;
        }

        if(max_i<i+p[i]) {
            id = i;
            max_i = i + p[i];
        }

        len=max(len,p[i-1]);
    }

    return len;
}

int main(){
    cin >> s1;

    init();

    cout << Manacher() << endl;

    return 0;
}