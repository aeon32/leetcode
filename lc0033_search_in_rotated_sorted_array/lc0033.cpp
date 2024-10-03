#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <limits>
#include <type_traits>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>


class Solution {
 public:
    int search(std::vector<int>& nums, int target)
    {
        using nums_iterator = std::remove_reference<decltype(nums)>::type::const_iterator;
        using value_type = std::remove_reference< decltype(nums) > :: type::value_type;

        if (nums.empty())
            return -1;

        nums_iterator startIt = nums.cbegin();
        nums_iterator endIt = nums.cend() - 1;

        int res = -1;

        while(startIt <= endIt)
        {
            nums_iterator mid = startIt + (endIt - startIt) / 2;

            value_type startValue = *startIt;
            value_type endValue = *endIt;
            value_type midValue = *mid;
            std::cout<<startValue<<" "<<midValue<<" "<<endValue<<std::endl;

            bool first_part_sorted = startValue <= midValue;
            bool second_part_sorted = midValue <= startValue;

            if (target < midValue)
            {

                if (first_part_sorted)
                {
                    if (target >= startValue)
                    {
                        endIt = mid - 1;
                    } else
                    {
                       startIt = mid + 1;
                    }
                } else
                {
                    endIt = mid - 1;
                }

            } else if (target > *mid)
            {
                if (second_part_sorted)
                {

                    if (target <= endValue)
                        startIt = mid + 1;
                    else
                        endIt = mid - 1;

                } else
                {
                        startIt = mid + 1;

                }

            } else {
                res = mid - nums.cbegin();
                break;
            }


        }
        return res;
    }
};

int test(const std::string & nums, int target)
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
        res = solution.search(array, target);

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
    const char * nums = "[3,1]";

    int res = test(std::string(nums), 1);

}

void test0()
{
    const char * nums = "[0,1,2]";
    int res = test(std::string(nums), 0);
    res = test(std::string(nums), 1);
    res = test(std::string(nums), 2);
    res = test(std::string(nums), 3);
    res = test(std::string(nums), -1);



}


int main(int argc, char** argv)
{
    test1();
}

