//
// Created by lenovo on 2024/12/17.
//

#include<iostream>

using namespace std;

using ll = long long;

int k=19;

//哈希算法
ll BKDRHash(char *s){
    ll sum=0;
    for(int i=0;s[i];i++){
        sum=sum*k+s[i];
    }
    return sum;
}

int main(){
    char des[20];
    cin >> des;
    ll t= BKDRHash(des);

    int n;
    cin >> n;
    int total=0;
    while(n--){
        char temp[20];
        cin >> temp;
        if(BKDRHash(temp)==t){
            total++;
        }
    }

    cout << total << endl;

    return 0;
}
