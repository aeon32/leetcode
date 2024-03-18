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
    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> res;

        generate_parenthesis(n, n, "", res);

        return res;

    }

 private:
    void generate_parenthesis(int available_open, int available_close,  std::string val, std::vector<std::string> & out)
    {

        bool end = true;
        if (available_open)
        {
            generate_parenthesis(available_open - 1, available_close, val + '(', out);
            end = false;
        };

        if  (available_close >available_open )
        {
            generate_parenthesis(available_open, available_close - 1, val + ')', out);
            end = false;
        }

        if (end)
        {
            out.emplace_back(val);
        }

    }
};


void test1()
{
   Solution solution;
   //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
   for(auto & val : solution.generateParenthesis(3))
   {
       std::cout<<val<<std::endl;
   }


}



int main(int argc, char** argv)
{
   test1();

}

