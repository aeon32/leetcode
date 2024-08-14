#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <span>


class Solution {
 public:
    std::vector<int> circularPermutation(int n, int start) {
        std::vector<int> res;
        if ( n == 1)
        {
            return std::vector{start, (int) !start};
        }

        unsigned int count = 1 << n;
        res.reserve(count);

        res.push_back(0);
        int current_power = 1;
        int start_index = 0;

        for (int i = 1; i < count; i++)
        {
            if (i == (current_power * 2) )
            {
                current_power = i;
            }
            int val = current_power + res[2*current_power - i-1];
            if (val == start)
                start_index = i;
            res.push_back(val);
        }

        std::reverse(res.begin(), res.begin() + start_index);
        std::reverse(res.begin() + start_index, res.end());
        std::reverse(res.begin(), res.end());

        return res;

    }
};
void test1()
{
   Solution solution;
   //std::cout<<solution.minFlips(2, 6, 5)<<std::endl;
   auto res = solution.circularPermutation(3, 2);

   for (int val : res)
   {
       std::cout<<val<<" ";
   }
   std::cout<<std::endl;

}



int main(int argc, char** argv)
{
   test1();

}

