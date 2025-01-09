//B 数组中数值和下标相等的元素
//AcWing 69

#include<iostream>
#include<vector>

using namespace std;

class Solution1 {
public:
    int getNumberSameAsIndex(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            if(nums[i]==i) return i;
        }
        return -1;
    }
};

class Solution2 {
public:
    bool check(int index,vector<int>& nums){
        if(nums[index]>=index) return true;
        return false;
    }

    int getNumberSameAsIndex(vector<int>& nums) {
        int l=0,r=nums.size()-1;
        
        while(l<r){
            int mid=l+r>>1;
            if(check(mid,nums)) r=mid;
            else l=mid+1;
        }
        
        if(nums[l]==l) return l;
        else return -1;
    }
};