#include<iostream>
#include<cstring>

using namespace std;

const int N=1e5+3;

/*拉链法
int h[N],e[N],ne[N],idx;

void insert(int x){
    int k=(x%N+N)%N;  //正整数

    e[idx]=x;ne[idx]=h[k];h[k]=idx++;
}

bool find(int x){
    int k=(x%N+N)%N;
    for(int i=h[k];i!=-1;i=ne[i])
        if(e[i]==x) return true;
    
    return false;
}

int main(){
    int n;
    scanf("%d",&n);

    memset(h,-1,sizeof(h));

    while(n--){
        char op[2];
        int x;
        scanf("%s%d",op,&x);

        if(*op=='i') insert(x);
        else{
            if(find(x)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
*/

//开放寻址法
const int N=2*1e5+3,null=0x3f3f3f3f;
int h[N];

int find(int x){
    int k=(x%N+N)%N;
    
    while(h[k]!=null && h[k]!=x){
        k++;
        if(k==N) k=0;
    }

    return k;
}

int main(){
    int n;
    scanf("%d",&n);

    memset(h,0x3f,sizeof(h));

    while(n--){
        char op[2];
        int x;
        scanf("%s%d",op,&x);

        int k=find(x);
        if(*op=='i') h[k]=x;
        else{
            if(h[k]!=null) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}