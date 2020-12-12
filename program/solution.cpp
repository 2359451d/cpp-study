#include<vector>
#include<unordered_map>
#include<stdio.h>

bool containsDuplicate(std::vector<int>& nums) {
        auto iter = nums.begin();
        std::unordered_map<int, int> map1;
        for (int each:nums)
        {
            // if found
            if (map1.find(each)!=map1.end())
            {
                return true;
            }
            map1.insert(std::pair<int,int>(each, 1));
        }
        return false;
}

int main(int argc, char const *argv[])
    {
        std::vector<int> list1 = {1,2,3,4};
        printf("%d\n",containsDuplicate(list1));
        return 0;
}