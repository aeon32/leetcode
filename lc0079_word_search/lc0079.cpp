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

    struct CheckWordRes
    {
        bool found_partially;
        bool found_full;
    };

    CheckWordRes check_word(int start_i, int start_j, std::vector<std::vector<char>>& board, const char * word )
    {

        char word_symbol = *word;
        if (word_symbol == 0)
            return CheckWordRes{true, true};

        char & board_symbol = board[start_j][start_i];
        if (board_symbol == word_symbol)
        {

            int N = board.size();
            int M = board.front().size();
            char board_symbol_backup = board_symbol;
            board_symbol = 0;
            word++;
            CheckWordRes ok{*word == 0, *word == 0};
            if (!ok.found_partially && start_i > 0)
                ok = check_word(start_i - 1, start_j, board, word);

            if (!ok.found_partially && start_i < M-1)
                ok = check_word(start_i + 1, start_j,  board, word);

            if (!ok.found_partially && start_j > 0 )
                ok = check_word(start_i, start_j - 1,  board, word);

            if (!ok.found_partially && start_j < N-1 )
                ok = check_word(start_i, start_j + 1, board, word);

            if (ok.found_full)
            {
                //std::cout<<"path "<< start_i<<" "<<start_j<<std::endl;
            }

            board_symbol = board_symbol_backup;
            return ok;

        } else
            return CheckWordRes{false, false};
    }

    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        int N = board.size();
        int M = board.front().size();

        for (int j = 0; j < N; j++)
        {
            std::vector<char> & row = board[0];
            for (int i = 0; i < M; i++)
            {
                CheckWordRes ok = check_word(i, j, board, word.c_str());
                if (ok.found_full)
                    return true;

            }
        }
        return false;

    }
};

void test(const std::string & nums, const std::string & word)
{
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(nums.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");
        static_assert( std::ranges::range<PyObject_wrapper> , "as");

        std::vector<std::vector<char>> array;
        std::vector<char> row_array;
        for (PyObject_wrapper row : parsed)
        {
            auto char_view = row | std::views::transform( [] (const PyObject_wrapper & wrapper) {return (char) wrapper.str().asString()[0];});
            std::ranges::copy(char_view, std::back_inserter(row_array));

            array.emplace_back();
            std::swap(array.back(), row_array);

        }

        Solution solution;
        bool res = solution.exist(array, word);
        std::cout<<"[ ";
        for (std::vector<char> & row : array)
        {
            std::cout<<"[ ";
            for (char letter : row)
            {
                std::cout<<letter<<" ";
            }
            std::cout << "],";

        }
        std::cout << "] word "<<word<< " res "<<res<<std::endl;


    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }

}


void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = R"=ad([["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]])=ad";
    const char * word = "ABCCED";

    test(std::string(nums), word);

}

void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = R"=ad([["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]])=ad";
    const char * word = "SEE";

    test(std::string(nums), word);
}

void test3()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = R"=ad([["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]])=ad";
    const char * word = "ABCB";

    test(std::string(nums), word);
}

void test4()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * nums = R"=ad([["A"]])=ad";
    const char * word = "A";

    test(std::string(nums), word);
}


int main(int argc, char** argv)
{
    //char c = 0xFB;
    //std::cout<< (int) c <<std::endl;
    //test0();
    test1();
    test2();
    test3();
    test4();
}

