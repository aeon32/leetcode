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
    int minFlips(int a, int b, int c)
    {
        int flips = 0;

        std::make_unsigned_t<decltype(c)> aux = -1;

        while (aux != 0)
        {
            int bit_a = a & 1;
            int bit_b = b & 1;
            int bit_c = c & 1;

            if ( (bit_a | bit_b) != bit_c)
            {
                if (bit_c)
                    flips += 1;
                else
                    flips += bit_a + bit_b;
            }
            a = a >> 1;
            b = b >> 1;
            c = c >> 1;
            aux = aux >> 1;
        }
        return flips;
    }
};

void test1()
{
   Solution solution;
   std::cout<<solution.minFlips(2, 6, 5)<<std::endl;

}



int main(int argc, char** argv)
{
   test1();

}

