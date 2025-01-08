//
// Created by lenovo on 2024/12/18.
//
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAX=1000;

struct Trie{
    int child[26];
    int fail;
    int count;
}T[MAX];

int cnt=1;

queue<int> q;

void insert(char *s){
    int len=strlen(s);

    int p=1;

    for(int i=0;i<len;i++){
        if(T[p].child[s[i]-'a']==0){
            T[p].child[s[i]-'a']=++cnt;
        }
        p=T[p].child[s[i]-'a'];
    }

    T[p].count++;
}

void setFail(){
    for(int i=0;i<26;i++){
        T[0].child[i]=1;
    }

    q.push(1);
    T[1].fail=0;

    while(!q.empty()){
        int u=q.front();
        q.pop();

        for(int i=0;i<26;i++){
            int v=T[u].child[i];
            int f=T[u].fail;

            if(v==0){
                T[u].child[i]=T[f].child[i];
                continue;
            }else{
                T[v].fail=T[f].child[i];
                q.push(v);
            }
        }
    }
}

int search(char *s){
    int len=strlen(s);

    int p=1;

    int num=0;

    for(int i=0;i<len;i++){
        int v=s[i]-'a';
        int k=T[p].child[v];

        while(k>1 && T[k].count!=-1){
            num+=T[k].count;
            T[k].count=-1;
            k=T[k].fail;
        }

        p=T[p].child[v];
    }

    return num;
}

int main(){

    int n;

    cin >> n;

    for(int i=0;i<n;i++){
        char temp[50];
        cin >> temp;
        insert(temp);
    }

    setFail();

    char temp[50];
    cin >> temp;
    cout << search(temp) << endl;

    return 0;
}