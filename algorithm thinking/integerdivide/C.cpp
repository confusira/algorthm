//C 0到n-1中缺失的数字
//Acwing 68

#include<iostream>
#include<vector>

using namespace std;

class Solution1 {
public:
    int getMissingNumber(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=i) return i;
        }
        return nums.size();
    }
};

class Solution2 {
public:
    bool check(int index,vector<int>& nums){
        if(nums[index]==index) return false;
        return true;
    }

    int getMissingNumber(vector<int>& nums) {
        if(nums.size()==0) return 0; //数组为零，就不能通过索引方法判断，会出现段错误
        int l=0,r=nums.size()-1;
        
        while(l<r){
            int mid=l+r>>1;
            if(check(mid,nums)) r=mid;
            else l=mid+1;
        }
        
        if(nums[l]==l) return nums.size();
        else return l;
    }
};