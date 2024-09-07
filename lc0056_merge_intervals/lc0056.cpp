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
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {

        std::vector<std::vector<int>> res;

        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int> & vec1, const std::vector<int> & vec2) {return vec1.front() < vec2.front();});

        auto it = intervals.begin();
        std::vector<int> merging_interval = *it;
        ++it;

        bool merging_interval_updated = true;
        for (;it != intervals.end(); ++it)
        {
            if (it->front() > merging_interval.back())
            {
                res.push_back(merging_interval);
                std::swap(merging_interval,*it);
            } else if (it->back() > merging_interval.back())
            {
                merging_interval.back() = it->back();

            }
        }
        res.push_back(merging_interval);

        return res;
    }
};


void test(const std::string & nums)
{
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(nums.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");
        static_assert( std::ranges::range<PyObject_wrapper> , "as");

        std::vector<int> interval;
        std::vector<std::vector<int>> intervals;
        for (PyObject_wrapper row : parsed)
        {
            interval.clear();
            auto int_view = row | std::views::transform( [] (const PyObject_wrapper & wrapper) {return wrapper.asInt();});
            std::ranges::copy(int_view, std::back_inserter(interval));
            intervals.push_back(interval);

        }



        Solution solution;
        auto res = solution.merge(intervals);

        std::cout<<nums<<std::endl;
        std::cout<<"    [ ";
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

void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[[1,3],[2,6],[8,10],[15,18]]";

    test(std::string(nums));

}


void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = "[[1,4],[4,5]]";

    test(std::string(nums));

}


int main(int argc, char** argv)
{
    //char c = 0xFB;
    //std::cout<< (int) c <<std::endl;
    //test0();
    test1();
    test2();

}

