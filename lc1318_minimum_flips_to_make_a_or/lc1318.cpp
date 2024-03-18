#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>


class Solution {
 public:
    std::vector<int> countBits(int n)
    {
        std::vector <int> res(n+1);
        for (int i = 0; i <= n; i++)
        {
            int j = i;
            int n = 0;
            while (j != 0)
            {
                n += j & 1;
                j = j >> 1;
            }
            res[i] = n;

        }
        return res;

    }
};


void test1()
{
   Solution solution;
   //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
   for(int val : solution.countBits(2))
   {
       std::cout<<val<<std::endl;
   }


}



int main(int argc, char** argv)
{
   test1();

}

