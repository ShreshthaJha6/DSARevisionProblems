#include <bits/stdc++.h>
using namespace std;

//given an array, check if it can be partitioned into two subsets with equal sum. 
//1<nums.length()<=200 and 1<=nums[i]<=100

//------------------APPROACH-------------------------------------------------
//using the 0-1 knapsack approach. where the target is sum/2.
//if the sum is odd->return false;

//----------RECURSION------------------
//tc = O(2^n) and SC = O(n) for recursion stack
bool recursion(vector<int>& nums, int idx, int target){
    if(idx >= nums.size()){
        return (target == 0)? true : false;
    }

    //pick
    bool pick = false;
    if(nums[idx]<=target){
        pick = recursion(nums, idx+1, target - nums[idx]);
    }
    bool not_pick = recursion(nums, idx+1, target);
    return pick || not_pick;
}
//-------------MEMOIZATION--------------------
//stest = idx, target
//dimensions are = (n+1)*(target+1). here target = sum/2
//tc = O(n*target) and sc = O(n*target) + O(n) for recursion stack

bool memoization(vector<int>& nums, int idx, int target, vector<vector<bool>>& dp){
    if(idx>=nums.size()){
        return (target==0);
    }
    if(dp[idx][target]!= -1) return dp[idx][target];

    //pick
    bool pick = false;
    if(nums[idx]<=target){
        pick = memoization(nums, idx+1, target - nums[idx], dp);
    }
    //not-pick
    bool not_pick = memoization(nums, idx+1, target, dp);
    return dp[idx][target] = pick || not_pick;
}

//----------TABULATION--------------------
//states= idx, target
//dimensions are = (n+1)*(target+1). here target = sum/2
//tc = O(n*target) and sc = O(n*target)
bool tabulation(vector<int>& nums, int n, int target){
    vector<vector<bool>> dp(n+1, vector<bool>(target+1, 0));
    //base case
    for(int i=0; i<=n; i++){
        dp[i][0] = 1; //if target is 0, return true;
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=target; j++){
            if(nums[i]<=j){
                dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][target];
}

//------------SPACE OPTIMIZATION----------------
bool space_optimization(vector<int>& nums, int n, int target){
    //{1, 5, 11, 5}//4//11
    vector<bool> prev(target+1, 0);//12
    //base case: prev[0] = 1
    prev[0] = 1;//true;//100000000000

    for(int i=0; i<n; i++){//1
        vector<bool> curr(target+1, 0); curr[0] = true;
        for(int j=1; j<=target; j++){
            if(nums[i]<=j){
                curr[j] = prev[j] || prev[j-nums[i]];
            }else{
                curr[j] = prev[j];
            }
        }
        prev = curr;
    }
    return prev[target];
}



bool canPartition(vector<int>& nums){
    int n = nums.size();
    int sum = 0;
    for(int x:nums) sum+=x;

    if(sum%2 != 0)return false;
    sum = sum/2;

    bool result = false;
    vector<vector<bool>> dp(n+1, vector<bool>(sum+1, -1));
    result = space_optimization(nums, n, sum);
    return result;
}

int main(){
    vector<int> nums1 = {1, 5, 11, 5};
    vector<int> nums2 = {1,2,3,5};
    cout<<canPartition(nums1)<<endl;//true
    cout<<canPartition(nums2)<<endl; // false;
    return 0;
}