#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <span>

void out(std::vector<int> & vec)
{
    std::cout << "[";
    for (int i = 0; i <vec.size(); i++)
    {
        std::cout << vec[i];
        std::cout << (i == vec.size() - 1 ? ']' : ',');
    }
    std::cout << std::endl;
}


class Solution {
 public:

    //non-recursive version
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        int s = nums.size();
        std::vector<std::vector<int>> res;

        res.push_back(nums);

        std::vector<int> swap_count (s);

        out(nums);
        while(true)
        {
            int i = 0;
            while ( i < nums.size() && swap_count[i] == s - i - 1 )
            {
                int last_swapped = swap_count[i];
                swap_count[i] = 0;
                std::swap(nums[i], nums[last_swapped + i]);
                i++;
            }
            if (i == s)
                break;

            std::swap(nums[i], nums[swap_count[i] + i]);
            swap_count[i]++;
            std::swap(nums[i], nums[swap_count[i] + i]);

            out(nums);
            //out(swap_count);
        }

        return res;
    }


    void permute_recursive_(std::vector<int> & data, int pos, std::vector<std::vector<int>> & res )
    {
        if (pos == data.size() - 1)
        {
            res.push_back(data);
            return ;
        }

        for (int i = pos; i < data.size(); i++)
        {
            std::swap(data[pos], data[i]);
            permute_recursive_(data, pos+1, res);
            std::swap(data[pos], data[i]);
        };
    }


    std::vector<std::vector<int>> permute_recursive(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> res;

        std::vector aux = nums;
        permute_recursive_(aux, 0, res);

        return res;
    }


};

void test1()
{
   Solution solution;
   //std::cout<<solution.minFlips(2, 6, 5)<<std::endl;
   std::vector<int> arg{1, 2, 3, 4};
   auto res = solution.permute(arg);


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

   std::cout<<"========="<<std::endl;
   res = solution.permute_recursive(arg);

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

