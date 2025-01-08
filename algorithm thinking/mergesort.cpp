//
// Created by lenovo on 2024/12/20.
//
#include<iostream>

using namespace std;

const int N=1e6+10;

int n;
int q[N],tmp[N];

void mergesort(int q[],int l,int r){
    if(l>=r) return;

    int mid=l+r>>1;

    mergesort(q,l,mid);
    mergesort(q,mid+1,r);

    int k=0,i=l,j=mid+1;
    while(i<=mid && j<=r){
        if(q[i]<=q[j]) tmp[k++]=q[i++];
        else tmp[k++]=q[j++];
    }

    while(i<=mid) tmp[k++]=q[i++];
    while(j<=r) tmp[k++]=q[j++];

    for(i=l,j=0;i<=r;i++,j++) q[i]=tmp[j];
}

int main(){
    scanf("%d",&n);

    for(int i=0;i<n;i++) scanf("%d",&q[i]);

    mergesort(q,0,n-1);

    for(int i=0;i<n;i++) printf("%d",q[i]);

    return 0;
}