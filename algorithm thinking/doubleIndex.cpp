//
// Created by lenovo on 2024/12/23.
//
#include<iostream>
#include<string.h>

using namespace std;

//字符串扫描单词 “ab def cd”
//int main(){
//    char str[1000];
//
//    gets(str);
//
//    int n=strlen(str);
//
//    for(int i=0;i<n;i++){
//        int j=i;
//        while(j<n && str[j]!=' ') j++;
//
//        for(int k=i;k<j;k++){
//            printf("%c",str[k]);
//        }
//        printf("\n");
//
//        i=j;
//    }
//
//    return 0;
//}

//最长不重复连续子序列
//暴力遍历 O(N^2)
//双指针 O(N)

const int N=1e6+10;

int a[N];
int s[N];

int main(){
    int n;
    cin >> n;

    for(int i=0;i<n;i++)scanf("%d",&a[i]);

    int res=0;

    for(int i=0,j=0;i<n;i++){
        s[a[i]]++;
        while(s[a[i]]>1){
            s[a[j]]--;
            j++;
        }

        res=max(res,i-j+1);
    }

    cout << res << endl;

    return 0;
}
