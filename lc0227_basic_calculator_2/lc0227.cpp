#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <stack>
#include <variant>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>


class Solution
{
 public:
    struct Op
    {
        char op;
    };

    using Token = std::variant<int, Op>;
    using OpStack = std::stack<Op>;
    using RPNStack = std::stack<int>;

    struct Calc
    {
        OpStack sorting_station;
        RPNStack rpn_stack;
        bool has_first_val;

        Calc():has_first_val(false)
        {

        }

        void feed(const Op & op)
        {
            //std::cout<<"op"<<op.op<<std::endl;
            if (sorting_station.empty())
            {
                if (op.op == '-' && !has_first_val)
                    push_exit_queue(0);
                sorting_station.push(op);
                return;
            }
            Op top_op = sorting_station.top();

            if (op.op == '-' || op.op == '+')
            {
                if (top_op.op == '(' )
                {
                    if (op.op == '-' && !has_first_val)
                        push_exit_queue(0);

                } else
                {
                    while (!sorting_station.empty() &&
                           (sorting_station.top().op == '-'||
                             sorting_station.top().op == '+' ||
                             sorting_station.top().op == '*' ||
                             sorting_station.top().op == '/'
                           )
                           )
                    {
                        push_exit_queue(sorting_station.top());
                        sorting_station.pop();
                    }

                }

                sorting_station.push(op);
            }

            if (op.op == '*' || op.op == '/')
            {
                while (!sorting_station.empty() &&
                      (
                        sorting_station.top().op == '*' ||
                        sorting_station.top().op == '/'
                       )
                 )
                {
                    push_exit_queue(sorting_station.top());
                    sorting_station.pop();
                }
                sorting_station.push(op);
            }

            if (op.op == '(')
            {
                has_first_val = false;
                sorting_station.push(op);
            }

            if (op.op == ')')
            {
                while (!sorting_station.empty() && sorting_station.top().op != '(')
                {
                    push_exit_queue(sorting_station.top());
                    sorting_station.pop();
                }
                sorting_station.pop();
            }


        }

        void feed(int val)
        {
            //std::cout<<"val"<<val<<std::endl;
            //sorting_station.push(val);
            has_first_val = true;
            push_exit_queue(val);
        }

        void push_exit_queue(int val)
        {
            rpn_stack.push(val);
        }

        void push_exit_queue(Op op)
        {
            int val2 = rpn_stack.top();
            rpn_stack.pop();
            int val1 = rpn_stack.top();
            rpn_stack.pop();
            int res = 0;
            switch(op.op)
            {
               case '+': res = val1 + val2; break;
               case '-': res = val1 - val2; break;
               case '*': res = val1 * val2; break;
               case '/': res = val1 / val2; break;
            }
            rpn_stack.push(res);

        }

        int res()
        {

            while(!sorting_station.empty())
            {
                Op op = sorting_station.top();
                sorting_station.pop();
                push_exit_queue(op);
            }
            return rpn_stack.top();
        }
    };


    int calculate(std::string s)
    {
        const char * str = s.c_str();
        const char * str_end = str + s.size();

        Calc calc;

        const std::string_view special_chars = "+-*/()";
        while (str < str_end)
        {
            char symb = *str;
            if (std::isspace(symb))
            {
                str++;
                continue;;
            }

            if (std::find(special_chars.cbegin(), special_chars.cend(), symb) != special_chars.cend())
            {
                calc.feed(Op{symb});
                str++;
            } else
            {
                int val;
                std::from_chars_result conv = std::from_chars(str, str_end, val);
                calc.feed(val);
                str = conv.ptr;

            }
        }
        return calc.res();
    }
};


int test(const std::string & statement)
{

    Solution solution;
    int res = solution.calculate(statement);

    std::cout<<"res : "<<res<<std::endl;
    return res;
}

void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    std::cout<< __PRETTY_FUNCTION__ <<std::endl;
    const char * tokens = R"ad(-4 + 1 - 2)ad";
    std::cout<< __PRETTY_FUNCTION__<<" input:"<<tokens<<std::endl;
    test(std::string(tokens));
    //answer should be 595352
}

void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * tokens = R"ad( 2-1 + 2 )ad";
    std::cout<< __PRETTY_FUNCTION__<<" input:"<<tokens<<std::endl;
    test(std::string(tokens));
    //answer should be 595352
}

void test3()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * tokens = R"ad(2 - (5-6)  )ad";
    std::cout<< __PRETTY_FUNCTION__<<" input:"<<tokens<<std::endl;
    test(std::string(tokens));
    //answer should be 595352
}

void test4()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * tokens = R"ad(1 + 3*4  )ad";
    std::cout<< __PRETTY_FUNCTION__<<" input:"<<tokens<<std::endl;
    test(std::string(tokens));
    //answer should be 595352
}

void test5()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * tokens = R"ad(1*2-3/4+5*6-7*8+9/10)ad";
    std::cout<< __PRETTY_FUNCTION__<<" input:"<<tokens<<std::endl;
    test(std::string(tokens));
    //answer should be 595352
}

int main(int argc, char** argv)
{
    /*
    test1();
    test2();
    test3();
    test4();
     */
    test5();

}


