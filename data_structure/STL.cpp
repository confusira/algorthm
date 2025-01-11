#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector> 
//分配内存空间所需时间与空间大小无关，与申请次数有关
/*vector
size() 大小
empty() 判空
clear() 清空
front()/back() 头尾元素
push_back()/pop_back() 尾部压弹
begin()/end() 迭代器
[] 索引
支持比较运算 按字典序
*/

/*pair
first 第一个元素
second 第二个元素
支持比较运算 以first为第一关键字，以second为第二关键字（字典序）
make_pair(,)/{,}
*/

/*string
size()
empty()
clear()
substr(起始下标，长度) 返回子串
c_str() printf输出时调用
*/

/*queue
size()
empty()
push()
front()/back()
pop()
*/

/*priority_queue
默认为大顶堆
小顶堆 priority_queue<int,vector<int>,greater<int>>
push()
top()
pop()
*/

/*stack
size()
empty()
push()
top()
pop()
*/

/*deque
size()
empty()
clear()
front()/back()
push_front()/push_back()
pop_front()/pop_back()
[]
*/

/*set,map,multiset,multimap
size()
empty()
clear()

set/multiset
insert()
find()
count()
erase(数/迭代器) O(k+logn)
lower_bound()/upper_bound(x) 返回大于等于/大于x的数的迭代器

map/multimap
insert() 插入一个pair
erase(pair/迭代器)
find()
[]  O(logn)
lower_bound()/upper_bound()
*/

/*unordered_set,unordered_map,unordered_multiset,unordered_multimap 
与上述操作类似，但增删改查时间复杂度为O(1)
不支持lower_bound()/upper_bound()
*/

/*bitset
压位
bool数组 一字节    1024B
bitset数组 八字节  128B
bitset<个数>
支持~,&,|,^运算
>>,<<
==,!=
[]
count() 返回1的个数
any() 返回是否至少有一个1
none() 返回是否全为0

set() 把所有位置为1
set(k,v) 把第k位置为v
reset() 把所有位置为0
flip() 等价于取反
flip(k) 第K位取反
*/

using namespace std;

int main(){
    vector<int> a(10,3);
    vector<int> a[10];

    return 0;
}