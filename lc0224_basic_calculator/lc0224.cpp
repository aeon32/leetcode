#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <stack>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>


struct Calc
{

    using FiguresStack= std::stack<int> ;
    using OpStack = std::stack<char>;

    FiguresStack figuresStack;
    OpStack opStack;

    void feed_op(char op)
    {
        //std::cout<<op<<std::endl;
        if (op == '+' || op == '-' || op == '(')
        {
            opStack.push(op);
        }
        if (op == ')')
        {
            int val = figuresStack.top();
            figuresStack.pop();
            feed_val(val);
        }
    }

    void feed_val(int val)
    {
        //std::cout<<val<<std::endl;
        if (opStack.empty() )
        {
            figuresStack.push(val);
            return;
        } else if (opStack.top() == '(')
        {
            figuresStack.push(val);
            opStack.pop();
        } else if (opStack.top() == '+')
        {
            int val1 = figuresStack.top();
            figuresStack.pop();
            opStack.pop();
            figuresStack.push(val1 + val);
        } else if (opStack.top() == '-')
        {
            opStack.pop();
            int val1 = 0;
            if (!opStack.empty() && opStack.top() == '(')
            {
                opStack.pop();

            } else
            {
                if (!figuresStack.empty())
                {
                    val1 = figuresStack.top();
                    figuresStack.pop();
                }
            }
            figuresStack.push(val1 - val);
        }
    }

    int res()
    {
        return figuresStack.top();
    }
};

class Solution
{
 public:


    int calculate(std::string s)
    {
        const char * str = s.c_str();
        const char * str_end = str + s.size();

        Calc calc;

        const std::string_view special_chars = "+-()";
        while (str < str_end)
        {
            char symb = *str;
            if (std::isspace(symb))
            {
                str++;
                continue;;
            }

            int val;
            switch (symb)
            {
              case '+':
              case '-':
              case '(':
              case ')':
                  calc.feed_op(symb);
                  str++;
              break;
              default:
              {
                  std::from_chars_result conv = std::from_chars(str, str_end, val);
                  str = conv.ptr;
                  calc.feed_val(val);
              }

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
    const char * tokens = R"ad(1 + 1)ad";
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
    const char * tokens = R"ad(1 -(-2) )ad";
    std::cout<< __PRETTY_FUNCTION__<<" input:"<<tokens<<std::endl;
    test(std::string(tokens));
    //answer should be 595352
}



int main(int argc, char** argv)
{
    //test1();
    //test2();
    test3();

}


