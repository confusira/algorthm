#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<unordered_map>

using namespace std;

const int N =2000010;

int n,m;
int p[N];
unordered_map<int,int> S;

struct Query{
    int a,b,e;
}q[N];

int find(int x){
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}

int get(int x){
    if(S.count(x)==0) S[x]=++n;
    return S[x];
}

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        n=0;
        scanf("%d",&m);

        S.clear();

        for(int i=0;i<m;i++){
            int x,y,e;
            scanf("%d%d%d",&x,&y,&e);
            q[i]={get(x),get(y),e};
        }

        for(int i=1;i<=n;i++) p[i]=i;

        for(int i=0;i<m;i++){
            if(q[i].e==1){
                int pa=find(q[i].a);
                int pb=find(q[i].b);
                p[pa]=pb;
            }
        }

        int has_conflict=false;
        for(int i=0;i<m;i++){
            if(q[i].e==0){
                int pa=find(q[i].a);
                int pb=find(q[i].b);
                if(pa==pb){
                    has_conflict=true;
                    break;
                }
            }
        }

        if(has_conflict) puts("NO");
        else puts("YES");
    }

    return 0;
}