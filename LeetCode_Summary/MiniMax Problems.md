# MiniMax Problems
[475. Heaters](https://leetcode.com/problems/heaters/#/solutions) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/475.%20Heaters.cpp))
```
Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.
Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.
So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.
Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
```

```c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int res = INT_MIN;
        sort(heaters.begin(), heaters.end());
        
        for (int house : houses) {
            int index = findUpperBoundIndex(heaters, house); // find the smallest upper bound of house
            int curDist = INT_MAX;
            if (index != heaters.size()) curDist = heaters[index]-house;
            if (index) curDist = min(curDist, house-heaters[index-1]);
            res = max(res, curDist);
        }
        
        return res;
    }
    
    // return the first element that is not smaller than val
    int findUpperBoundIndex(vector<int> &nums, int val) { 
        int left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = left + (right-left)/2;
            if (nums[mid] < val) left = mid+1;
            else right = mid;
        }
        return nums[left] >= val ? left : left+1;
    }
};
```

