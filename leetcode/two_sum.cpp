/*
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target){
	map<int,int> a;
	vector<int> b(2, -1);
	for(int i = 0;i<=nums.size();i++){
		if(a.count(target-nums[i])>0)
		{
			b[0] = a[target-nums[i]];
			b[1] = i;
			break;
		}
		a[nums[i]] = i;
	}
	return b;
}

int main(){

}

