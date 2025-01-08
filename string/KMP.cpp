//
// Created by lenovo on 2024/12/17.
//

#include<iostream>
#include<cstring>

using namespace std;

using ll = long long;

int Next[20];

void getnext(char *t){
    int j=0,k=-1;
    Next[0]=-1;

    while(j<strlen(t)){
        if(k==-1 || t[j]==t[k]){
            j++;
            k++;

            if(t[j]==t[k]){
                Next[j]=Next[k];
            }else{
                Next[j]=k;
            }
        }else{
            k=Next[k];
        }
    }

}

int KMP(char *s,char *t){
    int sum=0,j=-1;

    for(int i=0;i<strlen(s);i++){
        while(j!=-1 && s[i]!=t[j+1]) j=Next[j];

        if(s[i]==t[j+1]){
            j++;
        }

        if(j+i==strlen(t)){
            sum++;
            j=Next[j];
        }

    }

    return sum;
}

int main(){
    char s[50],t[20];

    cin >> s >> t;

    getnext(t);

    int sum=KMP(s,t);

    cout << sum << endl;

    return 0;
}