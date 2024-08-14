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


class Solution
{
 public:
    using RPNStack= std::stack<int> ;

    int evalRPN(std::vector<std::string>& tokens)
    {
        RPNStack stack;
        constexpr std::string_view operations = "+-*/";
        for (const std::string & token : tokens)
        {
            if (token.size() == 1 &&
                 std::find(operations.begin(), operations.end(), token[0]) != operations.end())
            {
                int op2 = stack.top();
                stack.pop();
                int op1 = stack.top();
                stack.pop();
                int val = 0;
                switch (token[0])
                {
                case '+': val = op1 + op2;break;
                case '-': val = op1 - op2;break;
                case '*': val = op1 * op2;break;
                case '/': val = op1 / op2;break;
                }
                stack.push(val);
            } else
            {
                int val = std::stoi(token);
                stack.push(val);
            }
        }

        return stack.top();

    }
};


int test(const std::string & tokens)
{
    int res = -1;
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(tokens.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");


        static_assert( std::ranges::range<PyObject_wrapper> , "as");


        auto str_view = parsed | std::views::transform( [] (const PyObject_wrapper & wrapper) {return (wrapper).str().asString();});

        std::vector<std::string> token_parsed;
        std::ranges::copy(str_view, std::back_inserter(token_parsed));


        Solution solution;
        res = solution.evalRPN(token_parsed);

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
    const char * tokens = R"ad(["2","1","+","3","*"])ad";
    test(std::string(tokens));
    //answer should be 595352
}

void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * tokens = R"ad(["10","6","9","3","+","-11","*","/","*","17","+","5","+"])ad";
    test(std::string(tokens));
    //answer should be 595352
}




int main(int argc, char** argv)
{
    test2();

}


