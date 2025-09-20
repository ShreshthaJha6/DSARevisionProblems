#include <bits/stdc++.h>
using namespace std;
//given n items each with weight w and value v, and a knapsack with capacity W, find the maximum value that can be put in the knapsack
//0-1 knapsack: each item can be chosen at most once

int recursion(vector<int>& weight, vector<int>& value, int n, int W){
    if(n==0 || W==0) return 0;
    if(weight[n-1] <= W){
        return max(value[n-1] + recursion(weight, value, n-1, W-weight[n-1]), recursion(weight, value, n-1, W));
    }
    else{
        return recursion(weight, value, n-1, W);
    }
}

int memoization(vector<int>& weight, vector<int>& value, int n, int W, vector<vector<int>>& dp){
    if(n==0 || W==0) return 0;
    if(dp[n][W] != -1)return dp[n][W];
    
    if(weight[n-1] <= W){
        dp[n][W] = max(value[n-1] + memoization(weight, value, n-1, W-weight[n-1], dp), memoization(weight, value, n-1, W, dp));
    }
    else{
        dp[n][W] = memoization(weight, value, n-1, W, dp);
    }
    return dp[n][W];
}

int knapsack(vector<int>& weight, vector<int>& value, int W){
    int n = value.size();

    //return recursion(weight, value, n, W);
    vector<vector<int>> dp(n+1, vector<int>(W+1, -1));
    return memoization(weight, value, n, W, dp);
}

int tabulation(vector<int>& weight, vector<int>& value, int W){
    int n = value.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i=1; i<=n; i++){
        for(int j=0; j<=W; j++){
            if(weight[i-1] <= j){
                dp[i][j] = max(value[i-1] + dp[i-1][j - weight[i-1]], dp[i-1][j]);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][W];
}

int space_optimization(vector<int>& weight, vector<int>& value, int W){
    int n = value.size();
    vector<int> prev(W+1, 0);

    //initialization for the first item with index 0. w<weight[0]->0; w>weight[0]->value[0]
    for(int w = weight[0]; w<=W; w++){
        prev[w] = value[0];
    }

    for(int i=1; i<n; i++){//i is the current item index
        vector<int> curr(W+1, 0);
        for(int j=0; j<=W; j++){//j is the current capacity
            int not_take = prev[j];
            int take = 0;
            if(weight[i]<=j){
                take = value[i] + prev[j-weight[i]];
            }
            curr[j] = max(take, not_take);
        }
        prev = curr;
    }
    return prev[W];
}

int main(){
    /*Input: W = 4, val[] = [1, 2, 3], wt[] = [4, 5, 1] 
Output: 3
Explanation: Choose the last item, which weighs 1 unit and has a value of 3.
Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6] 
Output: 0
Explanation: Every item has a weight exceeding the knapsack's capacity (3).
Input: W = 5, val[] = [10, 40, 30, 50], wt[] = [5, 4, 2, 3] 
Output: 80
Explanation: Choose the third item (value 30, weight 2) and the last item (value 50, weight 3) for a total value of 80.*/
    int W = 5;
    vector<int> value = {10, 40, 30, 50};
    vector<int> weight = {5, 4, 2, 3};
    cout << space_optimization(weight, value, W) << endl;
    W = 4;
    value = {1, 2, 3};
    weight = {4, 5, 1};
    cout << space_optimization(weight, value, W) << endl;
    W = 3;
    value = {1, 2, 3};
    weight = {4, 5, 6};
    cout << space_optimization(weight, value, W) << endl;

    return 0;
}