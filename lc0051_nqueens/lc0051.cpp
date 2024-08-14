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
    std::cout<<"[";
    for (int i = 0; i <vec.size(); i++)
    {
        std::cout << vec[i];
        std::cout << (i == vec.size() - 1 ? ']' : ',');
    }
}

void out_debug(const char * prefix, int i, std::vector<int> & positions, std::vector<std::vector<int>> & possible_positions)
{
    std::cout <<prefix<<" i="<<i<<" ========"<<std::endl;
    for (int j = 0; j < positions.size(); j++)
    {
        std::cout<< "row" << j << " ";
        out(possible_positions[j]);
        int pos = positions[j];
        std::cout << " queen at " << (pos != -1 ? possible_positions[j][pos] : -1 )<< std::endl;
    }
    std::cout<<std::endl;

}

class Solution {
 public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        std::vector<std::vector<std::string>> res;
        if (n == 1)
        {
            res.push_back(std::vector<std::string> {std::string("Q")});
            return res;
        }
        if (n < 4)
            return res;

        std::vector <int> positions(n, -1);
        std::vector<std::vector<int>> possible_positions(n);
        for (int i = 0; i < n ; i++)
        {
            possible_positions[0].push_back(i);
        }

        int i = 1;
        do {

            //out_debug("before", i, positions, possible_positions);
            if ( i == n)
            {
                res.emplace_back(n,std::string(n,'.'));
                std::vector<std::string> & row = res.back();

                for (int j = 0; j < n; j++)
                {
                    row[j][possible_positions[j][positions[j]]] = 'Q';
                }

            }

            //unwind stack backward
            while(i >0 && (++positions[i-1] >= possible_positions[i-1].size()))
            {
                possible_positions[i-1].clear();
                positions[i-1] = -1;
                i--;
            }

            //out_debug("after increment", i, positions, possible_positions);

            if (i==0)
                break;


            while (i < n && positions[i] == -1)
            {

                //we should calculate possible positions
                for (int k = 0; k < n; k++)
                {
                    bool available_field = true;
                    for (int j = 0; available_field && (j < i); j++)
                    {
                        int queen_pos = possible_positions[j][positions[j]];
                        available_field = queen_pos!=k && std::abs(k - queen_pos) != std::abs(i - j);
                    }
                    if (available_field)
                        possible_positions[i].push_back(k);
                }
                if (!possible_positions[i].empty())
                    positions[i] = 0;
                else
                    break;
                i++;
            }

        } while(true);

       return res;

    }
};

void test1()
{
   Solution solution;
   //std::cout<<solution.minFlips(2, 6, 5)<<std::endl;
   auto res = solution.solveNQueens(4);


   for (auto & row : res)
   {
       for (int i = 0; i < row.size(); i++ )
       {
           std::cout<<row[i]<<std::endl;
       }
       std::cout<<"================="<<std::endl;


   }

}



int main(int argc, char** argv)
{
   test1();

}

