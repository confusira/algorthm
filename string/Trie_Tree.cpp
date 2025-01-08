//
// Created by lenovo on 2024/12/17.
//
#include<cstring>
#include<iostream>

using namespace std;

const int MAX=10000;

struct Trie{
    int child[26];
}T[MAX];

int q=0;

void insert(char *s){
    int len=strlen(s);

    int p=0;

    for(int i=0;i<len;i++){
        if(T[p].child[s[i]-'a']==0){
            T[p].child[s[i]-'a']=++q;
        }

        p=T[p].child[s[i]-'a'];
    }
}

bool search(char *s){
    int len=strlen(s);

    int p=0;

    for(int i=0;i<len;i++){
        if(T[p].child[s[i]-'a']==0){
            return false;
        }

        p=T[p].child[s[i]-'a'];
    }

    return true;
}

int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        char temp[50];
        cin >> temp;
        insert(temp);
    }

    int m;
    cin >> m;
    for(int i=0;i<m;i++){
        char temp[50];
        cin >> temp;
        if(search(temp)){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}