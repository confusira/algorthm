//
// Created by lenovo on 2024/12/27.
//
#include<iostream>

using namespace std;

//int main(){
//    int n=10;
//
//    for(int i=3;i>=0;i--) cout << (n >> i & 1 ) ;
//    cout << endl;
//
//    return 0;
//}

//一个数中有多少个1

int lowbit(int x){
    return x & (-x);
}

int main(){
    int n;
    cin >> n;

    while(n--){
         int x;
         cin >> x;

         int res=0;

         while(x){
             res++;
             x-=lowbit(x);
         }

         cout << res << endl;
    }

    return 0;
}