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
    int maxDistToClosest_complicated(std::vector<int>& seats) {


        bool is_empty_started = seats.front() == 0;
        int empty_space_len = is_empty_started ? 1 : 0;
        int max_empty_space_len = empty_space_len;
        bool left_empty_started = is_empty_started;

        int left_empty_space_len = empty_space_len;
        int right_empty_space_len = 0;


        for (int i = 1; i < seats.size(); i++)
        {
            int seat = seats[i];
            if (seat == 0)
            {
                if (is_empty_started)
                {
                    empty_space_len++;
                } else
                {
                    is_empty_started = true;
                    empty_space_len = 1;
                }

                if (empty_space_len > max_empty_space_len)
                    max_empty_space_len = empty_space_len;
                if (left_empty_started)
                {
                    left_empty_space_len++;
                }

                if (i == seats.size() - 1)
                    right_empty_space_len = empty_space_len;
            }

            if (seat == 1)
            {
                is_empty_started = false;
                left_empty_started = false;

            }
        }

        std::cout<< left_empty_space_len<<" "<<max_empty_space_len<<" "<<right_empty_space_len<<std::endl;


        return std::max({left_empty_space_len, right_empty_space_len, (max_empty_space_len + 1 ) / 2 });
    }

    int maxDistToClosest(std::vector<int>& seats) {
        int res = 0;
        int zero_count = 0;
        bool is_one_found = false;
        for(int i{}; i < (int)seats.size(); ++i)
        {
            if(seats[i] == 0)
                ++zero_count;
            else if(seats[i] == 1)
            {
                if(is_one_found)
                    res = std::max(res, (zero_count + 1) / 2);
                else
                    res = std::max(res, zero_count);
                is_one_found = true;
                zero_count = 0;
            }
        }

        res = std::max(res, zero_count);
        return res;
    }
};

void test(const std::string & seats)
{
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(seats.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");
        static_assert( std::ranges::range<PyObject_wrapper> , "as");

        std::vector<int> seats_parsed;
        auto int_view = parsed | std::views::transform( [] (const PyObject_wrapper & wrapper) {return wrapper.asInt();});
        std::ranges::copy(int_view, std::back_inserter(seats_parsed));

        Solution solution;
        auto res = solution.maxDistToClosest(seats_parsed);


        std::cout<<"[ ";
        for (int seat : seats_parsed)
        {
            std::cout<<seat<<",";
        }

        std::cout << "] - "<<res<<std::endl;


    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }

}

void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * seats = "[1,0,0,0,1,0,1,]";
    test(std::string(seats));
}

void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * seats = "[1,0,0,0]";
    test(std::string(seats));
}


void test3()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * seats = "[0,1]";
    test(std::string(seats));
}



int main(int argc, char** argv)
{
    //char c = 0xFB;
    //std::cout<< (int) c <<std::endl;
    //test0();
    test1();
    test2();
    test3();
}

