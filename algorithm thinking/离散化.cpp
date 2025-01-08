//
// Created by lenovo on 2024/12/27.
//
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int,int> PII;

const int N=3*1e6+10;

int n,m;

int a[N],s[N];

vector<int> alls;
vector<PII> add,queries;

//二分
int find(int x){
    int l=0,r=alls.size()-1;
    while(l<r){
        int mid=l+r>>1;
        if(alls[mid]>=x) r=mid;
        else l=mid+1;
    }

    return r+1;
}

//去重手动实现
vector<int>::iterator unique(vector<int> &a){
    int j=0;
    for(int i=0;i<a.size();i++){
        if(i==0 || a[i]!=a[i-1]){
            a[j++]=a[i];
        }
    }

    return a.begin()+j;
}

int main(){
    cin >> n >> m;

    //输入
    for(int i=0;i<n;i++){
        int x,c;
        cin >> x >> c;
        add.push_back({x,c});

        alls.push_back(x);
    }

    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        queries.push_back({l,r});
        alls.push_back(l);
        alls.push_back(r);
    }

    //去重
    sort(alls.begin(),alls.end());
    alls.erase(unique(alls.begin(),alls.end()),alls.end());

    //添加
    for(auto item:add){
        int x=find(item.first);
        alls[x]+=item.second;
    }

    //前缀和
    for(int i=1;i<alls.size();i++){
        s[i]=s[i-1]+alls[i];
    }

    //查询
    for(auto item:queries){
        int l=find(item.first),r=find(item.second);
        cout << s[r]-s[l-1] << endl;
    }

    return 0;
}