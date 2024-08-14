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
    struct Interval
    {
        int start;
        int end;
    };

    bool is_ovelapped_sorted(const Interval & prev, const Interval & next) const
    {
        return next.start <= prev.end;
    }

    bool is_inside_sorted(const Interval & prev, const Interval & next) const
    {
        return next.end <=prev.end;
    }

    using Intervals = std::vector<Interval>;

    int findMinArrowShots(std::vector<std::vector<int>>& points_raw)
    {
        Intervals intervals;
        intervals.reserve(points_raw.size());
        for(std::vector<int> & row: points_raw)
        {
            intervals.emplace_back(Interval{row[0], row[1]});
        }

        auto interval_sorter = [] (const Interval & first, const Interval & second)
        {
            return first.start < second.start;
        };
        std::sort(intervals.begin(), intervals.end(), interval_sorter);

        Interval * prev_outer_interval = &intervals.front();

        int res = intervals.size();
        for (int i = 1; i < intervals.size(); i++)
        {
            Interval & current = intervals[i];
            if (is_inside_sorted(*prev_outer_interval, current))
            {
                prev_outer_interval = &current;
                res--;
            } else if (is_ovelapped_sorted(*prev_outer_interval, current))
            {
                res--;
            }  else
            {
                //no interception
                prev_outer_interval = &current;
            }

        }

        return res;
    }
};


int test(const std::string & intervals)
{
    int res = -1;
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(intervals.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");


        static_assert( std::ranges::range<PyObject_wrapper> , "as");

        std::vector<std::vector<int>> intervals;
        for (PyObject_wrapper interval:parsed)
        {
            std::cout<<interval.str().asString()<<std::endl;

            auto int_view = interval | std::views::transform( [] (const PyObject_wrapper & wrapper) {return wrapper.asInt();});

            std::vector<int> interval_parsed;

            std::ranges::copy(int_view, std::back_inserter(interval_parsed));
            intervals.emplace_back(interval_parsed);

        }

        Solution solution;
        res = solution.findMinArrowShots(intervals);

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
    const char * prices = "[[1,2],[2,3],[3,4],[4,5]]";

    test(std::string(prices));
    //answer should be 595352
}



int main(int argc, char** argv)
{
   test1();

}

