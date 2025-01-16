//
// Created by lenovo on 2024/12/30.
//
#include<iostream>

using namespace std;

const int N=1e6+10;

//int head,e[N],ne[N],idx;
//
////初始化
//void init(){
//    head=-1;
//    idx=0;
//}
//
////将X插到头节点
//void add_to_head(int x){
//    e[idx]=x,ne[idx]=head,head=idx,idx++;
//}
//
////将X插到下标为k的数后面
//void add(int k,int x){
//    e[idx]=x,ne[idx]=ne[k],ne[k]=idx,idx++;
//}
//
////将k后面的点删除
//void remove(int k){
//    ne[k]=ne[ne[k]];
//}
//
//int main(){
//    int m;
//    cin >> m;
//
//    init();
//
//    while(m--){
//        int k,x;
//        char op;
//
//        cin >> op;
//        if(op=='H'){
//            cin >> x;
//            add_to_head(x);
//        }else if(op=='O'){
//            cin >> k;
//            if(!k) head=ne[head];
//            remove(k-1);
//        }else{
//            cin >> k >> x;
//            add(k-1,x);
//        }
//    }
//
//    for(int i=head;i!=-1;i=ne[i]) cout << e[i] << " ";
//
//    cout << endl;
//
//    return 0;
//}

int m;
int e[N],l[N],r[N],idx;

//初始化
void init(){
    //0表示最左边节点，1表示最右边节点
    r[0]=1,l[1]=0;
    idx=2;
}

//在下标为K的右边插入X
void add(int k,int x){
    e[idx]=x,l[idx]=k,r[idx]=r[k],l[r[k]]=idx,r[k]=idx;
}

//在下标为K的左边插入X add(l[k],x)

//删除下标为K的点
void remove(int k){
    r[l[k]]=r[k],l[r[k]]=l[k];
}