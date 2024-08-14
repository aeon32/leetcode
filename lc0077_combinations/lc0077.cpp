#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>

class Solution {
 public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> res;

        std::vector<int> row(k);
        for (int i = 0; i < k; i++)
        {
            row [i] = k - i;
        }

        do
        {
            res.push_back(row);

            int i = 0;          //current position index

            while((i < k) && ++row[i] > (n-i) )
            {
                i++;
            }
            if (i == k)
                break;

            i--;
            while (i >= 0 )
            {
                row[i] = row[i +1 ] + 1;
                i--;
            }

        } while(true);

        return res;
    }
};

void test1()
{
   Solution solution;
   //std::cout<<solution.minFlips(2, 6, 5)<<std::endl;
   auto res = solution.combine(4, 2);

   for (auto & row : res)
   {
       std::cout<<"[";
       for (int i = 0; i < row.size(); i++ )
       {
           std::cout<<row[i];
           std::cout<< ( i == row.size() - 1 ? ']' : ',');

       }
       std::cout<<std::endl;


   }

}



int main(int argc, char** argv)
{
   test1();

}

