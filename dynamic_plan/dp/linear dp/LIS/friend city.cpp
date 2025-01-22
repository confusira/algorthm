#include<iostream>
#include<algorithm>

using namespace std;

typedef pair<int,int> PII;

const int N =5010;

int n;
PII q[N];
int f[N];

int main(){
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%d%d",&q[i].first,&q[i].second);
    }

    sort(q,q+n);

    int res=0;
    for(int i=0;i<n;i++){
        f[i]=1;
        for(int j=0;j<i;j++){
            if(q[j].second<q[i].second) f[i]=max(f[i],f[j]+1);
        }
        res=max(res,f[i]);
    }

    printf("%d\n",res);

    return 0;
}