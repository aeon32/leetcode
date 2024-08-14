#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <limits>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>


class Solution {
 public:
    int reverse(int x)
    {
        using Unsigned = std::make_unsigned<decltype(x)>::type;
        int min = std::numeric_limits< decltype(x) > :: min();
        int max = std::numeric_limits< decltype(x) > :: max();

        Unsigned res = 0;
        Unsigned res_max = x >= 0 ? max : -(min + 1);
        Unsigned res_max_10 = res_max / 10;

        bool positive = (x >=0);

        while (x != 0)
        {
            if (res > res_max_10)
                return 0;

            res *= 10;

            Unsigned num =  (Unsigned ) std::abs(x % 10);
            x = x / 10;

            if (res <= (res_max - num))
            {
               res += num;
            } else
               return 0;
        }

        return positive ? res : -res;
    }
};

void test1()
{
   Solution solution;
   //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
    //2147483647
   //7453847412
   int res = solution.reverse(-1240);
   std::cout<<res<<std::endl;


}

void test_ariphmetic()
{
    int x = -20;
    using unsigned_type = std::make_unsigned<decltype(x)>;
    int min = std::numeric_limits< decltype(x) > :: min();

    int c = -(min + 1);

    std::cout<<c<<std::endl;




}

int main(int argc, char** argv)
{
    //char c = 0xFB;
    //std::cout<< (int) c <<std::endl;
   test1();
}

