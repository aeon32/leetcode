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

    std::vector<std::vector<int>> combinationSum1(std::vector<int>& candidates, int target)
    {
        std::vector<std::vector<int>> res;

        std::sort(candidates.begin(), candidates.end());
        std::remove_cvref< decltype(candidates) >::type::iterator it =std::find_if(candidates.begin(), candidates.end(), [target](int val) { return val > target;});
        candidates.erase(it, candidates.end());

        std::vector<int> big_figure (candidates.size());
        int sum = 0;

        const unsigned int MAX_DIGIT = 12;


        std::vector<int> row;
        decltype(big_figure)::iterator fig_beg = big_figure.begin();
        decltype(big_figure)::iterator fig_end = big_figure.end();


        int current_digit_pos = 0;
        do {
            auto digit = fig_beg;
            while ( digit != fig_end && *(digit) == MAX_DIGIT)
            {
                *digit = 0;
                ++digit;
            };

            if (digit == fig_end)
                break;

            (*digit)++;
            res.push_back(big_figure);

        } while (true);


        return res;

    }

    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        std::vector<std::vector<int>> res;

        std::sort(candidates.begin(), candidates.end());
        std::remove_cvref< decltype(candidates) >::type::iterator it =std::find_if(candidates.begin(), candidates.end(), [target](int val) { return val > target;});
        candidates.erase(it, candidates.end());

        std::vector<int> big_figure (candidates.size());
        int sum = 0;


        std::vector<int> row;

        do {
            std::size_t digit_index = 0;
            while (digit_index < candidates.size() && (candidates[digit_index] + sum) > target)
            {
                sum -= candidates[digit_index] * big_figure[digit_index];
                big_figure[digit_index] = 0;
                digit_index++;
            }

            if (digit_index == candidates.size())
                break;

            big_figure[digit_index]++;
            sum += candidates[digit_index];

            if (sum == target)
            {
                row.clear();
                for(int i = 0; i < big_figure.size(); i++)
                {
                    int digit = candidates[i];
                    int count = big_figure[i];
                    while(count--)
                    {
                        row.push_back(digit);
                    }
                }
                res.push_back(row);
            }


        } while (true);


        return res;

    }
};

void test(const std::string & nums, int target)
{
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(nums.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");
        static_assert( std::ranges::range<PyObject_wrapper> , "as");

        std::vector<int> array;
        auto int_view = parsed | std::views::transform( [] (const PyObject_wrapper & wrapper) {return wrapper.asInt();});
        std::ranges::copy(int_view, std::back_inserter(array));

        Solution solution;
        auto res = solution.combinationSum(array, target);
        std::cout<<"[ ";
        for (std::vector<int> & row : res)
        {
            std::cout<<"[ ";
            for (int digit : row)
            {
                std::cout<<digit<<" ";
            }
            std::cout << "],";

        }
        std::cout << "]"<<std::endl;


    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }

}

void test0()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[2,3]";
    int target = 6;

    test(std::string(nums), target);
}

void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[2,3,7]";
    int target = 7;

    test(std::string(nums), target);

}



int main(int argc, char** argv)
{
    //char c = 0xFB;
    //std::cout<< (int) c <<std::endl;
    //test0();
    test0();

}

