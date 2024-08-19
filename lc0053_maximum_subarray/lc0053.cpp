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
    int maxSubArray(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums.front();

        int i = 0;
        int max_negative_num = nums[i];
        int val;
        while ( i<nums.size() && (val = nums[i++]) <0)
        {
            if (val > max_negative_num)
                max_negative_num = val;
        }
        //all are negative
        if (val < 0)
            return max_negative_num;

        std::vector<int> folded;
        folded.reserve(nums.size());
        folded.push_back(nums[i-1]);
        bool is_positive = true;

        for( ;i < nums.size(); i++)
        {
            val = nums[i];
            if (val >= 0)
            {
                if (is_positive)
                    folded.back() += val;
                else
                {
                    is_positive = true;
                    folded.push_back(val);
                }
            } else
            {
                if (is_positive)
                {
                    is_positive = false;
                    folded.push_back(val);
                } else
                {
                    folded.back() += val;
                }

            }
        }
        if (folded.back() < 0)
        {
            folded.resize(folded.size() - 1);
        }

        std::vector<int> dp((folded.size() + 1) / 2 );
        dp.front() = folded.front();
        for (i = 2; i < folded.size(); i+=2)
        {
            int j = i / 2;
            dp[j] = std::max({dp[j - 1] + folded[i - 1] + folded[i], folded[i] });
            //res = std::max({res, res + folded[i - 1] + folded[i], folded[i]});
        }
        return *std::max_element(dp.begin(), dp.end());



    }
};

int test(const std::string & nums)
{
    int res = -1;
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
        res = solution.maxSubArray(array);

    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }
    std::cout<<"res : "<<res<<std::endl;
    return res;
}

void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[-2,1,-3,4,-1,2,1,-5,4]";

    int res = test(std::string(nums));

}

void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[1]";

    int res = test(std::string(nums));

}

void test3()
{
    const char * nums = "[5,4,-1,7,8]";

    int res = test(std::string(nums));
}

void test4()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[8,-19,5,-4,20]";

    int res = test(std::string(nums));

}


int main(int argc, char** argv)
{
    //char c = 0xFB;
    //std::cout<< (int) c <<std::endl;
    test1();
    test2();
    test3();
    test4();
}

