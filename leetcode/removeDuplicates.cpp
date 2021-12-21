#include<stdio.h>
#include<algorithm>
#include <vector>
#include <iostream>
using namespace std;
#if 1
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
#if 0  
	  //my solution  
  	int i,j;
	for(i=0,j=0;j<nums.size()-1;i=j)
	{
		while( (i< nums.size()-1) && (nums[i] == nums[i+1]) )
			i++;
		if(i!=j)
			nums.erase(nums.begin()+j,nums.begin()+i);
		j++;
	}	
#endif
	if ( nums.size() == 0)
            return 0;
	int left=0;
	for(int r=1;r<nums.size();r++)
	{
		if(nums[left] != nums[r])
			nums[++left] = nums[r];
	}
	return ++left;
    }
    void rotate(vector<int>& nums, int k) {
	    int size = nums.size();
	    while(k--)
	    {

		    int tmp = nums.back();
		    nums.pop_back();
		    //nums[0] =  nums[size-1];
		    //nums[size-1] = tmp;
		    nums.insert(nums.begin(),tmp);


	    }
    }
};
#endif


int main()
{
	int a[] = {1,1,2,3,3,3,4,4};

	vector<int> vec(a,a+8);
	class Solution s;
	std::cout << "before:" << vec.size() << endl;
	s.rotate(vec, 3);
	std::cout << vec.size() << endl;
}
